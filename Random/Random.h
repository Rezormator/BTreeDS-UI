#pragma once

#include <string>
#include <vector>

constexpr int STRING_LENGTH = 10;
constexpr int COUNT = 10000;

class Random {
private:
    static std::string generateString(int length);
public:
    static std::vector<std::string> generateStrings(int count = COUNT);
    static std::vector<int> generateInts(int count = COUNT);
    static std::vector<double> generateDoubles(int count = COUNT);
};
