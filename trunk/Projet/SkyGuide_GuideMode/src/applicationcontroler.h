#ifndef APPLICATIONCONTROLER_H
#define APPLICATIONCONTROLER_H

#include <QThread>

#include "guidemodehandler.h"


class TerminationHandler : public QThread
{
    Q_OBJECT

public:
    TerminationHandler(GuideModeHandler* handler,  QObject* parent = NULL)
        :QThread(parent),
          p_handler(handler)
    {
    }

    ~TerminationHandler()
    {
    }

protected:
    void run();
private:
    GuideModeHandler* p_handler;
};


#endif // APPLICATIONCONTROLER_H
