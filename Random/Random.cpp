#include "Random.h"
#include <random>
#include <set>

std::string Random::generateString(const int length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);
    std::string randomString;

    for (int i = 0; i < length; ++i) {
        const auto index = distribution(generator);
        randomString += characters[index];
    }

    return randomString;
}

std::vector<std::string> Random::generateStrings(const int count) {
    std::vector<std::string> strings;
    for (int i = 0; i < count; i++) {
        std::string randomString;
        strings.push_back(generateString(STRING_LENGTH));
    }
    return strings;
}

std::vector<int> Random::generateInts(const int count) {
    std::vector<int> ints;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(1, count * 10);
    while (ints.size() < count) {
        int randomNum = distribution(generator);
        ints.push_back(randomNum);
    }
    return ints;
}

std::vector<double> Random::generateDoubles(const int count) {
    std::vector<double> doubles;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(1, count * 5);
    while (doubles.size() < count) {
        double randomNum = distribution(generator);
        doubles.push_back(randomNum);
    }
    return doubles;
}
