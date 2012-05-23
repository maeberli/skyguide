#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QStringList>
#include <cmath>
#include <QVariant>
#include <QMessageBox>

#include "BrighStars.h"

BrighStars::BrighStars(QString bd) : _bd(bd)
{
    this->_stars = 1628;
    this->_right_ascension = new double[this->_stars];
    this->_declinaison = new double[this->_stars];
    this->_magnitude = new double[this->_stars];
    this->_sqlDB = QSqlDatabase::addDatabase("QSQLITE");
}


void BrighStars::toSelect()
{
    int i = 0;

    this->_sqlDB.setDatabaseName(this->_bd);

    if (!_sqlDB.open())
    {
        QMessageBox msgBox;
        msgBox.setText("Open connection with database failed !");
        msgBox.exec();

        return;
    }

    QSqlQuery query = this->_sqlDB.exec("SELECT right_ascension, declinaison, magnitude FROM stars");

    if (query.lastError().isValid())
    {
        this->_sqlDB.close();

        QMessageBox msgBox;
        msgBox.setText("Query failed !");
        msgBox.exec();

        return;
    }
    while (query.next())
    {
        this->_right_ascension[i] = query.value(0).toDouble();
        this->_declinaison[i] = query.value(1).toDouble();
        this->_magnitude[i] = query.value(2).toDouble();
        i++;
    }
    this->_sqlDB.close();
}

BrighStars::~BrighStars()
{
    delete[] _right_ascension;
    delete[] _declinaison;
    delete[] _magnitude;
}
