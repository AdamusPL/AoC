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

//check which card is better
bool compare(const char& a, const char& b) {
    string kindsOfCards = "AKQJT98765432";

    return kindsOfCards.find(a) > kindsOfCards.find(b);
}

void Day7::readData() {
    fstream file;
    file.open("cmake-build-debug/data7.txt", ios::in);

    string hand;
    int value;

    while (!file.eof()) {
        file >> hand;
        file >> value;
        cards.emplace_back(hand, value);
    }

    file.close();
}

void Day7::part1() {
    readData();

    //pair: (hand+value) +
    vector<pair<pair<string, int>, int>> cardsWithParameters;

    for (auto &handValue: cards) {
        kindChecker(handValue.first, cardsWithParameters, handValue);
    }

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

void Day7::part2() {
    readData();


}

int checkKind(vector<pair<char, int>> numberOfCards) {
    //check type of hand
    if (numberOfCards.size() == 1) {
        //five of a kind
        return 1;
    }
    if (numberOfCards.size() == 4) {
        //one pair
        return 6;
    }
    if (numberOfCards.size() == 5) {
        //high card
        return 7;
    }
    if (numberOfCards.size() == 2) {
        if (numberOfCards[0].second == 4 || numberOfCards[1].second == 4) {
            //four of a kind
            return 2;
        }
        //full house
        return 3;
    }
    if (numberOfCards.size() == 3) {
        if (numberOfCards[0].second == 3 || numberOfCards[1].second == 3 || numberOfCards[2].second == 3) {
            //three of a kind
            return 4;
        }
        //two pairs
        return 5;
    }
    return 88;
}

void Day7::kindChecker(string hand, vector<pair<pair<string, int>, int>>& cardsWithParameters, pair<string, int> handValue) {
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

    int kind = checkKind(numberOfCards);
    int insertionIndex = 0;
    bool changed = false;

    //if no cards were inserted
    if (cardsWithParameters.empty()) {
        cardsWithParameters.emplace_back(handValue, kind);
        return;
    }

    for (size_t i = 0; i < cardsWithParameters.size(); ++i) {

        if (cardsWithParameters.size() == 10) {
            cout << "LOL";
        }

        const auto& card = cardsWithParameters[i];

        //when card with the same rank exist
        if (card.second == kind) {
            for (int j=0; j<5; j++) {
                if (card.first.first[j] != hand[j]) {
                    bool isWorse = compare(hand[j], card.first.first[j]);
                    if (isWorse) {
                        insertionIndex = i;
                        changed = true;
                    }
                    else if (cardsWithParameters[i+1].second != kind || i == cardsWithParameters.size() - 1) {
                        insertionIndex = i+1;
                    }
                    break;
                }
            }
        }
        if (changed) {
            break;
        }
        if (card.second > kind) {
            insertionIndex = i+1;
        }
    }

    pair<pair<string, int>, int> card = pair(handValue, kind);
    cardsWithParameters.insert(cardsWithParameters.begin() + insertionIndex, card);
}