#pragma once

#include <string>
#include "../Utils.h"

class DataUnit {
    friend bool operator<(const DataUnit &lhs, const DataUnit &rhs);
private:
    int key;
    std::string svalue;
    int ivalue;
    double dvalue;
public:
    DataUnit(int key, std::string svalue, int ivalue, double dvalue);
    DataUnit();
    void setValueS(const std::string &value);
    void setValueI(int value);
    void setValueD(double value);
    NODISCARD int getKey() const;
    NODISCARD std::string getValueS() const;
    NODISCARD int getValueI() const;
    NODISCARD double getValueD() const;
};
