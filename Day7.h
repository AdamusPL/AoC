//
// Created by adamc on 19.03.2024.
//

#ifndef AOC1_DAY7_H
#define AOC1_DAY7_H

#include <fstream>
#include <iostream>
using namespace std;

class Day7 {
    void kindChecker(string, vector<pair<pair<string, int>, int>>&, pair<string, int>);
    char checkWhichCardIsWorse(char, char);
    string kindsOfCards;
    //hand+value
    vector<pair<string, int>> cards;
    void readData();
public:
    Day7();
    void part1();
    void part2();
};


#endif //AOC1_DAY7_H
