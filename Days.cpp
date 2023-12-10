//
// Created by adamc on 09/12/2023.
//

#include "Days.h"

void Days::day1_part1() {
    fstream file;
    file.open("data1.txt",ios::in);

    string data;
    string solution;
    int sum = 0;

    while(!file.eof()){
        file >> data;
        solution = "";

        for(int i=0; i<data.length(); i++){
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

void Days::day1_part2() {
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

            for (int j = 0; j < converter.size(); ++j) {
                if(converter[j].first.size() == 3 && i>=2){ //one two six
                    if(data[i-2] == converter[j].first[0] && data[i-1] == converter[j].first[1] && data[i] == converter[j].first[2]){
                        if(solution.length() < 2){
                            solution += converter[j].second;
                        }
                        else{
                            solution[1] = converter[j].second;
                        }
                    }
                }

                else if(converter[j].first.size() == 4 && i>=3) { //zero four five nine
                    if (data[i - 3] == converter[j].first[0] && data[i - 2] == converter[j].first[1] &&
                        data[i - 1] == converter[j].first[2]
                        && data[i] == converter[j].first[3]) {
                        if (solution.length() < 2) {
                            solution += converter[j].second;
                        } else {
                            solution[1] = converter[j].second;
                        }
                    }
                }

                else{ //three seven eight
                    if (data[i - 4] == converter[j].first[0] && data[i - 3] == converter[j].first[1] &&
                        data[i - 2] == converter[j].first[2]
                        && data[i - 1] == converter[j].first[3] && data[i] == converter[j].first[4]) {

                        if (solution.length() < 2) {
                            solution += converter[j].second;
                        } else {
                            solution[1] = converter[j].second;
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

void Days::day2(){
    fstream file;
    file.open("data2.txt",ios::in);
    string line;
    string number;
    int red = 12;
    int green = 13;
    int blue = 14;
    bool skip;
    int possible = 0;
//    vector<string> dictionary;
//    dictionary.push_back("red");
//    dictionary.push_back("green");
//    dictionary.push_back("blue");

    for (int numberOfGame = 1; numberOfGame <= 100; ++numberOfGame) {
        skip = false;
        getline(file, line, ':'); //Game nr:

        do {

            getline(file, line, ';'); //1 taking hand from bag

            for (int i = 0; i < line.size(); i++) {
                if(line[i]>=49 && line[i]<=57){
                    number+=line[i];
                }

                if(line[i] == 'r'){
                    if(stoi(number) > red){
                        skip = true;
                        continue;
                    }
                    number="";
                    while(line[i]!=',') i++;
                }

                else if(line[i] == 'g'){
                    if(stoi(number) > green){
                        skip = true;
                        continue;
                    }
                    number="";
                    while(line[i]!=',') i++;
                }

                else if(line[i] == 'b'){ //b
                    if(stoi(number) > blue){
                        skip = true;
                        continue;
                    }
                    number="";
                    while(line[i]!=',') i++;
                }
            }

        } while (line[line.size()-1] != '\n');

        if(!skip) possible++;

    }

    std::cout<<possible<<std::endl;
}