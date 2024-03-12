//
// Created by adamc on 09.03.2024.
//

#include "Day6.h"

void Day6::part1() {

    fstream file;
    file.open("data6.txt",ios::in);

    string data;
    file >> data;
    int number;
    std::vector<int> time;
    for(int i=0; i<4; i++){
        file >> number;
        time.push_back(number);
    }
    file >> data;
    std::vector<int> distance;
    for(int i=0; i<4; i++){
        file >> number;
        distance.push_back(number);
    }

    std::vector<int> options;
    int result = 1;

    for(int i=0; i<time.size(); i++){
        int k = time[i];
        int methods = 0;
        for(int j=0; j<time[i]+1; j++){
            if(j*k > distance[i]){
                methods++;
            }
            k--;
        }
        result*=methods;
    }

    std::cout << result << std::endl;

    file.close();

}

void Day6::part2(){

    fstream file;
    file.open("data6.txt",ios::in);

    string data;
    file >> data;
    string timeString;
    for(int i=0; i<4; i++){
        file >> data;
        timeString+=data;
    }

    double time = stod(timeString);

    file >> data;
    string distanceString;
    for(int i=0; i<4; i++){
        file >> data;
        distanceString+=data;
    }

    double distance = stod(distanceString);

    int methods = 0;
    double k=time;
    for(double j=0; j<time+1; j++){
        if(j*k > distance){
            methods++;
        }
        k--;
    }

    std::cout << methods << std::endl;

}
