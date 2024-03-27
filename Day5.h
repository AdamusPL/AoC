//
// Created by adamc on 18.03.2024.
//

#ifndef AOC1_DAY5_H
#define AOC1_DAY5_H

#include <fstream>
#include <vector>
using namespace std;

class Day5 {
    //first elem of pair is type of soil, second is pair: first - vector of sources, second - destinations
    vector<pair<string,vector<pair<pair<long long, long long>,long long>>>> sourceAndDestination;
    vector<long long> needed;
    void readData_part1();
    void solve_part1();

    vector<pair<long long, long long>> needed2;
    void readData_part2();
    void solve_part2();

public:
    void part1();


};


#endif //AOC1_DAY5_H
