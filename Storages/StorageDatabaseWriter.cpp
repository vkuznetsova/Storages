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
    }

    database().commit();
}

void StorageDatabaseWriter::updateBalance(const int value, const QString idNode)
{
    QSqlQuery queryUpdateBalance(database());
    queryUpdateBalance.prepare("update nodes set balance = :value where id = :idNode");
    queryUpdateBalance.bindValue(":value", value);
    queryUpdateBalance.bindValue(":idNode", idNode);
    if(!queryUpdateBalance.exec())
    {
        qDebug()<<"Запрос для обновления balance в таблице nodes не выполнен";
    }
    checkLastError(queryUpdateBalance);
}

void StorageDatabaseWriter::updateExpense(const int value, const QString idNode)
{
    QSqlQuery queryUpdateExpense(database());
    queryUpdateExpense.prepare("update nodes set expense = :value where id = :idNode");
    queryUpdateExpense.bindValue(":value", value);
    queryUpdateExpense.bindValue(":idNode", idNode);
    if(!queryUpdateExpense.exec())
    {
        qDebug()<<"Запрос для обновления expense в таблице nodes не выполнен";
    }
    checkLastError(queryUpdateExpense);

}

