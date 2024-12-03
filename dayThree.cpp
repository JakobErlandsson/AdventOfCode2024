#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "utils/helper.h"

using namespace std;

int main() {
    vector<string> puzzleInput =
        readFileContentsIntoStringVector("inputs/3.txt");
    string code = "";

    for (string &line : puzzleInput) {
        code.append(line);
    }
    regex mulDoDontPattern(R"(mul\(\d{1,3},\d{1,3}\)|(do\(\))|(don't\(\)))");
    regex digitsInMul("(\\d+),(\\d+)");
    smatch match;

    auto words_begin =
        sregex_iterator(code.begin(), code.end(), mulDoDontPattern);
    auto words_end = sregex_iterator();

    vector<string> matches;

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        matches.push_back(match.str());
    }
    int totalPartOne = 0;
    int totalPartTwo = 0;
    bool active = true;
    for (string &line : matches) {
        if (line == "do()")
            active = true;
        else if (line == "don't()")
            active = false;
        else {
            if (regex_search(line, match, digitsInMul)) {
                int res = stoi(match[1]) * stoi(match[2]);
                totalPartOne += res;
                if (active) totalPartTwo += res;
            }
        }
    }
    cout << totalPartOne << endl << totalPartTwo << endl;
    return 0;
}