//
// Created by adamc on 09.03.2024.
//

#include "Day4.h"

void Day4::launch() {
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
        for(char i : data){
            if(i >= '0' && i <= '9') number+=i;
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

        for(int myNumber : myNumbers){
            for (int winningNumber : winningNumbers) {
                if(myNumber == winningNumber){
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

    for(auto & numberOfCopy : numberOfCopies){
//        cout<<numberOfCopies[i].second<<endl;
        sumOfScratchCards+=numberOfCopy.second;
    }

    cout << sumOfPoints << endl;
    cout << sumOfScratchCards << endl;

    file.close();
}
