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
    }
}

void StorageDatabaseInterface::createSchema()
{

    QSqlQuery query;
    QString str = "create table if not exists table trees ( id varchar primary key not null,"
            " parent varchar, child varchar);"
            " create table if not exists table nodes (id varchar primary key not null,"
            " balance integer, expense integer);";
    if(!query.exec(str))
    {
        qDebug()<< "Таблицы создать невозможно";
    }

    QString strInsertTrees =
            "replace into trees (id, parent, child) values ('%1', '%2', '%3');";
    str = strInsertTrees.arg("first")
            .arg("root")
            .arg("node1");
    if(!query.exec(str))
    {
        qDebug()<< "Данные в таблицу trees не вставлены";
    }

    str = strInsertTrees.arg("second")
            .arg("root")
            .arg("node2");
    if(!query.exec(str))
    {
        qDebug()<< "Данные в таблицу trees не вставлены";
    }

    QString strInsertNodes =
            "replace into nodes (id, balance, expense) values ('%1', %2, %3);";
    str = strInsertNodes.arg("root")
            .arg("10")
            .arg("5");
    if(!query.exec(str))
    {
        qDebug()<< "Данные в таблицу nodes не вставлены";
    }
    str = strInsertNodes.arg("node1")
            .arg("100")
            .arg("5");
    if(!query.exec(str))
    {
        qDebug()<< "Данные в таблицу nodes не вставлены";
    }
    str = strInsertNodes.arg("node2")
            .arg("-10")
            .arg("5");
    if(!query.exec(str))
    {
        qDebug()<< "Данные в таблицу nodes не вставлены";
    }

}
