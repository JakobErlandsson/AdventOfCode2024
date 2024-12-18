#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "utils/helper.h"

using namespace std;

regex digitsRegex("X\\W(\\d+),\\sY\\W(\\d+)");
smatch match;

long solve(int ax, int ay, int bx, int by, long px, long py) {
    /*
    ax * A + bx * B = px
    ay * A + by * B = py

    A = (px - bx * B) / ax
    ay * (px - bx * B) / ax + by * B = py
    (ay * px - ay * bx * B) / ax + by * B = py
    (ay * px - (by * ax - ay * bx) * B)) / ax = py
    ay * px - (by * ax - ay * bx) * B) = py * ax
    (by * ax - ay * bx) * B) = py * ax - ay * px
    B = (py * ax - ay * px) / (by * ax - ay * bx)
    A = (px - bx * B) / ax
    */

    if ((py * ax - ay * px) % (by * ax - ay * bx) == 0) {
        long B = (py * ax - ay * px) / (by * ax - ay * bx);
        if (B >= 0 && (px - bx * B) % ax == 0) {
            long A = (px - bx * B) / ax;
            if (A >= 0) {
                return A * 3 + B;
            }
        }
    }
    return 0;
}

int main() {
    int cost = 0;
    long costInsane = 0;
    vector<string> puzzleInput =
        readFileContentsIntoStringVector("inputs/13.txt");

    for (int i = 0; i < puzzleInput.size(); i+=4) {
        string A = split(puzzleInput[i], ": ")[1];
        string B = split(puzzleInput[i + 1], ": ")[1];
        string price = split(puzzleInput[i + 2], ": ")[1];
        int ax, ay, bx, by, px, py = 0;
        if (regex_match(A, match, digitsRegex)) {
            ax = stoi(match[1]);
            ay = stoi(match[2]);
        }
        if (regex_match(B, match, digitsRegex)) {
            bx = stoi(match[1]);
            by = stoi(match[2]);
        }
        if (regex_match(price, match, digitsRegex)) {
            px = stoi(match[1]);
            py = stoi(match[2]);
        }
        cost += solve(ax, ay, bx, by, px, py);
        costInsane += solve(ax, ay, bx, by, px + 10000000000000, py + 10000000000000);
    }
    cout << cost << endl;
    cout << costInsane << endl;
}