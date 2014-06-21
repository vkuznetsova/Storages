#include <QCoreApplication>
#include <QTime>

#include "TStorageTree.h"
#include "TTableModel.h"
#include "TStorageDatabaseInterface.h"
#include "TStorageTreeNode.h"

#include "Swindow.h"

int main(int argc, char *argv[])
{
    StorageDatabaseReader reader("dataBaseName");
    QStringList listId = reader.readID();
    for(int i = 0; i < listId.size(); i++)
    {
        QString idTree = listId.at(i);
        reader.writeToFile(idTree);
    }

    StorageTree().readFromJSONFile("file.json");
#ifdef TESTS
//    TStorageTree tStorageTree;
//    QTest::qExec(&tStorageTree);


//    TTableModel tTableModel;
//    QTest::qExec(&tTableModel);

//    TStorageDatabaseInterface tStorageDatabaseInterface;
//    QTest::qExec(&tStorageDatabaseInterface);

//    TStorageTreeNode tStorageTreeNode;
//    QTest::qExec(&tStorageTreeNode);

    Q_UNUSED(argc)
    Q_UNUSED(argv)

    return 0;
#endif

#ifdef GUI
    QApplication a(argc, argv);
    Swindow w(argc, argv, &a);
    w.show();
    return a.exec();
#endif

}
