#include "StorageDatabaseInterface.h"

StorageDatabaseInterface::StorageDatabaseInterface()
{
}

StorageDatabaseInterface::StorageDatabaseInterface(const QString &dataBaseName):
    dataBaseName_(dataBaseName)
{
    open();
    // createSchema();
}

StorageDatabaseInterface::~StorageDatabaseInterface()
{
//    database().close();
//    QSqlDatabase::removeDatabase(dataBaseName_);
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
