#ifndef STORAGEDATABASEINTERFACE_H

#define STORAGEDATABASEINTERFACE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFile>

class StorageDatabaseInterface
{
public:
    StorageDatabaseInterface();
    StorageDatabaseInterface(const QString &dataBaseName);

    void createSchema();

private:
    QString dataBaseName_;
    QSqlDatabase dataBase_;
    QString pathFile_;
};

#endif // STORAGEDATABASEINTERFACE_H
