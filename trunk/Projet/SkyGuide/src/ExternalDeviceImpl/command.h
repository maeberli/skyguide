/**
  * Class declaration file of Command.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef EXTERNALDEVICEIMPL_COMMAND_H
#define EXTERNALDEVICEIMPL_COMMAND_H


//include Qt-headers
#include <QObject>
#include <QString>

#include "starpointercommunication.h"

namespace ExternalDeviceImpl {

class StarPointerCommunication;

#define _SEP_ ','   //< Seperator sign between data informations.

/**
  * Abstract class implements the basics of a Communication command.
  *
  * Each command received or sent by StarPointerCommunication should inherit from this class.
  */
class Command :  public QObject
{

public:
    /**
      * Enum defines the different ping commands, with their proper command value.
      */
    enum Commands {
        Ping            = 00,
        PointerMode     = 01,
        GuideMode       = 02,
        GPS             = 03,
        Accelerometer   = 04,
        Magnetometer    = 05,
        PICStatus       = 06
    };

    /**
      * Constructor, setups objects.
      *
      * @param type     Command type of to setup object.
      * @param data     String of data, which should represent the trame.
      */
    Command(Commands type, QString data);

    /**
      * Prepare the command based on the member data for send.
      *
      * @return         Prepared command as a string.
      */
    virtual QString prepareForSend() const;

    /**
      * Analyze the data string submitted by constructor.
      * Safes the extracted information in the member variables.
      *
      * @return         True on success, False if an error occured.
      */
    virtual bool analyzeData();

    /**
      * Decide what to do if the method is called.
      *
      * This method could react if the StarPointerCommunication is for example
      * in a certain state and this methode is called (often for if the command is received).
      *
      * @param com      Reference to starpointer communication which contains state informations.
      */
    virtual void decide(StarPointerCommunication& com) = 0;

protected:
    Commands p_type;    //< type of the command object
    QString p_data;     //< (received) data string of the command
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_COMMAND_H
