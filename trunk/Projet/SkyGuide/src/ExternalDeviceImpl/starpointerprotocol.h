#ifndef STARPOINTERPROTOCOL_H
#define STARPOINTERPROTOCOL_H

#include <QObject>
#include "abstractserial.h"


class StarPointerProtocol : public QObject
{
    Q_OBJECT
public:
    explicit StarPointerProtocol(QObject *parent = 0);
    ~StarPointerProtocol();

private slots:
        void incommingData();

private:
    AbstractSerial *m_conn;
};

#endif // STARPOINTERPROTOCOL_H
