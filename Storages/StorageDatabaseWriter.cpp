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
    checkLastError(queryDeleteFromTrees);\

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

    query.prepare("INSERT OR REPLACE INTO nodes (id, balance, expense) VALUES (:id, :balance, :expense)");
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
    queryUpdateBalance.prepare("UPDATE nodes SET balance = :value WHERE id = :idNode");
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
    queryUpdateExpense.prepare("UPDATE nodes SET expense = :value WHERE id = :idNode");
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
    QJsonDocument doc1;
    QJsonDocument doc = doc1.fromJson(data);
    QJsonArray array = doc.array();
    QJsonObject obj;
    StorageTree tree;

    //QJsonObject obj = array.last().toObject();
    for(int i = 0; i < array.size(); i++)
    {
        obj = array[i].toObject();
        const QString idTree = obj.value(StorageTree::idKey).toString();
        tree = StorageTree(idTree, obj);
        qDebug()<<"obj"<<obj;
        qDebug()<<"tree"<<tree.toJSON();
        StorageDatabaseWriter::write(tree);
    }
    //    QString line;
    //    for(int i = 0; i < obj.keys().size(); i++)
    //    {
    //        if(obj[obj.keys().at(i)].isArray())
    //        {
    //            QJsonArray arr = obj[obj.keys().at(i)].toArray();
    //            for(int j = 0; j < arr.size(); j++)
    //            {
    //                QVariantMap map = arr[j].toObject().toVariantMap();
    //                foreach (const QString &it, map.keys())
    //                {
    //                    line += it +  map.value(it).toString();
    //                }
    //            }
    //        }
    //        else
    //        {
    //            QString listData = obj.keys().at(i);
    //            QString value = obj[obj.keys().at(i)].toString();
    //            line += listData + value;
    //        }
    //    }

}
