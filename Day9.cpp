//
// Created by adamc on 05/06/2026.
//

#include "Day9.h"

void Day9::part1() {
    fstream file;
    file.open("data9.txt", ios::in);

    if (file.is_open()) {
        string line;
        vector<vector<int> > allValues;
        vector<int> values;
        int finalSum = 0;

        while (getline(file, line)) {
            istringstream iss(line);
            string s;
            values.clear();
            while (getline(iss, s, ' ')) {
                values.push_back(std::stoi(s));
            }

            allValues.clear();
            allValues.push_back(values);

            bool zeros = std::all_of(values.begin(), values.end(), [](int i) { return i == 0; });

            while (!zeros) {
                vector<int> oldValues = values;
                vector<int> valuesNested;

                for (int i = 1; i < oldValues.size(); i++) {
                    valuesNested.push_back(oldValues[i] - oldValues[i - 1]);
                }
                allValues.push_back(valuesNested);

                zeros = std::all_of(valuesNested.begin(), valuesNested.end(), [](int i) { return i == 0; });
                values = valuesNested;
            }

            allValues[allValues.size() - 1].push_back(0);
            for (int i = allValues.size() - 2; i >= 0; i--) {
                vector<int> row = allValues[i + 1];
                int val1 = row[row.size() - 1];
                vector<int> row2 = allValues[i];
                int val2 = row2[row2.size() - 1];
                allValues[i].push_back(val1 + val2);
            }

            vector<int> final = allValues[0];
            int valueFinal = final[final.size() - 1];
            cout << valueFinal << endl;
            finalSum += valueFinal;
        }

        cout << "Score: " << finalSum << endl;

        file.close();
    }
}
