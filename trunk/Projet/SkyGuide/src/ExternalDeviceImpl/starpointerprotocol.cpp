#include "starpointerprotocol.h"

#include <QByteArray>
#include <QString>

StarPointerProtocol::StarPointerProtocol(QObject *parent) :
    QObject(parent)
{
    m_conn = new AbstractSerial(this);

    connect(m_conn, SIGNAL(readyRead()),
            this, SLOT(incommingData()));

    //open connection and configure it
    m_conn->enableEmitStatus(true);
    m_conn->setDeviceName("/dev/ttyS0");
    m_conn->open(QIODevice::ReadWrite);
    m_conn->setBaudRate(AbstractSerial::BaudRate9600);
    m_conn->setParity(AbstractSerial::ParityNone);
    m_conn->setDataBits(AbstractSerial::DataBits8);
    m_conn->setFlowControl(AbstractSerial::FlowControlOff);
}


StarPointerProtocol::~StarPointerProtocol()
{
    m_conn->close();
    delete m_conn;
}

void StarPointerProtocol::incommingData()
{
    QByteArray ba = m_conn->readAll();
    QString test = QString::fromAscii(ba.data(), ba.length());

    //extract commands


    //check for each command crc

    //search the command and parse it
}
