#include <iostream>
#include <vector>
#include <string>
#include "utils/helper.h"
#include "dayTwo.h"

using namespace std;

bool isSafeWithTolerance(vector<string> numbers) {
    vector<vector<string>> variations;
    for (int i = 0; i < numbers.size(); i++) {
        vector<string> toTest;
        copy(numbers.begin(), numbers.end(), back_inserter(toTest));
        toTest.erase(toTest.begin() + i);
        if (isSafe(toTest)) {
            return true;
        }
    }
    return false;
}

bool isSafe(vector<string> numbers) {
    int a = stoi(numbers[0]);
    int b = stoi(numbers[1]);
    // positive is decresing, negative if increasing, 0 if neither
    int order = sign(a - b);
    if (order == 0) {
        return false;
    }
    for (int i  = 0; i < numbers.size() - 1; i++) {
        b = stoi(numbers[i+1]);
        int diff = abs(a-b);
        if (sign(a - b) != order || diff < 1 || diff > 3) {
            return false;
        }
        a = b;
    }
    return true;
}

int main() { 

    vector<string> input = readFileContentsIntoStringVector("inputs/2.txt");
    int nSafe = 0;
    int nSafeWithTolerance = 0;

    for (string &line : input) {
        vector<string> numbers = split(line, " ");
        if (isSafe(numbers)) {
            nSafe++;
        } else {
            nSafeWithTolerance += isSafeWithTolerance(numbers);
        }
        
    }
    cout << nSafe << endl;
    cout << nSafeWithTolerance + nSafe << endl;
    return 0;
}