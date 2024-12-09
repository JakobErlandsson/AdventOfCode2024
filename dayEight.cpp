#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include "utils/helper.h"

using namespace std;

int width, height;

tuple<int, int> calcDist(tuple<int, int> a, tuple<int, int> b) {
    int ax = get<0>(a);
    int ay = get<1>(a);
    int bx = get<0>(b);
    int by = get<1>(b);
    return {ax-bx, ay-by};
}

bool inside(tuple<int, int> pos) {
    int x = get<0>(pos);
    int y = get<1>(pos);
    return x >= 0 && x < width && y >= 0 && y < height;
}

int add(int a, int b) {
    return a + b;
}
int sub(int a, int b) {
    return a - b;
}

tuple<int, int> eval(tuple<int, int> a, tuple<int, int> b, int(*func) (int, int)) {
    int ax = get<0>(a);
    int ay = get<1>(a);
    int bx = get<0>(b);
    int by = get<1>(b);
    return {func(ax, bx), func(ay, by)};
}

int main() {
    vector<string> roofMap = readFileContentsIntoStringVector("inputs/8.txt");

    width = roofMap[0].size();
    height = roofMap.size();
    map<char, vector<tuple<int, int>>> antennas;
    map<tuple<int, int>, char> antennasInvert;
    set<char> antennaNames;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char c = roofMap[y].at(x);
            if (c != '.') {
                antennasInvert[{x, y}] = c;
                antennaNames.insert(c);
                if (antennas.find(c) == antennas.end()) {
                    antennas.insert(pair<char, vector<tuple<int, int>>>(c, vector<tuple<int, int>>()));
                }
                antennas[c].push_back({x, y});
            }
        }
    }
    set<tuple<int, int>> antinodes;
    set<tuple<int, int>> antinodesExtended;
    set<char>::iterator itr;
    for (itr = antennaNames.begin(); itr != antennaNames.end(); itr++) {
        vector<tuple<int, int>> atns = antennas[*itr];
        for (int i = 0;  i < atns.size(); i++) {
            for (int j = i + 1; j < atns.size(); j++) {
                tuple<int, int> dist = calcDist(atns[i], atns[j]);

                tuple<int, int> locA = eval(atns[i], dist, add);
                tuple<int, int> locB = eval(atns[j], dist, sub);
                if (inside(locA)) antinodes.insert(locA);
                if (inside(locB)) antinodes.insert(locB);

                antinodesExtended.insert(atns[i]);
                antinodesExtended.insert(atns[j]);
                while (inside(locA)) {
                    antinodesExtended.insert(locA);
                    locA = eval(locA, dist, add);
                }
                while (inside(locB)) {
                    antinodesExtended.insert(locB);
                    locB = eval(locB, dist, sub);
                }
            }
        }
    }
    for (int y = 0; y < width; y++) {
        string row = "";
        for (int x = 0; x < height; x++) {
            if (antennasInvert.count({x, y})) row += antennasInvert[{x, y}];
            else if (antinodesExtended.count({x, y})) row += "#";
            else row += ".";
        }
        cout << row << endl;
    }
    cout << antinodes.size() << endl;
    cout << antinodesExtended.size() << endl;
}