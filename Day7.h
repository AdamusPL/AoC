//
// Created by adamc on 19.03.2024.
//

#ifndef AOC1_DAY7_H
#define AOC1_DAY7_H

#include <fstream>
#include <iostream>
using namespace std;

class Day7 {
    pair<char, int> kindChecker(string);
    char checkWhichCardIsBetter(char, char);
    string kindsOfCards;
public:
    Day7();
    void part1();
};


#endif //AOC1_DAY7_H
