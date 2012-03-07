#ifndef SKYRANGE_H
#define SKYRANGE_H

#include <QObject>

class SkyRange : public QObject
{
    Q_OBJECT
public:
    explicit SkyRange(QObject *parent = 0);
    explicit SkyRange(const SkyRange & skyrange);

signals:

public slots:

};

#endif // SKYRANGE_H
