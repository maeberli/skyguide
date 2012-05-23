#ifndef BRIGHSTARS_H
#define BRIGHSTARS_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "Star.h"

class BrighStars
{
    private:

    QSqlDatabase _sqlDB;

    QString _bd;

    int _stars;

    double* _right_ascension;

    double* _declinaison;

    double* _magnitude;

    public:

    // constructor

    BrighStars(QString bd);

    void toSelect();

    double getRightAscension(int index)
    {
        return _right_ascension[index];
    }

    double getDeclinaison(int index)
    {
        return _declinaison[index];
    }

    double getMagnitude(int index)
    {
        return _magnitude[index];
    }

    int getCount()
    {
        return _stars;
    }

    // destructor

    ~BrighStars();
};

#endif // BRIGHSTARS_H
