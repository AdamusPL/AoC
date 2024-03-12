//
// Created by adamc on 09.03.2024.
//

#include "Day8.h"

void Day8::part1(){

    readData();

    std::pair<string, std::pair<string, string>> actualNode;

    for(std::pair<string, std::pair<string, string>> element : letters){
        if(element.first=="AAA"){
            actualNode = element;
            break;
        }
    }

    bool stop = false;

    while(true){

        for(char direction : directions){

            if(direction=='L'){
                actualNode = find(actualNode.second.first, letters);
            }
            else{ //P
                actualNode = find(actualNode.second.second, letters);
            }

            moves++;

            if(actualNode.first=="ZZZ"){
                stop = true;
                break;
            }

        }

        if(stop){
            break;
        }

    }


    std::cout << moves << std::endl;
}

void Day8::part2(){

    readData();

    std::pair<string, std::pair<string, string>> actualNode;
    std::vector<std::pair<string, std::pair<string, string>>> startingNodes;


    for(std::pair<string, std::pair<string, string>> element : letters){
        if(element.first[2]=='A'){
            startingNodes.push_back(element);
        }
    }

    std::vector<int> minReach(startingNodes.size());

    std::fill(minReach.begin(), minReach.end(), 0);

    bool stop = false;
    int max=0;

    while(true){

        for(char direction : directions){

            for(auto& element: startingNodes) {

                if (direction == 'L') {
                    element = find(element.second.first, letters);
                } else { //P
                    element = find(element.second.second, letters);
                }
            }

            moves++;

            int endsWithZ = 0;
            int i=0;

            for(auto element: startingNodes) {
                if(element.first[2]=='Z'){
                    minReach[i] = moves;
                    endsWithZ++;
                }
                i++;
            }

            bool isAllCalculated = true;

            for(auto element : minReach){
                if(element == 0){
                    isAllCalculated = false;
                    break;
                }
            }

            if(isAllCalculated){
                for (auto element : minReach) {
                    for (auto elementIn : minReach) {
                        if(LCM(element, elementIn) > max){
                            max = LCM(element, elementIn);
                        }
                    }
                }
                stop = true;
            }

        }

        if(stop){
            break;
        }

    }

    std::cout << max << std::endl;



}

int Day8::LCM(int a, int b){
    return a*b/GCD(a,b);
}

int Day8::GCD(int a, int b){
    int remainder = a%b;
    return remainder == 0 ? b : GCD(b, remainder);

}

void Day8::readData(){
    fstream file;
    file.open("data8.txt",ios::in);

    file >> directions;

    while(!file.eof()){
        file >> node;
        file >> someData;
        file >> left;
        left = left.substr(1, left.size()-2);
        file >> right;
        right = right.substr(0, right.size()-1);
        letters.emplace_back(node, std::make_pair(left,right));
    }
    file.close();
}

std::pair<string, std::pair<string, string>> Day8::find(string wanted,
                                                        vector<std::pair<string, std::pair<string, string>>> letters){
    std::pair<string, std::pair<string, string>> actualNode;

    for(std::pair<string, std::pair<string, string>> element : letters){
        if(element.first==wanted){
            actualNode = element;
            break;
        }
    }

    return actualNode;
}