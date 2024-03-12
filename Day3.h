//
// Created by adamc on 09.03.2024.
//

#ifndef AOC1_DAY3_H
#define AOC1_DAY3_H

#include <fstream>
#include <iostream>
using namespace std;


class Day3 {
    char** readData();

    int rows;
    int columns;
    char** matrix;
public:
    void part1();

    void part2();
};


#endif //AOC1_DAY3_H
