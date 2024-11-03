#pragma once

#include "../BTree/BTree.h"

class BTreeActions {
private:
    static BTree *tree;
    static DataUnit validateInput();
public:
    static void setBTree(BTree *tree);
    NODISCARD static BTree *getBtree();
    static void insertData();
    static void searchData();
    static void editData();
    static void deleteData();
    static void fillData();
};
