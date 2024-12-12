#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>

#include "utils/helper.h"

using namespace std;

map<tuple<int, int>, int> trailMap;
vector<tuple<int, int>> trailheads;
int height, width;

vector<tuple<int, int>> getSurrounding(tuple<int, int> node) {
    vector<tuple<int, int>> ns;
    int x = get<0>(node);
    int y = get<1>(node);
    if (x > 0) ns.push_back({x-1, y});
    if (x < width - 1) ns.push_back({x+1, y});
    if (y > 0) ns.push_back({x, y-1});
    if (y < height -1) ns.push_back({x, y+1});
    return ns;
}

int main() {
    vector<string> puzzleInput = readFileContentsIntoStringVector("inputs/10.txt");

    height = puzzleInput.size();
    width = puzzleInput[0].size();
    for (int y = 0; y < width; y++) {
        for (int x = 0; x < height; x++) { 
            int h = puzzleInput[y].at(x) - '0';
            trailMap[{x, y}] = h;
            if (h == 0) trailheads.push_back({x, y});
        }
    }

    int nRoutes = 0;
    int rating = 0;
    for (auto &start : trailheads) {
        set<tuple<int, int>> peaks;
        queue<tuple<int, int>> q;
        q.push(start);
        set<tuple<int, int>> visited;
        while (!q.empty()) {
            tuple<int, int> node = q.front();
            q.pop();
            visited.insert(node);
            if(trailMap[node] == 9) {
                rating++;
                peaks.insert(node);
            }
            vector<tuple<int, int>> neighbours = getSurrounding(node);
            for (const auto &neighbour : neighbours) {
                if (visited.find(neighbour) == visited.end() && trailMap[neighbour] - trailMap[node] == 1) {
                    q.push(neighbour);
                }
            }
        }
        nRoutes += peaks.size();
    }
    cout << nRoutes << endl;
    cout << rating << endl;
}