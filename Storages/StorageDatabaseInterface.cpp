#include "StorageDatabaseInterface.h"

StorageDatabaseInterface::StorageDatabaseInterface()
{
}

StorageDatabaseInterface::StorageDatabaseInterface(const QString &dataBaseName):
    dataBaseName_(dataBaseName)
{

    //спросить у никиты как правильно открывать базы и почему так не правильно
    if(QSqlDatabase::contains(dataBaseName))
    {
        dataBase_ = QSqlDatabase::database(dataBaseName);
    }
    else
    {
        dataBase_ = QSqlDatabase::addDatabase("QSQLITE");
        dataBase_.setDatabaseName(dataBaseName);
    }

    if(!dataBase_.isOpen())
    {
        dataBase_.open();
        createSchema();
    }
}

void StorageDatabaseInterface::createSchema()
{
    QSqlQuery query;
    QString createTableTrees = "create table if not exists trees ( id varchar not null,"
            " parent varchar, child varchar, primary key(id, child));";
    QString createTableNodes = " create table if not exists nodes (id varchar primary key not null,"
            " balance integer, expense integer);";
    if(!query.exec(createTableTrees))
    {
        qDebug()<< "Таблицу Trees создать невозможно";
    }
    checkLastError(query);

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
