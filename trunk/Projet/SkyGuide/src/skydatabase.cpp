#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "skydatabase.h"

SkyDatabase::SkyDatabase(SkyConfiguration* config, QObject *parent) :
    SkyComponent(config, parent)
{
    emit logMessage(SKYLOGGER::VERBOSE, tr("Constructor SkyDatabase"));
}

QList<SkyElement *> * SkyDatabase::getSkyElements()
{
    QList<SkyElement *> *list = new QList<SkyElement *>();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(QString("stars.db"));

    if (!db.open())
        emit logMessage(SKYLOGGER::ERROR, tr("Database connection error: %1").arg(db.lastError().text()));

    QSqlQuery query;

    if (!query.exec(QString("SELECT * FROM stars where magnitude <= 4")))
        emit logMessage(SKYLOGGER::ERROR, tr("Database access error: %1").arg(db.lastError().text()));

    while (query.next())
    {
        SkyElement *temp = new SkyElement(query.value(1).toDouble(), query.value(2).toDouble(), query.value(4).toString(), query.value(5).toString(), query.value(8).toInt(), query.value(9).toDouble());
        list->append(temp);
    }

    query.clear();

    db.close();

    return list;
}
