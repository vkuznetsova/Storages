#include <QCoreApplication>
#include <QTime>

#include "TStorageTree.h"
#include "TTableModel.h"
#include "TStorageDatabaseInterface.h"

#include "Swindow.h"

int main(int argc, char *argv[])
{
    StorageDatabaseReader reader("dataBaseName");
    reader.readID();

//    for(int i = 1; i < 16; i++)
//    {
//        QTime timeWrite;
//        QTime timeRead;
//        StorageTree tree = StorageTree::generateTree(i);
//        tree.setID("idTree" + QString::number(i));
//        QFile::remove("dataBaseName");
//        StorageDatabaseWriter writer("dataBaseName");
//        timeWrite.start();
//        writer.write(tree);
//        StorageDatabaseReader reader("dataBaseName");
//        timeRead.start();
//        const StorageTree actual = reader.read(tree.id());
//        qDebug()<<tree.id()<<"level = "<<i<<"time of write = "<<(double)timeWrite.elapsed()/1000
//               <<"time of read = "
//              <<(double)timeRead.elapsed()/1000;
//    }


#ifdef TESTS


    TStorageTree tStorageTree;
    QTest::qExec(&tStorageTree);


    //        TTableModel tTableModel;
    //        QTest::qExec(&tTableModel);

    //    TStorageDatabaseInterface tStorageDatabaseInterface;
    //    QTest::qExec(&tStorageDatabaseInterface);

    return 0;
#endif

#ifdef GUI
    QApplication a(argc, argv);
    Swindow w(argc, argv, &a);
    w.show();
    return a.exec();
#endif

}
