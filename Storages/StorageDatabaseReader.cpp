#include "StorageDatabaseReader.h"

StorageDatabaseReader::StorageDatabaseReader()
{
}

StorageDatabaseReader::StorageDatabaseReader(const QString &dataBaseName):
    StorageDatabaseInterface(dataBaseName)
{

}

StorageTree StorageDatabaseReader::read(const QString &idTree)
{
    if(idTree.isNull())
    {
        return StorageTree();
    }

    StorageTree tree = StorageTree(idTree);
    //qWarning() << "creating tree. id: " << tree.id();
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

        //qWarning() << "reading row parent: " << parent << " child: " << child << " balance: " << balance << " expense: " << expense;

        tree.addChild(parent, child);
        tree.setBalance(child, balance);
        tree.setExpense(child, expense);
    }
    tree.autoSetRoot();
    tree.autoSetLevel();

    //qWarning() << "autosetting root: " << tree.root().id();
    return tree;
}

QList<QString> StorageDatabaseReader::readID()
{
    QList <QString> ids;
    QSqlQuery queryID(database());
    queryID.prepare("select distinct id from trees order by id asc");

    if(!queryID.exec())
    {
        qDebug()<<"Запрос для выборки всех id деревьев не выполнен.....";
    }
    checkLastError(queryID);
    while(queryID.next())
    {
        ids << queryID.value(0).toString();
        //qDebug()<<"all ids from db.."<<queryID.value(0).toString();
    }
    return ids;
}
