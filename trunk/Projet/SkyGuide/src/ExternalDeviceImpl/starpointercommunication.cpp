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



namespace ExternalDeviceImpl {

#define CRC_LENGTH 3

#define PING_INTERVAL 2999


StarPointerCommunication::StarPointerCommunication(QString devName,
                                                   AbstractSerial::BaudRate baudrate,
                                                   AbstractSerial::Parity parity,
                                                   AbstractSerial::DataBits dataBits,
                                                   AbstractSerial::Flow flow,
                                                   QObject *parent) :
    QObject(parent),
    p_actState(StarPointerCommunication::ModePointer),
    p_devName(devName),
    p_baudrate(baudrate),
    p_parity(parity),
    p_dataBits(dataBits),
    p_flow(flow)
{

    p_conn = new AbstractSerial(this);

    p_pingTimer = new QTimer(this);
    connect(p_pingTimer, SIGNAL(timeout()),
              this, SLOT(sendPing()));

    connect(p_conn, SIGNAL(readyRead()),
            this, SLOT(incommingData()));
    connect(p_conn, SIGNAL(signalStatus(QString,QDateTime)),
            this, SLOT(signalStatusChanged(QString, QDateTime)));
}


StarPointerCommunication::~StarPointerCommunication()
{
    closeConnection();
    delete p_pingTimer;
    delete p_conn;
}

void StarPointerCommunication::openConnection(ProtocollStates startState)
{
    //open connection and configure it
    p_conn->enableEmitStatus(true);
    p_conn->setDeviceName(p_devName);
    if(p_conn->open(QIODevice::ReadWrite))
    {
        p_conn->setBaudRate(p_baudrate);
        p_conn->setParity(p_parity);
        p_conn->setDataBits(p_dataBits);
        p_conn->setFlowControl(p_flow);
    }
    else
    {
        logError(tr("couldn't open serial device: %1").arg(p_conn->errorString()));
    }

    //initialize connection
    switch(startState)
    {
    case ModeGuide:
        changeInModeGuide();
        break;
    case ModePointer:
        changeInModePointer();
        break;
    }
}

void StarPointerCommunication::closeConnection()
{
    p_pingTimer->stop();
    p_conn->close();
}

bool StarPointerCommunication::sendModeGuideFlash(int flashDirection)
{
    if(p_actState != StarPointerCommunication::ModeGuide)
    {
        p_actState = StarPointerCommunication::ModeGuide;
    }

    return send(CmdGuideMode(flashDirection));
}

bool StarPointerCommunication::changeInModeGuide()
{
    p_actState = StarPointerCommunication::ModeGuide;
    p_pingTimer->stop();
    return send(CmdGuideMode());
}

bool StarPointerCommunication::changeInModePointer()
{
    p_actState = StarPointerCommunication::ModePointer;
    p_pingTimer->start();
    return send(CmdPointerMode());
}

void StarPointerCommunication::incommingData()
{
    QByteArray ba = p_conn->readAll();
    static QString buffer;

    //appends the data at the end of the buffer.
    buffer.append(QString::fromAscii(ba.data(), ba.length()));

    //extract commands
    //format: $[commande],[données]*[CRC]\r\n
    //"$01,123456*55\r\n$05,123546x456x45*cd\r\n$02,5g5g5*hh\r\n";
    QRegExp reg("\\$[0-9]{2},[0-9a-zA-Z,\\.]*\\*[0-9a-zA-Z]{2}\\r\\n");

    // if the regex match not, from the beginning,
    // remove the the data in front
    int index = reg.indexIn(buffer);
    if(index > 0)
        buffer.remove(0,index);

    //Now, if the regex match at the first position of the string, it's a correct trame.
    if(reg.indexIn(buffer) == 0)
    {
        //remove commmand form the buffer.
        buffer.remove(0, reg.matchedLength());
        QString data = reg.cap();

        //remove the '$' of the string
        data.remove(0,1);

        //remove the trailing "\r\n"
        data.chop(2);

        logVerbose(tr("received data: %1").arg(data));

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
    //lets prepare the string with the data specified in cmd
    QString tmp = cmd.prepareForSend();
    // calculate the CRC of the data-string and append the control characters
    QString toSend = QString("$") + calculateCRC(tmp) + QString("\r\n");

    logVerbose(tr("sent data: %1").arg(toSend));

    return (-1 != p_conn->write(toSend.toAscii()));
}

bool StarPointerCommunication::checkCRC(QString data)
{
    char crc = 0;

    // calculated the XOR CRC with each character of the string (excluded trailing CRC).
    for(int i = 0; i < data.length()-CRC_LENGTH; ++i)
        crc ^= data.at(i).toAscii();

    // Conversion of the CRC-byte in a two sign HEX-value.
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
    char crc = 0;

    // calculate the XOR CRC with each character fo the string
    for(int i = 0; i < data.length(); ++i)
        crc ^= data.at(i).toAscii();

    // Conversio nfo the CRC-byte in a two sign HEX-value.
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
