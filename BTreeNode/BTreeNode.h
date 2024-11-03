#pragma once

#include <vector>
#include "../DataUnit/DataUnit.h"

class BTreeNode {
private:
    int t;
    int n;
    bool leaf;
    std::vector<DataUnit> data;
    std::vector<BTreeNode *> children;
public:
    explicit BTreeNode(int t, bool leaf = true);
    ~BTreeNode();

    void setN(int n);
    void setDataUnit(int i, const DataUnit& dataUnit);
    void setChild(int i, BTreeNode *child);
    NODISCARD int getN() const;
    NODISCARD bool getIsLeaf() const;
    NODISCARD DataUnit getDataUnit(int i) const;
    NODISCARD BTreeNode *getChild(int i) const;

    void insertNonFull(const DataUnit& dataUnit);
    void splitChild(int i, BTreeNode *oldNode);

    NODISCARD DataUnit search(int key) const;

    void edit(int key, const DataUnit& dataUnit);

    void remove(const DataUnit &dataUnit);
    void remove(int key);
    void merge(int i);
    void fill(int i);
    void takeFromPrev(int i);
    void takeFromNext(int i);

    void printBTree(int depth = 0);
    void writeToFile(std::ofstream &out) const;
    void readFromFile(std::ifstream &in);
};
