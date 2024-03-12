//
// Created by adamc on 09.03.2024.
//

#ifndef AOC1_DAY8_H
#define AOC1_DAY8_H

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Day8 {
    string node;
    string left;
    string right;
    string directions;
    string someData;
    int moves = 0;
    std::vector<std::pair<string, std::pair<string, string>>> letters;
    pair<string, pair<string, string>> find(string, vector<std::pair<string, std::pair<string, string>>>);
    void readData();
    int LCM(int, int);
    int GCD(int, int);

public:
    void part1();
    void part2();
};


#endif //AOC1_DAY8_H
