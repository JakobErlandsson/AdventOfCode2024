#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utils/helper.h"

using namespace std;

void fromZero() {
    vector<string> stones = {"0"};
    for (int blink = 1; blink <= 75; blink++) {
        int size = stones.size();
        for (int i = 0; i < size; i++) {
            if (stones[i] == "0") {
                stones[i] = "1";
            } else if (stones[i].size() % 2 == 0) {
                string lhs = stones[i].substr(0, stones[i].size() / 2);
                string rhs = stones[i].substr(stones[i].size() / 2);
                stones[i] = to_string(stol(lhs));
                stones.push_back(to_string(stol(rhs)));
            } else {
                stones[i] = to_string(stol(stones[i]) * 2024);
            }
        }
        cout << blink << ":\t" << size << endl;
    }
}

int main() {
    fromZero();
    return 0;
    vector<string> stones = readFileContentsIntoStringVector("inputs/11.txt");
    stones = split(stones[0], " ");
    for (int blink = 0; blink < 75; blink++) {
        int size = stones.size();
        for (int i = 0; i < size; i++) {
            if (stones[i] == "0") {
                stones[i] = "1";
            } else if (stones[i].size() % 2 == 0) {
                string lhs = stones[i].substr(0, stones[i].size() / 2);
                string rhs = stones[i].substr(stones[i].size() / 2);
                stones[i] = to_string(stol(lhs));
                stones.push_back(to_string(stol(rhs)));
            } else {
                stones[i] = to_string(stol(stones[i]) * 2024);
            }
        }
        cout << stones.size() << "\t\t\t" << stones.size() - size << endl;
    }
}