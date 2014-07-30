#include <QCoreApplication>
#include <QTime>

#include "TStorageTree.h"
#include "TTableModel.h"
#include "TStorageDatabaseInterface.h"
#include "TStorageTreeNode.h"
#include "TOrderGenerator.h"
#include "TTableModelOrder.h"

#include "Swindow.h"

int main(int argc, char *argv[])
{
#ifdef TESTS
//            TStorageTree tStorageTree;
//            QTest::qExec(&tStorageTree);


//    TTableModel tTableModel;
//    QTest::qExec(&tTableModel);

//    TStorageDatabaseInterface tStorageDatabaseInterface;
//    QTest::qExec(&tStorageDatabaseInterface);

    //        TStorageTreeNode tStorageTreeNode;
    //        QTest::qExec(&tStorageTreeNode);

    TOrderGenerator tOrderGenerator;
    QTest::qExec(&tOrderGenerator);

//    TTableModelOrder tTableModelOrder;
//    QTest::qExec(&tTableModelOrder);

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
