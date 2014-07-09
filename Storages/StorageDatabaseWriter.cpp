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
    queryDeleteFromTrees.prepare("DELETE FROM trees WHERE id = :id");
    queryDeleteFromTrees.bindValue(":id", tree.id());
    if(!queryDeleteFromTrees.exec())
    {
        qDebug() << "Запрос для удаления существующей записи из trees не выполнен";
    }
    checkLastError(queryDeleteFromTrees);

    QSqlQuery query(database());
    query.prepare("INSERT INTO trees (id, parent, child) VALUES (:id, :parent, :child)");
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

    query.prepare("INSERT OR REPLACE INTO nodes (id, balance, expense, deliveryTime) VALUES (:id, :balance, :expense, :deliveryTime)");
    checkLastError(query);
    QHash<QString, StorageTreeNode> structureData = tree.structureData();
    foreach(const StorageTreeNode &child, structureData.values())
    {
        query.bindValue(":id", child.id());
        query.bindValue(":balance", child.getBalance());
        query.bindValue(":expense", child.getExpence());
        query.bindValue(":deliveryTime", child.getDeliveryTime());
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
    QSqlQuery queryUpdateDeliveryTime(database());
    queryUpdateDeliveryTime.prepare("UPDATE nodes SET balance = :value WHERE id = :idNode");
    queryUpdateDeliveryTime.bindValue(":value", value);
    queryUpdateDeliveryTime.bindValue(":idNode", idNode);
    if(!queryUpdateDeliveryTime.exec())
    {
        qDebug()<<"Запрос для обновления balance в таблице nodes не выполнен";
    }
    checkLastError(queryUpdateDeliveryTime);
}

void StorageDatabaseWriter::updateExpense(const int value, const QString idNode)
{
    QSqlQuery queryUpdateExpense(database());
    queryUpdateExpense.prepare("UPDATE nodes SET expense = :value WHERE id = :idNode");
    queryUpdateExpense.bindValue(":value", value);
    queryUpdateExpense.bindValue(":idNode", idNode);
    if(!queryUpdateExpense.exec())
    {
        qDebug()<<"Запрос для обновления expense в таблице nodes не выполнен";
    }
    checkLastError(queryUpdateExpense);
}

void StorageDatabaseWriter::updateDeliveryTime(const int value, const QString idNode)
{
    QSqlQuery queryUpdateExpense(database());
    queryUpdateExpense.prepare("UPDATE nodes SET deliveryTime = :value WHERE id = :idNode");
    queryUpdateExpense.bindValue(":value", value);
    queryUpdateExpense.bindValue(":idNode", idNode);
    if(!queryUpdateExpense.exec())
    {
        qDebug()<<"Запрос для обновления expense в таблице nodes не выполнен";
    }
    checkLastError(queryUpdateExpense);

}

void StorageDatabaseWriter::readFromJSONFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QByteArray data = file.readAll();
    QJsonDocument doc = doc.fromJson(data);
    QJsonObject obj = doc.object();
    qDebug()<<obj;
    StorageTree tree;
}
