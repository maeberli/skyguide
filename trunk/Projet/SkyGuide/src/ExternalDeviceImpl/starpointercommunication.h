/**
  * Class declaration file of StarPointerCommunication.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef EXTERNALDEVICEIMPL_STARPOINTERCOMMUNICATION_H
#define EXTERNALDEVICEIMPL_STARPOINTERCOMMUNICATION_H

//include Qt-headers
#include <QObject>
#include <QTimer>

//include SkyGuide specific headers
#include "abstractserial.h"

namespace ExternalDeviceImpl {

class Command;

/**
  * Class to access to a StarPointer Device.
  *
  * It contains te implementation of the protocol specific functionality and
  * it uses a serial connection for the communication.
  *
  */
class StarPointerCommunication : public QObject
{
    Q_OBJECT
public:

    /**
      * Defines the different possible commuication states.
      */
    enum ProtocollStates {
        ModeGuide           = 00,
        ModePointer         = 01
    };

    /**
      * Constructor, creates and initialize the object.
      *
      * @param baudrate     Baudrate of the serial communication
      * @param parity       Parameter to set the Parity-Bit configuration of the serial communication.
      * @param dataBits     Parameter to set the number of dataBit configuration of the serial communication.
      * @param flow         Paramter to set the flow configuration fo the serial communication.
      * @param parent   parent object (Qt-specific)
      */
    explicit StarPointerCommunication(
            QString devName,
            QString baudrate,
            QString parity,
            QString dataBits,
            QString flow,
            QObject *parent = 0);

    /**
      * Destructor, does the cleanup.
      */
    ~StarPointerCommunication();

    /**
      * Opens the connection and get into the specified mode.will
      *
      * @param startState   Connection  be initialized whith this state.
      */
    void openConnection(ProtocollStates startState =  ModeGuide);

    /**
      * Close the connection to the device.
      */
    void closeConnection();

    /**
      * Sends the command to set the flash direction on the external.
      * If not already in guide mode, the state will change to GuideMode.
      *
      * @param flashDirection   Direction of the flash on device screen.
      * @return                 True on success, false if an error occured.
      */
    bool sendModeGuideFlash(int flashDirection);

    /**
      * Change protocol state in Mode Gudie.
      *
      * @return                 True on success, false if an error occured.
      */
    bool changeInModeGuide();

    /**
      * Change protocol state in ModePointer
      *
      * @return                 True on success, false if an error occured.
      */
    bool changeInModePointer();

signals:
    /**
      * Signals that the communication has received new GPS data.
      *
      * @param longitude        Longitude information of GPS.
      * @param latitude         Latitude information of GPS.
      */
    void receivedGPSData(double longitude, double latitude);

    /**
      * Signals that the communication has received new Accelormeter data.
      *
      * @param xComp            x component of the accelormeter vector.
      * @param yComp            y component of the accelormeter vector.
      * @param zComp            z component of the accelormeter vector.
      */
    void receivedAccelormeterData(int xComp, int yComp, int zComp);

    /**
      * Signals that the communication has received new Magnetometer data.
      *
      * @param xComp            x component of the magnetometer vector.
      * @param yComp            y component of the magnetometervector.
      * @param zComp            z component of the magnetometer vector.
      */
    void receivedMagnetometerData(int xComp, int yComp, int zComp);

    /**
      * Signals that the object likes to log an error.
      *
      * @param message          Error-text to log.
      */
    void logError(QString message);

    /**
      * Signals thaht the object likes to log a info message.
      *
      * @param message          Info-text to log.
      */
    void logInfo(QString message);

    /**
      * Signals that the object likes to log a verbose message.
      *
      * @param message          Verbose-message to log.
      */
    void logVerbose(QString message);


private slots:
        /**
          * Handles the incomming data on the serial device.
          */
        void incommingData();

        /**
          * Handle the status changes of the serial device.
          *
          * @param status       Status text.
          * @param current      Time of the status change.
          */
        void signalStatusChanged(const QString &status, QDateTime current);

        /**
          * Send the ping command.
          */
        bool sendPing();

private:
    AbstractSerial *p_conn;                     //< Serial device socket
    ProtocollStates p_actState;                 //< actual state in which the protocol is in.
    QTimer *p_pingTimer;                        //< Intervall for send the ping command, to kepp connection alive.

    const QString p_devName;                    //< Serial device name.
    const QString p_baudrate;                   //< baudrate connection config
    const QString p_parity;                     //< parity connection config
    const QString p_dataBits;                   //< dataBits connection config
    const QString p_flow;                       //< flow connection config

    /**
      * sends the command passed as argument.
      *
      * @param cmd              Command to send.
      * @return                 True on success, false on error.
      */
    bool send(const Command &cmd);

    /**
      * Checks the CRC.
      *
      * format expected: "DATA*CC" where Data is the Ascii-string,
      * the '*' a seperator and CC the two Ascii signs of the CRC in hex.
      * Character of String interpretet as Ascii -> transformation in byte-value.
      * CRC-calculation XOR on each byte.
      *
      * @param data             Data-string to verfifie.
      * @return                 True if CRC ok, fals if not.
      */
    bool checkCRC(QString data);

    /**
      * Calculates the the CRC and adds the calculatet information to the string passed.
      *
      * @param data             For this string the CRC is calculatet.
      * @return                 String passed by argument, with appendend CRC
      *                         in hex (ascii characters) seperated by ','
      */
    QString calculateCRC(const QString& data);

    /**
      * Analyzes the cmomand-type field of a trame
      * and returns an object of the associeted object
      *
      * @param data             Data string to analyze.
      * @return                 A pointer to the created object, Null-pointer if failure occured or commnad not found.
      */
    Command* getCommandObject(QString data);

    // friend class of commands so that they can decide(),
    // based of information in StarPointerCommunicationObject
    friend class CmdAccelerometer;
    friend class CmdGPS;
    friend class CmdGuideMode;
    friend class CmdMagnetometer;
    friend class CmdPicStatus;
    friend class CmdPing;
    friend class CmdPointerMode;
    friend class CmdUnknwon;
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_STARPOINTERCOMMUNICATION_H
