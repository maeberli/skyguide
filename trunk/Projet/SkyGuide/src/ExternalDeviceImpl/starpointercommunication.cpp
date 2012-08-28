#include "starpointercommunication.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QTextStream>

#include "command.h"
#include "cmdaccelerometer.h"
#include "cmdgps.h"
#include "cmdguidemode.h"
#include "cmdmagnetometer.h"
#include "cmdpicstatus.h"
#include "cmdping.h"
#include "cmdpointermode.h"
#include "cmdunknown.h"

#define CRC_LENGTH 3

namespace ExternalDeviceImpl {

StarPointerCommunication::StarPointerCommunication(QString devName,
                                                   AbstractSerial::BaudRate baudrate,
                                                   AbstractSerial::Parity parity,
                                                   AbstractSerial::DataBits dataBits,
                                                   AbstractSerial::Flow flow,
                                                   QObject *parent) :
    QObject(parent),
    m_actState(StarPointerCommunication::ModePointer),
    m_devName(devName),
    m_baudrate(baudrate),
    m_parity(parity),
    m_dataBits(dataBits),
    m_flow(flow)
{

    m_conn = new AbstractSerial(this);

    m_pingTimer = new QTimer(this);
    connect(m_pingTimer, SIGNAL(timeout()),
              this, SLOT(sendPing()));

    connect(m_conn, SIGNAL(readyRead()),
            this, SLOT(incommingData()));
    connect(m_conn, SIGNAL(signalStatus(QString,QDateTime)),
            this, SLOT(signalStatusChanged(QString, QDateTime)));
}


StarPointerCommunication::~StarPointerCommunication()
{
    closeConnection();
    delete m_pingTimer;
    delete m_conn;
}

void StarPointerCommunication::openConnection()
{
    //open connection and configure it
    m_conn->enableEmitStatus(true);
    m_conn->setDeviceName(m_devName);
    if(m_conn->open(QIODevice::ReadWrite))
    {
        m_conn->setBaudRate(m_baudrate);
        m_conn->setParity(m_parity);
        m_conn->setDataBits(m_dataBits);
        m_conn->setFlowControl(m_flow);
    }
    else
    {
        logError(tr("couldn't open serial device: %1").arg(m_conn->errorString()));
    }

    //initialize connection
    m_pingTimer->start(PING_INTERVAL);
}

void StarPointerCommunication::closeConnection()
{
    m_pingTimer->stop();
    m_conn->close();
}

bool StarPointerCommunication::sendModeGuideFlash(int flashDirection)
{
    return send(CmdGuideMode(flashDirection));
}

bool StarPointerCommunication::changeInModeGuide()
{
    m_actState = StarPointerCommunication::ModeGuide;
    return send(CmdGuideMode());
}

bool StarPointerCommunication::changeInModePointer()
{
    m_actState = StarPointerCommunication::ModePointer;
    return send(CmdPointerMode());
}

void StarPointerCommunication::incommingData()
{
    QByteArray ba = m_conn->readAll();
    static QString buffer;
    buffer.append(QString::fromAscii(ba.data(), ba.length()));

    //extract commands
    //format: $[commande],[données]*[CRC]\r\n
    //"$01,123456*55\r\n$05,123546x456x45*cd\r\n$02,5g5g5*hh\r\n";
    QRegExp reg("\\$[0-9]{2},[0-9a-zA-Z,\\.]*\\*[0-9a-zA-Z]{2}\\\\r\\\\n");

    int index = reg.indexIn(buffer);
    if(index > 0)
        buffer.remove(0,index);

    if(reg.indexIn(buffer) == 0)
    {
        buffer.remove(0, reg.matchedLength());
        QString data = reg.cap();

        logVerbose(tr("received data: %1").arg(data));

        data.remove(0,1);
        data.chop(4);

        //check for each command crc
        if(checkCRC(data))
        {
            //remove crc data
            data.chop(CRC_LENGTH);

            Command* cmd = getCommandObject(data);

            if(cmd!=NULL)
                cmd->decide(*this);
        }
    }
}

void StarPointerCommunication::signalStatusChanged(const QString &status, QDateTime current)
{
    emit logVerbose(tr("serial device status: %1").arg(status));
}

bool StarPointerCommunication::sendPing()
{
    return send(CmdPing());
}

bool StarPointerCommunication::send(const Command& cmd)
{
    QString tmp = cmd.prepareForSend();
    QString toSend = QString("$") + calculateCRC(tmp) + QString("\\r\\n");

    return (-1 != m_conn->write(toSend.toAscii()));
}

bool StarPointerCommunication::checkCRC(QString data)
{
    char crc = data.at(0).toAscii();

    for(int i = 1; i < data.length()-CRC_LENGTH; ++i)
        crc ^= data.at(i).toAscii();

    QString crcInHex = "";
    QTextStream stream(&crcInHex);
    stream.setFieldWidth(2);
    stream.setPadChar('0');
    stream << hex << (int)crc << dec;

    emit logVerbose(tr("calculated CRC: %1").arg(crcInHex));

    return (data.right(CRC_LENGTH-1).toUpper() == crcInHex.toUpper());
}

QString StarPointerCommunication::calculateCRC(const QString& data)
{
    char crc = data.at(0).toAscii();

    for(int i = 1; i < data.length(); ++i)
        crc ^= data.at(i).toAscii();

    QString crcInHex = "";
    QTextStream stream(&crcInHex);
    stream.setFieldWidth(2);
    stream.setPadChar('0');
    stream << hex << (int)crc << dec;

    return data + "*" + crcInHex.toUpper();
}

Command* StarPointerCommunication::getCommandObject(QString data)
{
    Command* rv = NULL;

    QRegExp reg("^[0-9]{2}");

    if(0==reg.indexIn(data))
    {
        QString cmd = reg.cap();

        data.remove(0,3);

        switch(Command::Commands(cmd.toInt()))
        {
        case Command::GPS:
            rv = new CmdGPS(data);
            break;
        case Command::Accelerometer:
            rv = new CmdAccelerometer(data);
            break;
        case Command::GuideMode:
            rv = new CmdGuideMode(data);
            break;
        case Command::Magnetometer:
            rv = new CmdMagnetometer(data);
            break;
        case Command::PICStatus:
            rv = new CmdPicStatus(data);
            break;
        case Command::PointerMode:
            rv = new CmdPointerMode(data);
            break;
        case Command::Ping:
            rv = new CmdPing(data);
            break;
        default:
            rv = new CmdUnknwon();
            break;
        }

        //analyze the data and if they arent correct destroy the object return NULL
        if(!rv->analyzeData())
        {
            delete rv;
            rv = NULL;
        }
    }

    return rv;
}

} // namespace ExternalDeviceImpl
