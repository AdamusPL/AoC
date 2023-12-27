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
    string numberOfCubes;
    int red = 12;
    int green = 13;
    int blue = 14;
    int minR = 0, minG = 0, minB = 0;
    int power=0;
    bool skip = false;
    bool took = false;
    int sumOfIDs = 0;

    for (int numberOfGame = 1; numberOfGame <= 100; ++numberOfGame) {

        skip = false;
        getline(file,line);
        line+=',';
        number="";
        minR = 0;
        minG = 0;
        minB = 0;

        int i=0;
        while(line[i]!=':'){
            if(line[i] >= '0' && line[i] <= '9'){
                number+=line[i];
            }
            i++;
        }

        while(i!=line.size()-1) {
            if (line[i] >= '0' && line[i] <= '9') {
                numberOfCubes += line[i];
            }
            else if (line[i] == 'r') {
                if (stoi(numberOfCubes) > red) {
                    skip = true;
                }
                took = true;

                if(minR < stoi(numberOfCubes)){
                    minR = stoi(numberOfCubes);
                }

            } else if (line[i] == 'g') {
                if (stoi(numberOfCubes) > green) {
                    skip = true;
                }
                took = true;

                if(minG < stoi(numberOfCubes)){
                    minG = stoi(numberOfCubes);
                }

            } else if (line[i] == 'b') {
                if (stoi(numberOfCubes) > blue) {
                    skip = true;
                }
                took = true;
                if(minB < stoi(numberOfCubes)){
                    minB = stoi(numberOfCubes);
                }
            }

            i++;

            if(took){
                while(line[i]!=',' && line[i]!=';'){
                    i++;
                }
                numberOfCubes = "";
            }

            took = false;

        }

        if(!skip) {
            sumOfIDs += stoi(number);
        }

        power += minR*minG*minB;

    }

    std::cout << sumOfIDs << std::endl;
    std::cout << power << std::endl;
}