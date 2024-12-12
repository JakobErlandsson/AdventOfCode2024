#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "utils/helper.h"

using namespace std;

vector<int> layout;
vector<int> layoutShort;
vector<int> freeSpace;

long calcChecksum() {
    long checksum = 0;
    int pos = 0;
    int posFromBack = 0;
    int i = 0;
    while(true) {
        int n = layoutShort[i];
        for (int j = 0; j < n; j++) {
            checksum += (i*pos);
            pos++;
            if (pos >= layout.size()) return checksum;
        }

        n = freeSpace[i];
        for (int j = 0; j < n; j++) {
            int x = layout[layout.size() - 1 - posFromBack];
            checksum += (x * pos);
            pos++;
            posFromBack++;
            if (pos >= layout.size()) return checksum;
        }
        i++;
    }
}

bool finished(vector<bool> v) {
    for (const bool &b : v) {
        if (!b) return false;
    }
    return true;
}

vector<int> reorganize() {
    vector<int> newLayout;
    vector<bool> used(layoutShort.size(), false);
    int posFromBack = layoutShort.size() - 1;
    int i = 0;
    while (!finished(used)) {
        int n = layoutShort[i];
        if (used[i]) {
            for (int j = 0; j < n; j++) {
                newLayout.push_back(0);
            }
        } else {
            for (int j = 0; j < n; j++) {
                newLayout.push_back(i);
            }
            used[i] = true;
        }
        
        int available = freeSpace[i];
        for (int j = layoutShort.size() - 1; j >= 0; j--) {
            if (available == 0) {
                break;
            }
            n = layoutShort[j];
            if (!used[j] && n <= available) {
                for (int k = 0; k < n; k++) {
                    newLayout.push_back(j);
                }
                used[j] = true;
                available -= n;
            }
        }
        for (int j = 0; j < available; j++) {
            newLayout.push_back(0);
        }
        i++;
    }
    return newLayout;
}

int main() {
    string diskMap = readFileContentsIntoStringVector("inputs/9.txt")[0];
    
    bool data = true;
    int idx = 0;
    for (char &c : diskMap) {
        int num = c - '0';
        if (data) {
            layoutShort.push_back(num);
            for (int i = 0; i < num; i++) {
                layout.push_back(idx);
            }
            idx++;
        }
        else freeSpace.push_back(num);
        data = !data;
    }
    cout << calcChecksum() << endl;
    vector<int> newLayout = reorganize();
    long checksum = 0;
    for (int i = 0; i < newLayout.size(); i++) {
        checksum += (i * newLayout[i]);
    }
    cout << checksum << endl;
}