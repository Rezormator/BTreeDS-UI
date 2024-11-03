#pragma once

#include "../BTreeNode/BTreeNode.h"

class BTree {
private:
    int t;
    BTreeNode *root;
public:
    explicit BTree(int t);
    ~BTree();
    void insert(int key, const std::string &svalue, int ivalue, double dvalue);
    void insert(const DataUnit &dataUnit);
    NODISCARD bool contain(int key) const;
    NODISCARD DataUnit search(int key) const;
    void edit(int key, const DataUnit& dataUnit);
    void remove(const DataUnit &dataUnit);
    void remove(int key);
    void print();
    bool writeTreeToFile(const std::string &filename) const;
    bool readTreeFromFile(const std::string &filename);
};
