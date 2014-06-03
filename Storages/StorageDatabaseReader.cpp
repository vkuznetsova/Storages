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
    QSqlQuery query;
    query.prepare("select parent, child from trees where id = :id");
    query.bindValue(":id", idTree);

    if(idTree.isNull())
    {
        return StorageTree();
    }

    QSqlQuery query1;
    query1.prepare("select nodes.balance, nodes.expense from trees inner join nodes"
                   "on trees.child = nodes.id where trees.id = :id");
    query1.bindValue(":id", idTree);

    if(!query.exec())
    {
        qDebug()<<"Запрос для таблицы trees не выполнен.....";
    }
    checkLastError(query);

    if(!query1.exec())
    {
        qDebug()<<"Запрос для соединенных таблиц не выполнен.....";
    }
    query1.exec();
    checkLastError(query1);

    StorageTree tree = StorageTree(idTree);
    while(query.next())
    {
        const QString parent = query.value(0).toString();
        const QString child = query.value(1).toString();
        tree.addChild(parent, child);
        while(query1.next())
        {
            const int balance = query1.value(2).toInt();
            const int expense = query1.value(3).toInt();
            tree.setBalance(child, balance);
            tree.setExpense(child, expense);
        }
   }
    tree.autoSetRoot();
    return tree;
}
