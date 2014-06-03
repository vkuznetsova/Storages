#ifndef STORAGEDATABASEINTERFACE_H

#define STORAGEDATABASEINTERFACE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>

class StorageDatabaseInterface
{
public:
    StorageDatabaseInterface();
    StorageDatabaseInterface(const QString &dataBaseName);

    void createSchema();

protected:
    void checkLastError(const QSqlQuery &query);

private:
    QString dataBaseName_;
    QSqlDatabase dataBase_;
    QString pathFile_;
};

#endif // STORAGEDATABASEINTERFACE_H
