#ifndef TSTORAGETREE_H

#define TSTORAGETREE_H

#include <QtTest/QtTest>
#include "StorageTree.h"

class TStorageTree : public QObject
{
    Q_OBJECT
public:
    TStorageTree();

private slots:
    void TestChildren_data();
    void TestChildren();

    void TestLevel_data();
    void TestLevel();

    void TestParent_data();
    void TestParent();

    void TestSubTree_data();
    void TestSubTree();

    void TestToString_data();
    void TestToString();

    void TestIsLeaf_data();
    void TestIsLeaf();

    void TestIsBoolean_data();
    void TestIsBoolean();

    void TestIsBalanced_data();
    void TestIsBalanced();

    void TestLeafs_data();
    void TestLeafs();

    void TestCheck_data();
    void TestCheck();

    void TestCheckMore_data();
    void TestCheckMore();

    void TestNSuns_data();
    void TestNSuns();

    void TestRun_data();
    void TestRun();

    void TestTotalSum_data();
    void TestTotalSum();

    void TestPositiveElemsSum_data();
    void TestPositiveElemsSum();

    void TestEuclidMetric_data();
    void TestEuclidMetric();

    void TestAccumBalance_data();
    void TestAccumBalance();

    void TestGenerateTree_data();
    void TestGenerateTree();

    void TestNodeForNum_data();
    void TestNodeForNum();

    void TestOrder_data();
    void TestOrder();

    void TestRemoveNode_data();
    void TestRemoveNode();

    void TestAutoSetRoot_data();
    void TestAutoSetRoot();

    void TestAutoSetLevel_data();
    void TestAutoSetLevel();

    void TestAutoSetLeaf_data();
    void TestAutoSetLeaf();

    void TestAddChild_data();
    void TestAddChild();

    void TestNodesToJSONArray_data();
    void TestNodesToJSONArray();

    void TestEdgeToJSON_data();
    void TestEdgeToJSON();

    void TestEdgesToJSONArray_data();
    void TestEdgesToJSONArray();

    void TestToJSON_data();
    void TestToJSON();

    void TestStorageTree_data();
    void TestStorageTree();

    void TestWalkUpTree_data();
    void TestWalkUpTree();
};

#endif // TSTORAGETREE_H
