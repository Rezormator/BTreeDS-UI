#include "BTree.h"
#include <fstream>

BTree::BTree(const int t) : t(t), root(nullptr) {
}

BTree::~BTree() {
    delete root;
}

void BTree::insert(const int key, const std::string &svalue, const int ivalue, const double dvalue) {
    insert(DataUnit(key, svalue, ivalue, dvalue));
}

void BTree::insert(const DataUnit &dataUnit) {
    if (root == nullptr) {
        root = new BTreeNode(t);
        root->setDataUnit(0, dataUnit);
        root->setN(1);
    }
    else if (root->getN() == 2 * t - 1) {
        const auto newRoot = new BTreeNode(t, false);
        newRoot->setChild(0, root);
        newRoot->splitChild(0, root);

        int i = 0;
        if (newRoot->getDataUnit(0) < dataUnit) {
            i++;
        }
        newRoot->getChild(i)->insertNonFull(dataUnit);
        root = newRoot;
    }
    else {
        root->insertNonFull(dataUnit);
    }
}

bool BTree::contain(const int key) const {
    if (root == nullptr) {
        return false;
    }
    return root->search(key).getValueS() != " ";
}

DataUnit BTree::search(const int key) const {
    return root->search(key);
}

void BTree::edit(const int key, const DataUnit& dataUnit) {
    root->edit(key, dataUnit);
}

void BTree::remove(const DataUnit &dataUnit) {
    remove(dataUnit.getKey());
}

void BTree::remove(const int key) {
    root->remove(key);
    if (root->getN() == 0) {
        if (root->getIsLeaf()) {
            root = nullptr;
        } else {
            root = root->getChild(0);
        }
    }
}

void BTree::print() {
    if (root != nullptr) {
        root->printBTree();
    }
}

bool BTree::writeTreeToFile(const std::string &filename) const {
    std::ofstream out(filename);
    if (out.is_open()) {
        if (root != nullptr) {
            root->writeToFile(out);
        }
        out.close();
        return true;
    }
    return false;
}

bool BTree::readTreeFromFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file && file.peek() == std::ifstream::traits_type::eof()) {
        return false;
    }
    std::ifstream in(filename);
    if (in.is_open()) {
        if (root != nullptr) {
            delete root;
        }
        root = new BTreeNode(t);
        root->readFromFile(in);
        in.close();
        return true;
    }
    return false;
}
