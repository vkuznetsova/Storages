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
    QSqlQuery query(database());
    query.prepare("SELECT parent, child, balance, expense FROM nodes INNER JOIN trees"
                  " ON nodes.id = trees.child WHERE trees.id = :id");
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
    tree.autoSetLevel();

    return tree;
}

QList<QString> StorageDatabaseReader::readID()
{
    QList <QString> ids;
    QSqlQuery queryID(database());
    queryID.prepare("SELECT DISTINCT id FROM trees ORDER BY id ASC");

    if(!queryID.exec())
    {
        qDebug()<<"Запрос для выборки всех id деревьев не выполнен.....";
    }
    checkLastError(queryID);
    while(queryID.next())
    {
        ids << queryID.value(0).toString();
    }
    return ids;
}

void StorageDatabaseReader::writeToFile(const QString &idTree)
{
    StorageDatabaseReader reader("dataBaseName");
    StorageTree tree = reader.read(idTree);
    QJsonObject jsonGraph = tree.toJSON();
    QJsonArray array;
    array.append(QJsonValue(jsonGraph));
    QJsonDocument doc = QJsonDocument(array);
    QByteArray data = doc.toJson();
    QFile file("file.json");
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"Ошибка открытия файла для записи..";
    }
    file.write(data);
    file.close();
}
