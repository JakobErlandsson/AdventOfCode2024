#include <bitset>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "utils/helper.h"

using namespace std;

bool evaluate(vector<long> numbers, long target) {
    int nOperators = numbers.size() - 1;
    for (int i = 0; i < pow(2, nOperators); i++) {
        string operators = bitset<16>(i).to_string();
        operators = operators.substr(16 - nOperators, 16);
        long sum = numbers[0];
        for (int i = 0; i < operators.size(); i++) {
            if (operators.at(i) == '0')
                sum += numbers[i + 1];
            else
                sum *= numbers[i + 1];
        }
        if (sum == target) {
            return true;
        }
    }
    return false;
}

string toTernary(int n) {
    if (n == 0) return "0";
    string ternary = "";
    while (n > 0) {
        ternary += to_string(n % 3);
        n /= 3;
    }
    reverse(ternary.begin(), ternary.end());
    return ternary;
}

vector<long> concat(vector<long> numbers, string operators) {
    vector<long> newList = {numbers[0]};
    for (int i = 0;  i < operators.size(); i++) {
        if (operators.at(i) == '2') {
            string n1 = to_string(newList.back());
            string n2 = to_string(numbers[i+1]);
            newList.back() = stol(n1 + n2);
        } else {
            newList.push_back(numbers[i+1]);
        }
    }
    return newList;
}

bool evaluateWithConcat(vector<long> numbers, long target) {
    int nOperators = numbers.size() - 1;
    for (int i = 0; i < pow(3, nOperators); i++) {
        string operators = toTernary(i);
        operators = string(nOperators - operators.size(), '0') + operators;
        if (count(operators.begin(), operators.end(), '2')) {
            long sum = numbers[0];
            for (int j = 0; j < operators.size(); j++) {
                if (operators.at(j) == '0') sum += numbers[j+1];
                else if (operators.at(j) == '1') sum *= numbers[j+1];
                else sum = stol(to_string(sum) + to_string(numbers[j+1]));
            }
            if (sum == target) return true;
        }
    }
    return false;
}

int main() {
    vector<string> puzzleInput =
        readFileContentsIntoStringVector("inputs/7.txt");

    long total = 0;
    long totalWithConcat = 0;

    for (string &line : puzzleInput) {
        vector<string> splitted = split(line, ": ");
        long value = stol(splitted[0]);
        vector<long> numbers;
        for (string &num : split(splitted[1], " ")) {
            numbers.push_back(stol(num));
        }
        if (evaluate(numbers, value)) {
            total += value;
        } else if (evaluateWithConcat(numbers, value)) {
            totalWithConcat += value;
        }
    }
    cout << total << endl;
    cout << totalWithConcat  + total << endl;
}