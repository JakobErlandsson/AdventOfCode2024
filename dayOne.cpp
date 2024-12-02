#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include "utils/helper.h"

using namespace std;

int main() { 

    vector<string> input = readFileContentsIntoStringVector("inputs/1.txt");

    regex rgx("(\\d+)\\s+(\\d+)");
    smatch match; 

    vector<int> leftColumn(input.size());
    vector<int> rightColumn(input.size());
    map<int, int> rightMap;

    for (int i = 0; i < input.size(); i++)
    {
        string line = input[i];
        if (regex_match(line, match, rgx)) {
            leftColumn[i] = stoi(match[1]);
            int rhs = stoi(match[2]);
            rightColumn[i] = rhs;
            if (rightMap.count(rhs) == 0) {
                rightMap[rhs] = 1;
            } else {
                rightMap[rhs] += 1;
            }
        }
    }
    sort(leftColumn.begin(), leftColumn.end());
    sort(rightColumn.begin(), rightColumn.end());
    int totDist = 0;
    int similarity = 0;

    for (int i = 0; i < leftColumn.size(); i++) {
        totDist += abs(leftColumn[i] - rightColumn[i]);
        int mult = rightMap.count(leftColumn[i]) == 0 ? 0 : rightMap[leftColumn[i]];
        similarity += leftColumn[i] * mult;
    }

    cout << totDist << endl;
    cout << similarity << endl;
    return 0;
}