#ifndef STORAGEDATABASEINTERFACE_H

#define STORAGEDATABASEINTERFACE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "StorageTree.h"


class StorageDatabaseInterface
{
public:
    StorageDatabaseInterface();
    StorageDatabaseInterface(const QString &dataBaseName);

    ~StorageDatabaseInterface();

    void createSchema();

    QSqlDatabase database();

    bool open();


protected:
    void checkLastError(const QSqlQuery &query);

private:
    QString dataBaseName_;
};

#endif // STORAGEDATABASEINTERFACE_H
