#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <regex>
#include "utils/helper.h"

using namespace std;

vector<tuple<int, int>> step {
    {0, -1}, // UP
    {1, 0},  // RIGHT
    {0, 1},  // DOWN
    {-1, 0}  // LEFT
};

int width, height; // 0-indexed
map<tuple<int, int>, char> coordinates;

bool inside(tuple<int, int> pos) {
    int x = get<0>(pos);
    int y = get<1>(pos);
    return x >= 0 && x <= width && y >= 0 && y <= height;
}

set<tuple<int, int>> getVisitedSquares(tuple<int, int> startPos, bool findLoops, tuple<int, int> extraObstacle) {
    tuple<int, int> guardPos = {get<0>(startPos), get<1>(startPos)};
    int dir = 0; // UP: 0, RIGHT: 1, DOWN: 2, LEFT: 3
    set<tuple<int, int>> visited;
    set<tuple<tuple<int, int>, tuple<int, int>>> visitedWithDir;
    while (inside(guardPos)) {
        if (findLoops && visitedWithDir.count({guardPos, step[dir]})) {
            return set<tuple<int, int>>();
        }
        visited.insert(guardPos);
        visitedWithDir.insert({guardPos, step[dir]});
        int x = get<0>(guardPos);
        int y = get<1>(guardPos);
        int nextX = get<0>(step[dir]);
        int nextY = get<1>(step[dir]);
        while (coordinates[{x + nextX, y + nextY}] == '#' || (x + nextX == get<0>(extraObstacle) && y + nextY == get<1>(extraObstacle))) {
            dir = (dir + 1) % 4;
            nextX = get<0>(step[dir]);
            nextY = get<1>(step[dir]);
        }
        guardPos = {x + nextX, y + nextY};
    }
    return visited;
}

int main() {
    vector<string> puzzleInput = readFileContentsIntoStringVector("inputs/6.txt");
    width = puzzleInput[0].size() - 1;
    height = puzzleInput.size() - 1;
    tuple<int, int> guardPos;   
    int row = 0;
    for (string &line : puzzleInput) {
        for (int x = 0; x < line.size(); x++) {
            coordinates[{x, row}] = line.at(x);
            if (line.at(x) == '^') guardPos = {x, row};
        }
        row++;
    }

    set<tuple<int, int>> visited = getVisitedSquares(guardPos, false, {-1, -1});
    cout << visited.size() << endl;
    int loops = 0;
    set<tuple<int, int>>::iterator it;
    for (it = visited.begin(); it != visited.end(); it++) {
        if (getVisitedSquares(guardPos, true, *it).size() == 0) {
            loops++;
        }
    }
    cout << loops << endl;
}