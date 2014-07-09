#include "StorageDatabaseInterface.h"

StorageDatabaseInterface::StorageDatabaseInterface()
{
}

StorageDatabaseInterface::StorageDatabaseInterface(const QString &dataBaseName):
    dataBaseName_(dataBaseName)
{
    open();
}

StorageDatabaseInterface::~StorageDatabaseInterface()
{
}

QSqlDatabase StorageDatabaseInterface::database()
{
    return QSqlDatabase::database(dataBaseName_, false);
}

bool StorageDatabaseInterface::open()
{
    if(!QSqlDatabase::contains(dataBaseName_))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", dataBaseName_);
        db.setDatabaseName(dataBaseName_);

        if(!db.open())
        {
            qWarning() << "database not open" << db.lastError().text();
            return false;
        }

        createSchema();
    }
    return true;
}

void StorageDatabaseInterface::createSchema()
{
    QSqlQuery query(database());
    QString createTableTrees = "CREATE TABLE IF NOT EXISTS trees ( id VARCHAR NOT NULL,"
            " parent VARCHAR, child VARCHAR, PRIMARY KEY(id, child));";
    QString createTableNodes = " CREATE TABLE IF NOT EXISTS nodes (id VARCHAR PRIMARY KEY NOT NULL,"
            " balance INTEGER, expense INTEGER, deliveryTime INTEGER);";
    if(!query.exec(createTableTrees))
    {
        qDebug()<< "Таблицу Trees создать невозможно";
    }
    if(!query.exec(createTableNodes))
    {
        qDebug()<< "Таблицу Nodes создать невозможно";
    }
    checkLastError(query);
}

void StorageDatabaseInterface::checkLastError(const QSqlQuery &query)
{
    if(query.lastError().text() != " ")
    {
        qWarning() << query.lastError().text();
    }
}
