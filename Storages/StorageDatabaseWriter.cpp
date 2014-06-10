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
    QSqlQuery queryDeleteFromTrees(database());
    database().transaction();
    queryDeleteFromTrees.prepare("delete from trees where id = :id");
    queryDeleteFromTrees.bindValue(":id", tree.id());
    if(!queryDeleteFromTrees.exec())
    {
        qDebug() << "Запрос для удаления существующей записи из trees не выполнен";
    }
    checkLastError(queryDeleteFromTrees);\
    //qWarning() << "deleting old tree";

    QSqlQuery query(database());
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
            //qWarning() << "inserting id: " << tree.id() << " parent: " << parent << " child: " << child;
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
        //qWarning() << "inserting id: " << tree.id() << " child: " << tree.root().id();
    }

    query.prepare("insert or replace into nodes (id, balance, expense) values (:id, :balance, :expense)");
    checkLastError(query);
    QHash<QString, StorageTreeNode> structureData = tree.structureData();
    foreach(const StorageTreeNode &child, structureData.values())
    {
        query.bindValue(":id", child.id());
        query.bindValue(":balance", child.getBalance());
        query.bindValue(":expense", child.getExpence());
        if(!query.exec())
        {
            qDebug()<<"Запрос для таблицы nodes не выполнен";
        }
        checkLastError(query);
        //qWarning() << "inserting id: " << child.id() << " balance: " << child.getBalance() << " expense: " << child.getExpence();
    }

    database().commit();
}

