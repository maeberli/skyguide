/**
  * Class declaration file of CmdUnknown.
  *
  * @author Marco Aeberli
  *
  * @copyright Project P1 group DLM14 2012, all rights reserved
  */
#ifndef EXTERNALDEVICEIMPL_CMDUNKNWON_H
#define EXTERNALDEVICEIMPL_CMDUNKNWON_H

//include SkyGuide specific headers
#include "command.h"

namespace ExternalDeviceImpl {

/**
  * Command class for the CmdUnknwon trame.
  *
  * This class inherits Command, the base command implementation
  */
class CmdUnknwon : public Command
{
public:
    /**
      * Constructor, setups objects.
      *
      * @param data     String of data, which should represent the trame.
      */
    CmdUnknwon(QString data = "");

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

#endif // EXTERNALDEVICEIMPL_CMDUNKNWON_H
