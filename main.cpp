#include <QApplication>
#include "Actions/BTreeActions.h"
#include "BTree/BTree.h"
#include "MainWindow/MainWindow.h"

int main(int argc, char *argv[]) {
    const auto tree = new BTree(10);
    tree->readTreeFromFile("../BTree.txt");
    BTreeActions::setBTree(tree);
    QApplication app(argc, argv);
    MainWindow window;
    window.showMaximized();
    return QApplication::exec();
}