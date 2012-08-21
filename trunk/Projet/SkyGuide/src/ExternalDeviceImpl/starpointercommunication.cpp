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

StarPointerCommunication::StarPointerCommunication(QObject *parent) :
    QObject(parent)
{

    m_conn = new AbstractSerial(this);

    m_pingTimer = new QTimer(this);
    connect(m_pingTimer, SIGNAL(timeout()),
              this, SLOT(initConnection()));

    connect(m_conn, SIGNAL(readyRead()),
            this, SLOT(incommingData()));
    connect(m_conn, SIGNAL(signalStatus(QString,QDateTime)),
            this, SLOT(signalStatusChanged(QString, QDateTime)));

    //open connection and configure it
    m_conn->enableEmitStatus(true);
    m_conn->setDeviceName("/dev/ttyUSB0");
    if(m_conn->open(QIODevice::ReadWrite))
    {
        m_conn->setBaudRate(AbstractSerial::BaudRate9600);
        m_conn->setParity(AbstractSerial::ParityNone);
        m_conn->setDataBits(AbstractSerial::DataBits8);
        m_conn->setFlowControl(AbstractSerial::FlowControlOff);
    }


    //initialize connection
    m_pingTimer->start(PING_INTERVAL);
}


StarPointerCommunication::~StarPointerCommunication()
{
    m_conn->close();
    delete m_pingTimer;
    delete m_conn;
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
        qDebug() << "data:" << data;
        data.remove(0,1);
        data.chop(2);

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
    qDebug() << "serial status: " << status;
}

bool StarPointerCommunication::initConnection()
{
    return send(new CmdPing());
}

bool StarPointerCommunication::send(Command* cmd)
{
    QString tmp = cmd->prepareForSend();
    QString toSend = QString("$") + calculateCRC(tmp) + QString("\\r\\n");
    m_conn->write(toSend.toAscii());
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
    qDebug() << "CRC: " << crcInHex;

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
        rv->analyzeData();
    }

    return rv;
}

} // namespace ExternalDeviceImpl
