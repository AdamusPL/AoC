//
// Created by adamc on 09.03.2024.
//

#include "Day2.h"

void Day2::launch() {
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
