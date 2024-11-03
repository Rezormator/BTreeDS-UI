#include "BTreeNode.h"
#include <iostream>
#include <fstream>

BTreeNode::BTreeNode(const int t, const bool leaf) : t(t), n(0), leaf(leaf) {
    data.resize(2 * t - 1);
    children.resize(2 * t, nullptr);
}

BTreeNode::~BTreeNode() {
    for (const auto &child : children) {
        if (child == nullptr) {
            delete child;
        }
    }
}

void BTreeNode::setN(const int n) {
    this->n = n;
}

void BTreeNode::setDataUnit(const int i, const DataUnit &dataUnit) {
    data[i] = dataUnit;
}

void BTreeNode::setChild(const int i, BTreeNode *child) {
    children[i] = child;
}

int BTreeNode::getN() const {
    return n;
}

bool BTreeNode::getIsLeaf() const {
    return leaf;
}

DataUnit BTreeNode::getDataUnit(const int i) const {
    return data[i];
}

BTreeNode *BTreeNode::getChild(const int i) const {
    return children[i];
}

void BTreeNode::insertNonFull(const DataUnit &dataUnit) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && dataUnit < data[i]) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = dataUnit;
        n = n + 1;
    }
    else {
        while (i >= 0 && dataUnit < data[i]) {
            i--;
        }
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (data[i + 1] < dataUnit) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(dataUnit);
    }
}

void BTreeNode::splitChild(const int i, BTreeNode *oldNode) {
    const auto newNode = new BTreeNode(oldNode->t, oldNode->leaf);
    newNode->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        newNode->data[j] = oldNode->data[j + t];
    }
    if (oldNode->leaf == false) {
        for (int j = 0; j < t; j++) {
            newNode->children[j] = oldNode->children[j + t];
        }
    }

    oldNode->n = t - 1;
    for (int j = n; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }

    children[i + 1] = newNode;
    for (int j = n - 1; j >= i; j--) {
        data[j + 1] = data[j];
    }

    data[i] = oldNode->data[t - 1];
    n = n + 1;
}

DataUnit BTreeNode::search(const int key) const {
    int i = 0;
    while (i < n && key > data[i].getKey()) {
        i++;
    }

    if (i < n && data[i].getKey() == key) {
        return data[i];
    }
    if (leaf) {
        return {};
    }

    return children[i]->search(key);
}

void BTreeNode::edit(const int key, const DataUnit& dataUnit) {
    int i = 0;
    while (i < n && key > data[i].getKey()) {
        i++;
    }

    if (i < n && data[i].getKey() == key) {
        data[i].setValueS(dataUnit.getValueS());
        data[i].setValueI(dataUnit.getValueI());
        data[i].setValueD(dataUnit.getValueD());
    }

    if (!leaf) {
        children[i]->edit(key, dataUnit);
    }
}

void BTreeNode::remove(const DataUnit &dataUnit) {
    remove(dataUnit.getKey());
}

void BTreeNode::remove(const int key) {
    int i = 0;
    while (i < n && data[i].getKey() < key) {
        i++;
    }

    if (i < n && data[i].getKey() == key) {
        if (leaf) {
            for (int j = i + 1; j < n; j++) {
                data[j - 1] = data[j];
            }
            n--;
        }
        else {
            if (children[i]->n >= t) {
                const auto newDataUnit = children[i]->data[children[i]->n - 1];
                data[i] = newDataUnit;
                children[i]->remove(newDataUnit);
            }
            else if (children[i + 1]->n >= t) {
                const auto newDataUnit = children[i + 1]->data[0];
                data[i] = newDataUnit;
                children[i + 1]->remove(newDataUnit);
            }
            else {
                merge(i);
                children[i]->remove(key);
            }
        }
    }
    else {
        if (children[i]->n < t) {
            fill(i);
        }
        children[i]->remove(key);
    }
}

void BTreeNode::merge(const int i) {
    const auto child = children[i];
    const auto sibling = children[i + 1];

    child->data[child->n] = data[i];
    child->n++;
    for (int j = 0; j < sibling->n; j++) {
        child->data[child->n + j] = sibling->data[j];
    }

    if (!child->leaf) {
        for (int j = 0; j <= sibling->n; j++) {
            child->children[child->n + j + 1] = sibling->children[j];
        }
    }

    child->n += sibling->n;

    for (int j = i + 1; j < n; j++) {
        data[j - 1] = data[j];
    }

    for (int j = i + 2; j <= n; j++) {
        children[j - 1] = children[j];
    }

    n--;
    delete sibling;
}

void BTreeNode::fill(const int i) {
    if (i != 0 && children[i - 1]->n >= t) {
        takeFromPrev(i);
    }
    else if (i != n && children[i + 1]->n >= t) {
        takeFromNext(i);
    }
    else {
        if (i != n) {
            merge(i);
        }
        else {
            merge(i - 1);
        }
    }
}

void BTreeNode::takeFromPrev(const int i) {
    const auto child = children[i];
    const auto sibling = children[i - 1];

    for (int j = child->n - 1; j >= 0; j--) {
        child->data[j + 1] = child->data[j];
    }
    if (!child->leaf) {
        for (int j = child->n; j >= 0; j--) {
            child->children[j + 1] = child->children[j];
        }
    }
    child->data[0] = data[i - 1];
    child->n++;
    if (!child->leaf) {
        child->children[0] = sibling->children[sibling->n];
    }
    child->n++;

    data[i - 1] = sibling->data[sibling->n - 1];

    sibling->n--;
}

void BTreeNode::takeFromNext(const int i) {
    const auto child = children[i];
    const auto sibling = children[i + 1];

    child->data[child->n] = data[i];
    if (!sibling->leaf) {
        child->children[child->n + 1] = sibling->children[0];
    }
    child->n++;

    data[i] = sibling->data[0];

    for (int j = 1; j < sibling->n; j++) {
        sibling->data[j - 1] = sibling->data[j];
    }
    if (!sibling->leaf) {
        for (int j = 1; j <= sibling->n; j++) {
            sibling->children[j - 1] = sibling->children[j];
        }
    }
    sibling->n--;
}

void BTreeNode::printBTree(const int depth) {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) {
            children[i]->printBTree(depth + 1);
        }
        for (int j = 0; j < depth; j++) {
            std::cout << "           ";
        }
        std::cout << '(' << data[i].getKey() << ' ' << data[i].getValueS() << ")\n";
    }
    if (!leaf) {
        children[i]->printBTree(depth + 1);
    }
}

void BTreeNode::writeToFile(std::ofstream &out) const {
    out << n << "\n";
    for (int i = 0; i < n; i++) {
        out << data[i].getKey() << " ";
        out << data[i].getValueS() << " ";
        out << data[i].getValueI() << " ";
        out << data[i].getValueD() << "\n";
    }
    out << leaf << "\n";

    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            children[i]->writeToFile(out);
        }
    }
}

void BTreeNode::readFromFile(std::ifstream &in) {
    in >> n;

    for (int i = 0; i < n; i++) {
        int key;
        std::string svalue;
        int ivalue;
        double dvalue;

        in >> key >> svalue >> ivalue >> dvalue;
        data[i] = DataUnit(key, svalue, ivalue, dvalue);
    }

    bool isLeaf;
    in >> isLeaf;
    leaf = isLeaf;

    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            children[i] = new BTreeNode(t, leaf);
            children[i]->readFromFile(in);
        }
    }
}
