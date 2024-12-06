#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <regex>
#include "utils/helper.h"

using namespace std;

map<int, set<int>> rules;

bool compare(int a, int b) {
    return rules[a].count(b);
}

int main() {
    vector<string> puzzleInput = readFileContentsIntoStringVector("inputs/5.txt");
    regex rule("(\\d+)\\|(\\d+)");
    smatch match;

    bool isRules = true;
    vector<int> pages;

    int totMidNumbers = 0;
    int totMidNumbersFixed = 0;

    for (string &line : puzzleInput) {
        if (line.empty()) {
            isRules = false;
            continue;
        }
        if (isRules) {
            regex_match(line, match, rule);
            int lhs = stoi(match[1]);
            int rhs = stoi(match[2]);
            if (rules.find(lhs) == rules.end()) { // Key does not exist in map
                rules.insert(pair<int, set<int>>(lhs, set<int>())); 
            }
            rules[lhs].insert(rhs);
        } else {
            vector<string> tmp = split(line, ",");
            vector<int> numbers;
            for (string &t : tmp) {
                numbers.push_back(stoi(t));
            }
            if (is_sorted(numbers.begin(), numbers.end(), compare)) {
                totMidNumbers += numbers[numbers.size()/2];
            } else {
                sort(numbers.begin(), numbers.end(), compare);
                totMidNumbersFixed += numbers[numbers.size()/2];
            }
        }
    }
    cout << totMidNumbers << endl;
    cout << totMidNumbersFixed << endl;
}