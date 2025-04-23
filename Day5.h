//
// Created by adamc on 18.03.2024.
//

#ifndef AOC1_DAY5_H
#define AOC1_DAY5_H

#include <fstream>
#include <vector>
#include <climits>
#include <thread>
#include <mutex>
using namespace std;

class Day5 {
    mutex minMutex;
    //first elem of pair is type of soil, second is pair: first - vector of sources, second - destinations
    vector<pair<string,vector<pair<pair<long long, long long>,long long>>>> sourceAndDestination;
    vector<long long> needed;
    vector<pair<long long, long long>> neededPart2;
    void readData_part1();
    void solve_part1();

    vector<pair<long long, long long>> needed2;
    void readData_part2();
    void solve_part2();
    void processSeeds(pair<long long, long long>,
        const vector<pair<string, vector<pair<pair<long long, long long>, long long>>>>&,
        long long&);

public:
    void part1();
    void part2();
};


#endif //AOC1_DAY5_H
