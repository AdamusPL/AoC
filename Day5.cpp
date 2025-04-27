//
// Created by adamc on 18.03.2024.
//

#include <iostream>
#include <algorithm>
#include "Day5.h"

namespace std {
    class thread;
}

void Day5::part1() {
    readData_part1();
    solve_part1();
}

void Day5::part2() {
    readData_part2();
    solve_part2();
}


void Day5::readData_part1() {
    fstream file;
    file.open("cmake-build-debug/data5.txt", ios::in);

    string data;

    //reading needed seeds
    string number = "";
    data = "";
    getline(file, data);
    for (char d: data) {
        if (isdigit(d)) {
            number += d;
        } else if (d == ' ') {
            if (!number.empty()) {
                needed.push_back(stoll(number));
            }
            number = "";
        }
    }

    needed.push_back(stoll(number));

    pair<pair<long long, long long>, long long> line;
    string type;
    //reading destination/source
    while (!file.eof()) {
        bool newType = false;

        //read line
        getline(file, data);

        //if it's blank line
        if (data.empty()) {
            continue;
        }

        //if it's new type of soil
        else if (!isdigit(data[0])) {
            newType = true;
            type = data;
            //read another line
            getline(file, data);
        }

        int i = 0;
        number = "";
        for (char d: data) {
            //if it's digit, then create string of number
            if (isdigit(d)) {
                number += d;
            }
            //if it's space, then add number to vector
            else if (d == ' ') {
                if (!number.empty()) {
                    if (i == 0) {
                        line.first.first = stoll(number);
                        i++;
                    } else {
                        line.first.second = stoll(number);
                        i++;
                    }
                }
                number = "";
            }
        }

        //leftover
        line.second = stoll(number);

        if (newType) {
            vector<pair<pair<long long, long long>, long long> > vector;
            vector.push_back(line);
            sourceAndDestination.emplace_back(type, vector);
        } else {
            for (auto &value: sourceAndDestination) {
                if (type == value.first) {
                    value.second.emplace_back(line);
                }
            }
        }
    }

    file.close();
}

void Day5::solve_part1() {
    vector<pair<long long, vector<long long> > > corresponding;

    //find minimum location
    long long min = LONG_LONG_MAX;

    for (auto &seed: needed) {
        for (auto &value: sourceAndDestination) {
            for (auto &inValue: value.second) {
                if (inValue.first.second <= seed && seed <= inValue.first.second + inValue.second - 1) {
                    seed = inValue.first.first + seed - inValue.first.second;
                    break;
                }
            }
        }

        if (seed < min) {
            min = seed;
        }
    }

    std::cout << "Min location: " << min << std::endl;
}

void Day5::readData_part2() {
    fstream file;
    file.open("cmake-build-debug/data5.txt", ios::in);

    string data;

    //reading needed seeds
    string number1 = "";
    string number2 = "";
    data = "";
    getline(file, data);
    int counter = 0;

    for (char d: data) {
        if (isdigit(d)) {
            if (counter % 2 == 0) {
                number1 += d;
            } else {
                number2 += d;
            }
        } else if (d == ' ') {
            if (!number1.empty()) {
                if (counter % 2 != 0) {
                    neededPart2.emplace_back(stoll(number1), stoll(number2));
                    number1 = "";
                    number2 = "";
                }
                counter++;
            }
        }
    }

    neededPart2.emplace_back(stoll(number1), stoll(number2));

    pair<pair<long long, long long>, long long> line;
    string type;

    string number = "";

    //reading destination/source
    while (!file.eof()) {
        bool newType = false;

        //read line
        getline(file, data);

        //if it's blank line
        if (data.empty()) {
            continue;
        }

        //if it's new type of soil
        else if (!isdigit(data[0])) {
            newType = true;
            type = data;
            //read another line
            getline(file, data);
        }

        int i = 0;
        number = "";
        for (char d: data) {
            //if it's digit, then create string of number
            if (isdigit(d)) {
                number += d;
            }
            //if it's space, then add number to vector
            else if (d == ' ') {
                if (!number.empty()) {
                    if (i == 0) {
                        line.first.first = stoll(number);
                        i++;
                    } else {
                        line.first.second = stoll(number);
                        i++;
                    }
                }
                number = "";
            }
        }

        //leftover
        line.second = stoll(number);

        if (newType) {
            vector<pair<pair<long long, long long>, long long> > vector;
            vector.push_back(line);
            sourceAndDestination.emplace_back(type, vector);
        } else {
            for (auto &value: sourceAndDestination) {
                if (type == value.first) {
                    value.second.emplace_back(line);
                }
            }
        }
    }

    file.close();
}

void Day5::solve_part2() {
    vector<thread> threads;
    long long globalMin = LONG_LONG_MAX;

    threads.reserve(neededPart2.size());
for (const auto &seedRange: neededPart2) {
        threads.emplace_back([this, seedRange, &globalMin]() {
            this->processSeeds(seedRange, this->sourceAndDestination, globalMin);
        });
    }

    for (auto &t: threads) {
        t.join();
    }

    std::cout << "Min location: " << globalMin << std::endl;
}

void Day5::processSeeds(
    pair<long long, long long> seedRange,
    const vector<pair<string, vector<pair<pair<long long, long long>, long long> > > > &sourceAndDestination,
    long long &globalMin
) {
    vector<pair<long long, vector<long long> > > corresponding;

    //find minimum location
    long long localMin = LONG_LONG_MAX;

    for (long long i = seedRange.first; i < seedRange.first + seedRange.second; i++) {
        long long seed = i;
        for (auto &value: sourceAndDestination) {
            for (auto &inValue: value.second) {
                if (inValue.first.second <= seed && seed <= inValue.first.second + inValue.second - 1) {
                    seed = inValue.first.first + seed - inValue.first.second;
                    break;
                }
            }
        }

        if (seed < localMin) {
            localMin = seed;
        }
    }

    lock_guard<mutex> guard(minMutex);
    if (localMin < globalMin) {
        globalMin = localMin;
    }
}
