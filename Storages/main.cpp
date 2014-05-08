#include <QCoreApplication>

#include "TStorageTree.h"

int main(int argc, char *argv[])
{
    TStorageTree tStorageTree;
    QTest::qExec(&tStorageTree);

    return 0;
}
