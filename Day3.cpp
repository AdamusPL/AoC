//
// Created by adamc on 09.03.2024.
//

#include <vector>
#include <algorithm>
#include "Day3.h"

void Day3::part1() {
    readData();

    string number;
    bool detected = false;
    bool count = false;
    int sum = 0;

    int indexOfFirstDigit;
    int indexOfLastDigit;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; ++j) {

            count = false;
            detected = false;
            number = "";

            while (matrix[i][j] >= '0' && matrix[i][j] <= '9') {
                if (!detected) {
                    indexOfFirstDigit = j;
                    detected = true;
                }
                number += matrix[i][j];
                indexOfLastDigit = j;
                j++;
            }

            int digitNow = indexOfFirstDigit;

            if (detected) {

                while (digitNow <= indexOfLastDigit) {

                    if (digitNow == indexOfFirstDigit) {

                        if (digitNow != 0 && matrix[i][digitNow - 1] != '.') {
                            count = true;
                        }

                        if (i != 0 && digitNow != 0 && matrix[i - 1][digitNow - 1] != '.') {
                            count = true;
                        }

                        if (i != rows - 1 && digitNow != 0 && matrix[i + 1][digitNow - 1] != '.') {
                            count = true;
                        }

                    }

                    if (i != 0 && matrix[i - 1][digitNow] != '.') {
                        count = true;
                    }

                    if (i != rows - 1 && matrix[i + 1][digitNow] != '.') {
                        count = true;
                    }

                    if (digitNow == indexOfLastDigit) {

                        if (digitNow != columns - 1 && matrix[i][digitNow + 1] != '.') {
                            count = true;
                        }

                        if (i != 0 && digitNow != columns - 1 && matrix[i - 1][digitNow + 1] != '.') {
                            count = true;
                        }

                        if (i != rows - 1 && digitNow != columns - 1 && matrix[i + 1][digitNow + 1] != '.') {
                            count = true;
                        }


                    }

                    digitNow++;
                }
            }

            if (count) {
                sum += stoi(number);
                number = "";
            }

        }
    }

    std::cout << sum << std::endl;

}

bool compare(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
    return a.first.second < b.first.second;
}

bool compareLocations(const pair<string, pair<int, int>> &a, const pair<string, pair<int, int>> &b) {
    // First, compare by the first int in the pair
    if (a.second.first != b.second.first) {
        return a.second.first < b.second.first;
    }
    // If the first ints are equal, compare by the second int in the pair
    return a.second.second < b.second.second;
}

bool comparator(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
    // First sort by the first integer inside the pair
    if (a.first.first != b.first.first)
        return a.first.first < b.first.first;
    // If the first integers are equal, sort by the second integer inside the pair
    return a.first.second < b.first.second;
}

void Day3::part2() {

    readData();

    //vector of number + location of star
    vector<pair<string, pair<int, int>>> locationsOfAdjacency;
    vector<pair<pair<int, int>, int>> amountOfStars;

    string number;
    bool detected = false;
    bool count = false;

    int indexOfFirstDigit;
    int indexOfLastDigit;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; ++j) {

            count = false;
            detected = false;
            number = "";

            while (matrix[i][j] >= '0' && matrix[i][j] <= '9') {
                if (!detected) {
                    indexOfFirstDigit = j;
                    detected = true;
                }
                number += matrix[i][j];
                indexOfLastDigit = j;
                j++;
            }

            int digitNow = indexOfFirstDigit;
            pair<int, int> locationOfStar;

            //if number is detected, check if it's adjacent to star
            if (detected) {

                while (digitNow <= indexOfLastDigit) {

                    if (digitNow == indexOfFirstDigit) {

                        if (digitNow != 0 && matrix[i][digitNow - 1] == '*') {
                            count = true;
                            locationOfStar = make_pair(i, digitNow - 1);
                        }

                        if (i != 0 && digitNow != 0 && matrix[i - 1][digitNow - 1] == '*') {
                            count = true;
                            locationOfStar = make_pair(i - 1, digitNow - 1);
                        }

                        if (i != rows - 1 && digitNow != 0 && matrix[i + 1][digitNow - 1] == '*') {
                            count = true;
                            locationOfStar = make_pair(i + 1, digitNow - 1);
                        }

                    }

                    if (i != 0 && matrix[i - 1][digitNow] == '*') {
                        count = true;
                        locationOfStar = make_pair(i - 1, digitNow);
                    }

                    if (i != rows - 1 && matrix[i + 1][digitNow] == '*') {
                        count = true;
                        locationOfStar = make_pair(i + 1, digitNow);
                    }

                    if (digitNow == indexOfLastDigit) {

                        if (digitNow != columns - 1 && matrix[i][digitNow + 1] == '*') {
                            count = true;
                            locationOfStar = make_pair(i, digitNow + 1);
                        }

                        if (i != 0 && digitNow != columns - 1 && matrix[i - 1][digitNow + 1] == '*') {
                            count = true;
                            locationOfStar = make_pair(i - 1, digitNow + 1);
                        }

                        if (i != rows - 1 && digitNow != columns - 1 && matrix[i + 1][digitNow + 1] == '*') {
                            count = true;
                            locationOfStar = make_pair(i + 1, digitNow + 1);
                        }

                    }

                    digitNow++;
                }
            }

            //if number is adjacent to star, we put it to vector with location of adjacent star
            if (count) {

                pair<string, pair<int, int>> value = make_pair(number, locationOfStar);
                locationsOfAdjacency.emplace_back(value);

                //count how many numbers are adjacent to star
                bool exist = false;
                for (auto &inValue: amountOfStars) {
                    if (value.second.first == inValue.first.first && value.second.second == inValue.first.second) {
                        inValue.second++;
                        exist = true;
                        break;
                    }
                }
                if (!exist) {
                    amountOfStars.emplace_back(value.second, 1);
                }
                number = "";
            }

        }
    }

    //sort amountOfStars
    sort(amountOfStars.begin(), amountOfStars.end(), compare);

    //remove stars which are not adjacent to only 2 numbers
    vector<pair<pair<int, int>, int>> adjacentTo2Stars;

    for (auto &value: amountOfStars) {
        if (value.second == 2) {
            adjacentTo2Stars.emplace_back(value);
        }
    }

    for (auto it = locationsOfAdjacency.begin(); it != locationsOfAdjacency.end(); it++) {
        bool isInArray = false;
        for (auto &value: adjacentTo2Stars) {
            if ((*it).second.first == value.first.first && (*it).second.second == value.first.second){
                isInArray = true;
                break;
            }
        }
        if(!isInArray){
            it = locationsOfAdjacency.erase(it);
        }
    }


    sort(adjacentTo2Stars.begin(), adjacentTo2Stars.end(), comparator);
    //sort locationsOfAdjacency
    sort(locationsOfAdjacency.begin(), locationsOfAdjacency.end(), compareLocations);

    int sum = 0;
    int multiplicity = 1;

    //sum up multiplicity of numbers which are adjacent to only 2 numbers
    for (auto &inValue: adjacentTo2Stars) {
        int x = inValue.first.first;
        int y = inValue.first.second;
        for (auto value = locationsOfAdjacency.begin(); value != locationsOfAdjacency.end(); /*NOTHING*/) {
            if (inValue.first.first != (*value).second.first || inValue.first.second != (*value).second.second) {
                sum += multiplicity;
                multiplicity = 1;
                break;
            }
            multiplicity *= stoi(value->first);
            value = locationsOfAdjacency.erase(value);
        }

    }

    sum += multiplicity;

    cout << "Sum = " << sum << endl;

}

char **Day3::readData() {
    fstream file;
    string line;
    file.open("cmake-build-debug/data3.txt", ios::in);

    rows = 0;

    //count rows and columns in txt file
    while (!file.eof()) {
        getline(file, line);
        rows++;
    }

    columns = line.size();

    file.close();
    file.open("cmake-build-debug/data3.txt", ios::in);

    //read all chars from txt file to matrix
    matrix = new char *[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new char[columns];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}
