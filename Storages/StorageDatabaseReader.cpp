#include "StorageDatabaseReader.h"

StorageDatabaseReader::StorageDatabaseReader()
{
}

StorageDatabaseReader::StorageDatabaseReader(const QString &dataBaseName):
    StorageDatabaseInterface(dataBaseName)
{

}

StorageTree StorageDatabaseReader::read(const QString idTree)
{
    QSqlQuery queryID(database());
    queryID.prepare("select distinct id from trees");

    if(!queryID.exec())
    {
        qDebug()<<"Запрос для выборки все id деревьев не выполнен.....";
    }
    checkLastError(queryID);
//    while(queryID.next())
//    {
//        qDebug()<<queryID.value(0).toString();
//    }
    if(idTree.isNull())
    {
        return StorageTree();
    }

    StorageTree tree = StorageTree(idTree);
    QSqlQuery query(database());
    query.prepare("select parent, child, balance, expense from nodes inner join trees"
                   " on nodes.id = trees.child where trees.id = :id");
    query.bindValue(":id", idTree);

    if(!query.exec())
    {
        qDebug()<<"Запрос для соединенных таблиц не выполнен.....";
    }
    checkLastError(query);
    while(query.next())
    {
        const QString parent = query.value(0).toString();
        const QString child = query.value(1).toString();
        const int balance = query.value(2).toInt();
        const int expense = query.value(3).toInt();
        tree.addChild(parent, child);
        tree.setBalance(child, balance);
        tree.setExpense(child, expense);
    }
    tree.autoSetRoot();
    return tree;
}
