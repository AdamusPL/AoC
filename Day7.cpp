//
// Created by adamc on 19.03.2024.
//

#include <vector>
#include <algorithm>
#include "Day7.h"

//so close...

Day7::Day7() {
    kindsOfCards = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
}

bool compare(const pair<pair<string, int>, pair<char, int>>& a, const pair<pair<string, int>, pair<char, int>>& b) {
    // If counts are equal, compare based on the value of the card
    // You can create a map or array to assign ranks to cards
    string kindsOfCards = "AKQJT98765432";

    if(a.second.second != b.second.second) {
        bool cmp1;
        bool cmp2;

        cmp1 = a.second.second > b.second.second; // Sort by count, highest to lowest
        cmp2 = kindsOfCards.find(a.second.first) > kindsOfCards.find(b.second.first);

        if ((cmp1 && cmp2)) {
            return true;
        }
        if (cmp1 && !cmp2) {
            return false;
        }
        if (!cmp1 && cmp2) {
            return false;
        }
        if (!cmp1 && !cmp2) {
            return true;
        }
    }

    else{
        bool cmp2;

        cmp2 = kindsOfCards.find(a.second.first) > kindsOfCards.find(b.second.first);

        if(cmp2){
            return true;
        }

        else{
            return false;
        }
    }
}

void Day7::part1() {

    fstream file;
    file.open("cmake-build-debug/data7.txt", ios::in);

    //hand+value
    vector<pair<string, int>> cards;

    string hand;
    int value;

    while (!file.eof()) {
        file >> hand;
        file >> value;
        cards.emplace_back(hand, value);
    }

    file.close();

    //card+amount (max)
    pair<char, int> kinds;

    //pair: (hand+value) + (most repetitive card, how many times it repeats)
    vector<pair<pair<string, int>, pair<char, int>>> cardsWithParameters;

    int j = 1;

    for (auto &handValue: cards) {
        kinds = kindChecker(handValue.first);
        cardsWithParameters.emplace_back(handValue, kinds);
        j++;
    }

    //sort by number of repetitive cards and then most powerful cards
    sort(cardsWithParameters.begin(), cardsWithParameters.end(), compare);

    //calculate gains
    int sum = 0;
    int i = 1;

    for (auto &valueCard: cardsWithParameters) {
        cout << valueCard.first.second << "*" << i << "+";
        sum += valueCard.first.second * i;
        i++;
    }

    cout << "=" << sum << endl;

}

pair<char, int> Day7::kindChecker(string hand) {
    vector<pair<char, int>> numberOfCards;
    //count how many cards of which kind is in hand
    for (char x: hand) {
        bool exist = false;
        for (auto &value: numberOfCards) {
            if (x == value.first) {
                exist = true;
                value.second++;
            }
        }
        if (!exist) {
            numberOfCards.emplace_back(x, 1);
        }
    }

    int max = 0;
    pair<char, int> valueMax;

    //check what kind of card is the most common and which is most powerful
    for (auto &value: numberOfCards) {
        if (value.second > max) {
            max = value.second;
            valueMax = value;
        } else if (value.second == max) {
            //if there are two cards which appear in the same amount
            valueMax = make_pair(checkWhichCardIsBetter(valueMax.first, value.first), max);
        }
    }

    return valueMax;

}

char Day7::checkWhichCardIsBetter(char x, char y) {
    int rankX, rankY = 0;
    for (int i = 0; i < kindsOfCards.size(); i++) {
        if (x == kindsOfCards[i]) {
            rankX = i;
            break;
        }
    }

    for (int i = 0; i < kindsOfCards.size(); i++) {
        if (y == kindsOfCards[i]) {
            rankY = i;
            break;
        }
    }

    if (rankX < rankY) {
        return x;
    } else {
        return y;
    }
}