#include "DataUnit.h"

#include <utility>

DataUnit::DataUnit(const int key, std::string svalue, const int ivalue, const double dvalue)
: key(key), svalue(std::move(svalue)), ivalue(ivalue), dvalue(dvalue) {
}

DataUnit::DataUnit() : key(0), svalue(" "), ivalue(0), dvalue(0) {
}

void DataUnit::setValueS(const std::string &value) {
    svalue = value;
}

void DataUnit::setValueI(const int value) {
    ivalue = value;
}

void DataUnit::setValueD(const double value) {
    dvalue = value;
}

int DataUnit::getKey() const {
    return key;
}

std::string DataUnit::getValueS() const {
    return svalue;
}

int DataUnit::getValueI() const {
    return ivalue;
}

double DataUnit::getValueD() const {
    return dvalue;
}

bool operator<(const DataUnit &lhs, const DataUnit &rhs) {
    return lhs.key < rhs.key;
}