//
// Created by adamc on 09.03.2024.
//

#include "Day1.h"

void Day1::part1() {
    fstream file;
    file.open("data1.txt",ios::in);

    string data;
    string solution;
    int sum = 0;

    while(!file.eof()){
        file >> data;
        solution = "";

        for(char i : data){
            if(i == '0' || i == '1' || i == '2' || i == '3' || i == '4'
               || i == '5' || i == '6' || i == '7' || i == '8' || i == '9'){
                if(solution.length() < 2){
                    solution += i;
                }

                else{
                    solution[1] = i;
                }

            }
        }

        if(solution.length() == 1){
            solution += solution[0];
        }

        sum += stoi(solution);


    }

    std::cout << sum << std::endl;
}

void Day1::part2() {
    vector<pair<string, char>> converter;
    converter.emplace_back("zero", '0');
    converter.emplace_back("one", '1');
    converter.emplace_back("two", '2');
    converter.emplace_back("three",'3');
    converter.emplace_back("four", '4');
    converter.emplace_back("five", '5');
    converter.emplace_back("six", '6');
    converter.emplace_back("seven", '7');
    converter.emplace_back("eight", '8');
    converter.emplace_back("nine", '9');

    fstream file;
    file.open("data1.txt",ios::in);

    string data;
    string solution;
    int sum = 0;

    while(!file.eof()){
        file >> data;
        solution = "";

        for(int i=0; i<data.length(); i++){

            for (auto & j : converter) {
                if(j.first.size() == 3 && i>=2){ //one two six
                    if(data[i-2] == j.first[0] && data[i-1] == j.first[1] && data[i] == j.first[2]){
                        if(solution.length() < 2){
                            solution += j.second;
                        }
                        else{
                            solution[1] = j.second;
                        }
                    }
                }

                else if(j.first.size() == 4 && i>=3) { //zero four five nine
                    if (data[i - 3] == j.first[0] && data[i - 2] == j.first[1] &&
                        data[i - 1] == j.first[2]
                        && data[i] == j.first[3]) {
                        if (solution.length() < 2) {
                            solution += j.second;
                        } else {
                            solution[1] = j.second;
                        }
                    }
                }

                else{ //three seven eight
                    if (data[i - 4] == j.first[0] && data[i - 3] == j.first[1] &&
                        data[i - 2] == j.first[2]
                        && data[i - 1] == j.first[3] && data[i] == j.first[4]) {

                        if (solution.length() < 2) {
                            solution += j.second;
                        } else {
                            solution[1] = j.second;
                        }
                    }

                }
            }


            if(data[i] == '0' || data[i] == '1' || data[i] == '2' || data[i] == '3' || data[i] == '4'
               || data[i] == '5' || data[i] == '6' || data[i] == '7' || data[i] == '8' || data[i] == '9'){

                if(solution.length() < 2){
                    solution += data[i];
                }

                else{
                    solution[1] = data[i];
                }

            }
        }

        if(solution.length() == 1){
            solution += solution[0];
        }

        sum += stoi(solution);


    }

    std::cout << sum << std::endl;
}