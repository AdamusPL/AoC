//
// Created by adamc on 09/12/2023.
//

#include <cmath>
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

void Days::day3(){
    fstream file;
    string line;
    file.open("data3.txt",ios::in);

    int rows = 0;

    //count rows and columns in txt file
    while(!file.eof()){
        getline(file, line);
        rows++;
    }

    int columns = line.size();

    file.close();
    file.open("data3.txt",ios::in);

    //read all chars from txt file to matrix
    char matrix[rows][columns];
    int indexOfFirstDigit;
    int indexOfLastDigit;

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; ++j) {
            file >> matrix[i][j];
        }
    }

    string number;
    bool detected=false;
    bool count = true;
    int sum = 0;

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; ++j) {

            count = true;
            detected = false;
            number = "";

            while(matrix[i][j] >= '0' && matrix[i][j] <= '9'){
                if(!detected){
                    indexOfFirstDigit = j;
                    detected = true;
                }
                number+=matrix[i][j];
                j++;
                indexOfLastDigit = j;
            }

            if(detected){
                if(matrix[i][indexOfFirstDigit-1] != '.' || matrix[i-1][indexOfFirstDigit-1] != '.' ||
                matrix[i+1][indexOfFirstDigit-1] != '.'){
                    count = false;
                }

                while(indexOfFirstDigit!=indexOfLastDigit+1){

                    if(matrix[i-1][indexOfFirstDigit] != '.' || matrix[i+1][indexOfFirstDigit] != '.') {
                        count = false;
                    }

                    indexOfFirstDigit++;
                }

                if(matrix[i][indexOfFirstDigit+1] != '.' || matrix[i+1][indexOfFirstDigit+1] != '.' ||
                   matrix[i-1][indexOfFirstDigit+1] != '.'){
                    count = false;
                }

                if(count) {
                    sum += stoi(number);
                    number = "";
                }

            }

        }
    }

    std::cout << sum << std::endl;
    file.close();


}

void Days::day4(){
    fstream file;
    string data;
    int sumOfPoints = 0;
    int matches = 0;
    int sumOfScratchCards = 0;
    int matchesPrev = 0;
    file.open("data4.txt",ios::in);
    vector<int> winningNumbers;
    vector<int> myNumbers;

    vector<pair<int, int>> numberOfCopies; //<trafione, ilosc>

    for(int i=0; i<223; i++){
        numberOfCopies.emplace_back(0,1);
    }

    file >> data;

    while(!file.eof()) {

        //taking out garbage
        file >> data;
        string number;
        for(int i=0; i<data.size(); i++){
            if(data[i] >= '0' && data[i] <= '9') number+=data[i];
        }
//        std::cout << data << std::endl;
        matches = 0;


        while(!file.eof()){
            file >> data;
            if(data.find('|') != std::string::npos){
                break;
            }
            winningNumbers.push_back(stoi(data));
        }

        while(!file.eof()){
            file >> data;
            if(data.find("Card") != std::string::npos){
                break;
            }
            myNumbers.push_back(stoi(data));
        }

        for(int i=0; i<myNumbers.size(); i++){
            for (int j = 0; j < winningNumbers.size(); ++j) {
                if(myNumbers[i] == winningNumbers[j]){
                    matches++;
                    break;
                }
            }
        }

        int prevMatches = numberOfCopies[stoi(number)-1].second;

        for(int i=stoi(number); i<matches+stoi(number); i++){
            for(int j=0; j<prevMatches; j++) {
                numberOfCopies[i].second++;
            }
        }

        if(matches>0) {
            sumOfPoints += pow(2, matches - 1);
        }

        myNumbers.clear();
        winningNumbers.clear();
        number = "";
    }

    for(int i=0; i<numberOfCopies.size(); i++){
        cout<<numberOfCopies[i].second<<endl;
        sumOfScratchCards+=numberOfCopies[i].second;
    }

    cout << sumOfPoints << endl;
    cout << sumOfScratchCards << endl;

    file.close();
}