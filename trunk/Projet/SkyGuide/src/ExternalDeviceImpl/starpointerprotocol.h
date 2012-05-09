#ifndef STARPOINTERPROTOCOL_H
#define STARPOINTERPROTOCOL_H

#include <QObject>
//#include "../lib/libqserialdevice/abstractserial.h"


class StarPointerProtocol : public QObject
{
    Q_OBJECT
public:
    explicit StarPointerProtocol(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // STARPOINTERPROTOCOL_H
