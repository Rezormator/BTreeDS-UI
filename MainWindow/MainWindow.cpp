#include "MainWindow.h"
#include <QKeyEvent>
#include <QWidget>
#include <QLabel>

#include "../Actions/BTreeActions.h"
#include "../Button/Button.h"
#include "../InputLine/InputLine.h"
#include "../Input/Input.h"

MainWindow::MainWindow() {
    setWindowTitle("B-Tree Data Structure"); // 1536 816
    setupUI();
}

void MainWindow::setupUI() {
    const auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    const auto insertButton = new Button("Insert", this, 40, 40, 112);
    connect(insertButton->getButton(), &QPushButton::clicked, this, &BTreeActions::insertData);
    const auto searchButton = new Button("Search", this, 192, 40);
    connect(searchButton->getButton(), &QPushButton::clicked, this, &BTreeActions::searchData);
    const auto editButton = new Button("Edit", this, 341, 40);
    connect(editButton->getButton(), &QPushButton::clicked, this, &BTreeActions::editData);
    const auto deleteButton = new Button("Delete", this, 490, 40);
    connect(deleteButton->getButton(), &QPushButton::clicked, this, &BTreeActions::deleteData);
    const auto fillButton = new Button("Fill", this, 639, 40);
    connect(fillButton->getButton(), &QPushButton::clicked, this, &BTreeActions::fillData);
    const auto exitButton = new Button("Exit", this, 788, 40, 708, 716);
    connect(exitButton->getButton(), &QPushButton::clicked, this, &MainWindow::close);

    const auto inputID = new InputLine("Enter city ID...", this, 40, 130);
    const auto inputCity = new InputLine("Enter city name...", this, 40, 220);
    const auto inputPopulation = new InputLine("Enter city population...", this, 40, 310);
    const auto inputArea = new InputLine("Enter city area...", this, 40, 400);
    const auto result = new TextLabel("", this, 40, 490, 708, 50);
    Input::setInputs(inputID, inputCity, inputPopulation, inputArea, result);

    const auto adds = new TextLabel("", this, 40, 580, 708, 166);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    BTreeActions::getBtree()->writeTreeToFile("../BTree.txt");
    delete BTreeActions::getBtree();
}
