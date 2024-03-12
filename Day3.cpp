//
// Created by adamc on 09.03.2024.
//

#include "Day3.h"

void Day3::part1() {
    readData();

    string number;
    bool detected = false;
    bool count = false;
    int sum = 0;

    int indexOfFirstDigit;
    int indexOfLastDigit;

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; ++j) {

            count = false;
            detected = false;
            number = "";

            while(matrix[i][j] >= '0' && matrix[i][j] <= '9'){
                if(!detected){
                    indexOfFirstDigit = j;
                    detected = true;
                }
                number+=matrix[i][j];
                indexOfLastDigit = j;
                j++;
            }

            int digitNow = indexOfFirstDigit;

            if(detected) {

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

                    if(digitNow == indexOfLastDigit) {

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

            if(count) {
                sum += stoi(number);
                number = "";
            }

        }
    }

    std::cout << sum << std::endl;

}

void Day3::part2(){

    readData();

    string number;
    bool detected = false;
    bool count = false;
    int sum = 0;

    int indexOfFirstDigit;
    int indexOfLastDigit;

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; ++j) {

            count = false;
            detected = false;
            number = "";

            while(matrix[i][j] >= '0' && matrix[i][j] <= '9'){
                if(!detected){
                    indexOfFirstDigit = j;
                    detected = true;
                }
                number+=matrix[i][j];
                indexOfLastDigit = j;
                j++;
            }

            int digitNow = indexOfFirstDigit;

            if(detected) {

                while (digitNow <= indexOfLastDigit) {

                    if (digitNow == indexOfFirstDigit) {

                        if (digitNow != 0 && matrix[i][digitNow - 1] == '*') {
                            count = true;
                        }

                        if (i != 0 && digitNow != 0 && matrix[i - 1][digitNow - 1] == '*') {
                            count = true;
                        }

                        if (i != rows - 1 && digitNow != 0 && matrix[i + 1][digitNow - 1] == '*') {
                            count = true;
                        }

                    }

                    if (i != 0 && matrix[i - 1][digitNow] == '*') {
                        count = true;
                    }

                    if (i != rows - 1 && matrix[i + 1][digitNow] == '*') {
                        count = true;
                    }

                    if(digitNow == indexOfLastDigit) {

                        if (digitNow != columns - 1 && matrix[i][digitNow + 1] == '*') {
                            count = true;
                        }

                        if (i != 0 && digitNow != columns - 1 && matrix[i - 1][digitNow + 1] == '*') {
                            count = true;
                        }

                        if (i != rows - 1 && digitNow != columns - 1 && matrix[i + 1][digitNow + 1] == '*') {
                            count = true;
                        }


                    }

                    digitNow++;
                }
            }

            if(count) {
                sum += stoi(number);
                number = "";
            }

        }
    }

    std::cout << sum << std::endl;

}

char** Day3::readData(){
    fstream file;
    string line;
    file.open("data3.txt",ios::in);

    rows = 0;

    //count rows and columns in txt file
    while(!file.eof()){
        getline(file, line);
        rows++;
    }

    columns = line.size();

    file.close();
    file.open("data3.txt",ios::in);

    //read all chars from txt file to matrix
    matrix = new char*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new char[columns];
    }

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < columns; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}
