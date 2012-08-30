#ifndef STARPOINTERCOMMUNICATION_H
#define STARPOINTERCOMMUNICATION_H

#include <QObject>
#include <QTimer>
#include "abstractserial.h"

namespace ExternalDeviceImpl {

class Command;

class StarPointerCommunication : public QObject
{
    Q_OBJECT
public:
    enum ProtocollStates {
        ModeGuide           = 00,
        ModePointer         = 01
    };

    explicit StarPointerCommunication(
            QString devName,
            AbstractSerial::BaudRate baudrate,
            AbstractSerial::Parity parity,
            AbstractSerial::DataBits dataBits,
            AbstractSerial::Flow flow,
            QObject *parent = 0);
    ~StarPointerCommunication();

    void openConnection();
    void closeConnection();

    bool sendModeGuideFlash(int flashDirection);
    bool changeInModeGuide();
    bool changeInModePointer();

signals:
    void receivedGPSData(double longitude, double latitude);
    void receivedAccelormeterData(int xComp, int yComp, int zComp);
    void receivedMagnetometerData(int xComp, int yComp, int zComp);

    void logError(QString message);
    void logInfo(QString message);
    void logVerbose(QString message);


private slots:
        void incommingData();
        void signalStatusChanged(const QString &status, QDateTime current);
        bool sendPing();

private:
    AbstractSerial *m_conn;
    ProtocollStates m_actState;
    QTimer *m_pingTimer;

    QString m_devName;
    AbstractSerial::BaudRate m_baudrate;
    AbstractSerial::Parity m_parity;
    AbstractSerial::DataBits m_dataBits;
    AbstractSerial::Flow m_flow;

    bool send(const Command &cmd);

    bool checkCRC(QString data);
    QString calculateCRC(const QString& data);
    Command* getCommandObject(QString data);

    // friend class of commands so that they can decide(),
    // based of information in StarPointerCommunicationObject
    friend class CmdGPS;
    friend class CmdAccelerometer;
    friend class CmdMagnetometer;
};

} // namespace ExternalDeviceImpl

#endif // STARPOINTERCOMMUNICATION_H
