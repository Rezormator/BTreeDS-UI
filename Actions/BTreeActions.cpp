#include "BTreeActions.h"
#include "../DataUnit/DataUnit.h"
#include "../Input/Input.h"
#include <sstream>

#include "../Random/Random.h"

BTree *BTreeActions::tree;

void BTreeActions::setBTree(BTree *tree) {
    BTreeActions::tree = tree;
}

BTree *BTreeActions::getBtree() {
    return tree;
}

DataUnit BTreeActions::validateInput() {
    bool valid[3] = {true, true, true};
    const auto id = Input::getInputID()->getInputLine()->text().toInt(&valid[0]);
    const auto city = Input::getInputCity()->getInputLine()->text().toStdString();
    const auto population = Input::getInputPopulation()->getInputLine()->text().toInt(&valid[1]);
    const auto area = Input::getInputArea()->getInputLine()->text().toDouble(&valid[2]);
    for (const auto &valid_: valid) {
        if (!valid_) {
            Input::getResult()->getTextLabel()->setText("Invalid types");
            return {};
        }
    }
    DataUnit dataUnit(id, city, population, area);
    return dataUnit;
}

void BTreeActions::insertData() {
    const auto dataUnit = validateInput();
    if (dataUnit.getKey() == 0) {
        return;
    }
    if (tree->contain(dataUnit.getKey())) {
        Input::getResult()->getTextLabel()->setText("City with this ID already exist");
        return;
    }
    tree->insert(dataUnit);
    std::ostringstream oss;
    oss << "Inserted city: " << dataUnit.getValueS() << " with population: " << dataUnit.getValueI() << " and area: " <<
            dataUnit.getValueD() << " with id: " << dataUnit.getKey();
    const auto cityInfo = oss.str();
    Input::getResult()->getTextLabel()->setText(QString::fromStdString(cityInfo));
}

void BTreeActions::searchData() {
    bool valid;
    const auto id = Input::getInputID()->getInputLine()->text().toInt(&valid);
    if (!valid) {
        Input::getResult()->getTextLabel()->setText("Invalid types");
        return;
    }
    if (!tree->contain(id)) {
        Input::getResult()->getTextLabel()->setText("City with this ID dont exist");
        return;
    }
    const auto dataUnit = tree->search(id);
    std::ostringstream oss;
    oss << "City id: " << dataUnit.getKey() << "     City name: " << dataUnit.getValueS() << "     City population: " <<
            dataUnit.getValueI() << "     City area: " << dataUnit.getValueD();
    const auto cityInfo = oss.str();
    Input::getResult()->getTextLabel()->setText(QString::fromStdString(cityInfo));
}

void BTreeActions::editData() {
    const auto dataUnit = validateInput();
    if (dataUnit.getKey() == 0) {
        return;
    }
    if (!tree->contain(dataUnit.getKey())) {
        Input::getResult()->getTextLabel()->setText("City with this ID dont exist");
        return;
    }
    tree->edit(dataUnit.getKey(), dataUnit);
    std::ostringstream oss;
    oss << "Edit to city: " << dataUnit.getValueS() << " with population: " << dataUnit.getValueI() << " and area: " <<
            dataUnit.getValueD() << " with id: " << dataUnit.getKey();
    const auto cityInfo = oss.str();
    Input::getResult()->getTextLabel()->setText(QString::fromStdString(cityInfo));
}

void BTreeActions::deleteData() {
    bool valid;
    const auto id = Input::getInputID()->getInputLine()->text().toInt(&valid);
    if (!valid) {
        Input::getResult()->getTextLabel()->setText("Invalid types");
        return;
    }
    if (!tree->contain(id)) {
        Input::getResult()->getTextLabel()->setText("City with this ID dont exist");
        return;
    }
    tree->remove(id);
    std::ostringstream oss;
    oss << "Delete city with id: " << id;
    const auto deleteInfo = oss.str();
    Input::getResult()->getTextLabel()->setText(QString::fromStdString(deleteInfo));
}

void BTreeActions::fillData() {
    delete tree;
    tree = new BTree(10);
    const auto strings = Random::generateStrings();
    const auto ints = Random::generateInts();
    const auto doubles = Random::generateDoubles();
    for (int i = 0; i < COUNT; i++) {
        tree->insert(DataUnit(i + 1, strings[i], ints[i], doubles[i]));
    }
    Input::getResult()->getTextLabel()->setText("Tree filled with data");
}
