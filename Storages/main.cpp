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
   // reader.writeToFile("file");

    //    StorageTree().readFromJSONFile("file");
    //    StorageDatabaseWriter writer("dataBaseName1");
    //    for(int i = 0; i < listId.size(); i++)
    //    {
    //        QString idTree = listId.at(i);
    //        StorageTree tree = reader.read(idTree);
    //        reader.writeToFile(idTree, "file2");
    //        QJsonObject obj = tree.toJSON();
    //        StorageTree jsonTree = StorageTree(idTree, obj);
    //        writer.write(jsonTree);
    //    }
    //    StorageDatabaseReader reader1("dataBaseName1");
    //    listId = reader1.readID();
    //    for(int i = 0; i < listId.size(); i++)
    //    {
    //        QString idTree = listId.at(i);
    //        reader1.writeToFile(idTree, "file2");
    //    }
    //    StorageTree().readFromJSONFile("file2");
#ifdef TESTS
//        TStorageTree tStorageTree;
//        QTest::qExec(&tStorageTree);


    //    TTableModel tTableModel;
    //    QTest::qExec(&tTableModel);

        TStorageDatabaseInterface tStorageDatabaseInterface;
        QTest::qExec(&tStorageDatabaseInterface);

//        TStorageTreeNode tStorageTreeNode;
//        QTest::qExec(&tStorageTreeNode);

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
