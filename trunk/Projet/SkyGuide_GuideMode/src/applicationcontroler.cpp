#include "applicationcontroler.h"

void TerminationHandler::run()
{
    qDebug()<< "####################################";
    //wait for console input (carriage return)
    QTextStream qtin(stdin);
    qtin.readLine();
    qDebug()<< "####################################";

    p_handler->shutdownCommunication();
}
