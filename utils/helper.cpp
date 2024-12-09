#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
using namespace std;

vector<string> readFileContentsIntoStringVector(string fileName){
    ifstream file(fileName);

    if (!file.is_open()) {
        // print error message and return
        cerr << "Failed to open file: " << fileName << endl;
        return {};
    }

    vector<string> fileContents;
    string line;
    while (getline(file, line)) {
        fileContents.push_back(line);
    }

    file.close();

    return fileContents;
}

map<tuple<int, int>, char> readFileContentsIntoCoordinateMap(string fileName) {
    ifstream file(fileName);

    if (!file.is_open()) {
        // print error message and return
        cerr << "Failed to open file: " << fileName << endl;
        return {};
    }

    map<tuple<int, int>, char> coordinates;
    string line;
    int y = 0;
    while (getline(file, line)) {
        for (int x = 0; x < line.size(); x++) {
            coordinates[{x, y}] = line.at(x);
        }
    }
    file.close();
    return coordinates;
}

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

int sign(int n) {
    return (0 < n) - (n < 0);
}