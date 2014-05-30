#include <QCoreApplication>

#include "TStorageTree.h"
#include "TTableModel.h"
#include "TStorageDatabaseInterface.h"

#include "Swindow.h"

int main(int argc, char *argv[])
{
#ifdef TESTS
    TStorageTree tStorageTree;
    QTest::qExec(&tStorageTree);

    TTableModel tTableModel;
    QTest::qExec(&tTableModel);

    TStorageDatabaseInterface tStorageDatabaseInterface;
    QTest::qExec(&tStorageDatabaseInterface);

    return 0;
#endif

#ifdef GUI
    QApplication a(argc, argv);
    Swindow w(argc, argv, &a);
    w.show();
    return a.exec();
#endif

}
