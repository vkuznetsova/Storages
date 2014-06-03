#include "StorageDatabaseWriter.h"

StorageDatabaseWriter::StorageDatabaseWriter()
{
}

StorageDatabaseWriter::StorageDatabaseWriter(const QString &dataBaseName):
    StorageDatabaseInterface(dataBaseName)
{

}

void StorageDatabaseWriter::write(const StorageTree &tree)
{
    QSqlQuery query;
    query.prepare("insert into trees (id, parent, child) values (:id, :parent, :child)");
    checkLastError(query);

    const QHash<QString, QSet<QString> > structure = tree.structure();

    foreach(const QString &parent, structure.keys())
    {
        foreach(const QString &child, structure.value(parent))
        {
            query.bindValue(":id", tree.id());
            query.bindValue(":parent", parent);
            query.bindValue(":child", child);
            if(!query.exec())
            {
                qDebug()<<"Запрос для таблицы trees не выполнен";
            }
            checkLastError(query);
        }
    }
    if(!tree.root().id().isNull())
    {
        query.bindValue(":id", tree.id());
        query.bindValue(":parent", QString());
        query.bindValue(":child", tree.root().id());
        if(!query.exec())
        {
            qDebug()<<"Запрос для таблицы trees не выполнен";
        }
        checkLastError(query);
    }

    QSqlQuery query1;
    query1.prepare("insert into nodes (id, balance, expense) values (:id, :balance, :expense)");
    checkLastError(query1);
    QHash<QString, StorageTreeNode> structureData = tree.structureData();
    foreach(const StorageTreeNode &childID, structureData.values())
    {
        query1.bindValue(":id", childID.id());
        query1.bindValue(":balance", childID.getBalance());
        query1.bindValue(":expense", childID.getExpence());
        if(!query1.exec())
        {
            qDebug()<<"Запрос для таблицы nodes не выполнен";
        }
        checkLastError(query1);
    }
}

