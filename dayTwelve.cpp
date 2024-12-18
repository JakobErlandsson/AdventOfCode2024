#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utils/helper.h"

using namespace std;

map<tuple<int, int>, char> garden;
int width, height;

int countSides(set<tuple<int, int>> region, int sx, int sy) {
    vector<tuple<int, int>> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };
    tuple<int, int> start = {sx - 1, sy - 1};
    tuple<int, int> pos = {sx - 1, sy - 1};
    int sides = 0;
    int dir = 0;
    do {
        int right = (dir + 1) % 4;
        int left = dir > 0 ? dir - 1 : 3;
        int stepX = get<0>(directions[dir]);
        int stepY = get<1>(directions[dir]);
        int lookX = get<0>(directions[right]);
        int lookY = get<1>(directions[right]);
        tuple<int, int> step = {get<0>(pos) + stepX, get<1>(pos) + stepY};
        tuple<int, int> check = {get<0>(step) + lookX, get<1>(step) + lookY};
        if (region.find(step) != region.end()) {
            dir = left;
            sides++;
        } else if (region.find(check) == region.end()) {
            dir = right;
            sides++;
            pos = step;
        } else {
            pos = step;
        }
    } while (start != pos);
    return sides;
}

int main() {
    vector<string> puzzleInput = readFileContentsIntoStringVector("inputs/12.txt");
    width = puzzleInput[0].size();
    height = puzzleInput.size();
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            garden[{x, y}] = puzzleInput[y].at(x);
        }
    }
    int price = 0;
    int priceV2 = 0;
    set<tuple<int, int>> visited;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (visited.find({x, y}) == visited.end()) {
                int minX = x;
                int minY = y;
                char c = garden[{x, y}];
                queue<tuple<int, int>> q;
                q.push({x, y});
                set<tuple<int, int>> visitedLocal;
                set<tuple<int, int, int, int>> perimeter;
                while (!q.empty()) {
                    tuple<int, int> node = q.front();
                    q.pop();
                    if (visitedLocal.find(node) != visitedLocal.end()) {
                        continue;
                    }
                    visitedLocal.insert(node);
                    visited.insert(node);
                    for (auto &n : getSurrounding(node)) {
                        if (garden.find(n) == garden.end() || garden[n] != garden[node]) {
                            perimeter.insert({get<0>(n), get<1>(n), get<0>(node), get<1>(node)});
                        } else if (visitedLocal.find(n) == visitedLocal.end() && garden[n] == garden[node]) {
                            q.push(n);
                        }
                    }
                }
                price += perimeter.size() * visitedLocal.size();
                int sides = countSides(visitedLocal, minX, minY);
                priceV2 += visitedLocal.size() * sides;
                cout << garden[{minX, minY}] << "\ta:" << visitedLocal.size() << "\tp: " << perimeter.size() << "\ts: " << sides << endl;
            }
        }
    }
    cout << price << endl << priceV2 << endl;;
}