#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "skydatabase.h"

SkyDatabase::SkyDatabase(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyDatabase"));
}

QList<SkyElement *> * SkyDatabase::getSkyElements(/* const SkyRange & range */)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("getSkyElements SkyDatabase -> not implemented"));

    QList<SkyElement *> *list = new QList<SkyElement *>();

    if (QFile::exists(QString("stars.db")))
        qDebug() << "Le fichier stars.db existe.";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QString("stars.db"));

    if (!db.open())
        qDebug() << "Erreur de connection !";

    QSqlQuery query;

    if (!query.exec(QString("SELECT * FROM stars where magnitude <= 4")))
        qDebug() << "Erreur d'accès à la base de données !";

    while (query.next())
    {
        SkyElement *temp = new SkyElement(query.value(1).toDouble(), query.value(2).toDouble(), query.value(4).toString(), query.value(5).toString(), query.value(8).toInt(), query.value(9).toDouble());
        list->append(temp);
    }

    query.clear();

    db.close();

    return list;
}

void SkyDatabase::start()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Start SkyDatabase -> not implemented"));
}

void SkyDatabase::stop()
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Stop SkyDatabase -> not implemented"));
}
