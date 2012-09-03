/**
  * Class declaration file of CmdPing.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef EXTERNALDEVICEIMPL_CMDPING_H
#define EXTERNALDEVICEIMPL_CMDPING_H

//include SkyGuide specific headers
#include "command.h"

namespace ExternalDeviceImpl {

/**
  * Command class for the ping trame.
  *
  * This class inherits Command, the base command implementation
  */
class CmdPing : public Command
{
public:
    /**
      * Constructor, setups objects.
      *
      * @param data     String of data, which should represent the trame.
      */
    CmdPing(QString data = "");

    /**
      * Decide what to do if the method is called.
      *
      * This method could react if the StarPointerCommunication is for example
      * in a certain state and this methode is called (often for if the command is received).
      *
      * @param com      Reference to starpointer communication which contains state informations.
      */
    void decide(StarPointerCommunication& com);
};

} // namespace ExternalDeviceImpl

#endif // EXTERNALDEVICEIMPL_CMDPING_H
