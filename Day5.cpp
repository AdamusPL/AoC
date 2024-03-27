//
// Created by adamc on 18.03.2024.
//

#include <iostream>
#include <algorithm>
#include "Day5.h"

void Day5::part1() {

    readData_part1();
    solve_part1();

}

void Day5::readData_part1() {
    fstream file;
    file.open("data5.txt", ios::in);

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
            vector<pair<pair<long long, long long>, long long>> vector;
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

void Day5::solve_part1(){

    //sort seeds which we want to find
    sort(needed.begin(), needed.end());

    vector<pair<long long, vector<long long>>> corresponding;

    for (auto &seed: needed) {

        vector<long long> cor;
        corresponding.emplace_back(seed, cor);
        auto &someValue = corresponding[corresponding.size() - 1];

        for (auto &value: sourceAndDestination) {

            bool found = false;

            for (auto &inValue: value.second) {
                if (inValue.first.second <= seed && seed <= inValue.first.second + inValue.second - 1){
                    seed = inValue.first.first + seed - inValue.first.second;
                    someValue.second.push_back(seed);
                    found = true;
                    break;
                }
            }

            if(!found){
                someValue.second.emplace_back(seed);
            }

        }
    }

    //find minimum location
    long long min = LONG_LONG_MAX;

    for (auto &value: corresponding) {
        if (value.second[value.second.size() - 1] < min) {
            min = value.second[value.second.size() - 1];
        }
    }

    std::cout << "Min location: " << min << std::endl;

}

void readData_part2(){

}
