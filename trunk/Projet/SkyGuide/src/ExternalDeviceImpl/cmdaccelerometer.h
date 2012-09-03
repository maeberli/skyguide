/**
  * Class declaration file of CmdAccelerometer.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef EXTERNALDEVICEIMPL_CMDACCELEROMETER_H
#define EXTERNALDEVICEIMPL_CMDACCELEROMETER_H

//include SkyGuide specific headers
#include "command.h"

namespace ExternalDeviceImpl {

/**
  * Command class for the Accelerometer trame.
  *
  * This class inherits Command, the base command implementation
  */
class CmdAccelerometer : public Command
{
public:
    /**
      * Constructor, setups objects.
      *
      * @param data     String of data, which should represent the trame.
      */
    CmdAccelerometer(QString data = "");

    /**
      * Prepare the command based on the member data for send.
      *
      * @return         Prepared command as a string.
      */
    QString prepareForSend() const;

    /**
      * Analyze the data string submitted by constructor.
      * Safes the extracted information in the member variables.
      *
      * @return         True on success, False if an error occured.
      */
    bool analyzeData();

    /**
      * Decide what to do if the method is called.
      *
      * This method could react if the StarPointerCommunication is for example
      * in a certain state and this methode is called (often for if the command is received).
      *
      * @param com      Reference to starpointer communication which contains state informations.
      */
    void decide(StarPointerCommunication& com);

private:
    int p_xComp;        //< x component of the vector transmitted
    int p_yComp;        //< y component of the vector transmitted
    int p_zComp;        //< z component of the vector transmitted
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDACCELEROMETER_H
