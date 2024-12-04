#include "utils/helper.h"
#include <vector>
#include <string>
#include <iostream>
#include <regex>

using namespace std;

vector<string> makeVertical(vector<string> horizontal) {
    vector<string> res;
    for (int i = 0; i < horizontal.size(); i++) {
        string s = "";
        for (int j = 0; j < horizontal.size(); j++) {
            s += horizontal[j].at(i);
        }
        res.push_back(s);
    }
    return res;
}

vector<string> makePosDiagonal(vector<string> horizontal) {
    vector<string> res;
    for (int i = 1; i < horizontal.size() - 2; i++) {
        string s1 = "";
        string s2 = "";
        for (int j = 0; j < horizontal.size() - i; j++) {
            s1 += horizontal[j].at(j + i);
            s2 += horizontal[j + i].at(j);
        }
        res.push_back(s1);
        res.push_back(s2);
    }
    string s3 = "";
    for (int i = 0; i < horizontal.size(); i++) {
        s3 += horizontal[i].at(i);
    }
    res.push_back(s3);
    return res;
}

vector<string> makeNegDiagonal(vector<string> horizontal) {
    vector<string> res;
    int len = horizontal.size();
    for (int i = 1; i < len - 2; i++) {
        string s1 = "";
        string s2 = "";
        for (int j = 0; j < len - i; j++) {
            s1 += horizontal[j].at(len - 1 - i - j);
            s2 += horizontal[i + j].at(len - 1 - j);
        }
        res.push_back(s1);
        res.push_back(s2);
    }
    string s3 = "";
    for (int i = 0; i < len; i++) {
        s3 += horizontal[i].at(len - 1 - i);
    }
    res.push_back(s3);
    return res;
}

int main() {
    vector<string> wordSearchHorizontal = readFileContentsIntoStringVector("inputs/4.txt");
    vector<string> wordSearchVertical = makeVertical(wordSearchHorizontal);
    vector<string> wordSearchPosDiagonal = makePosDiagonal(wordSearchHorizontal);
    vector<string> wordSearchNegDiagonal = makeNegDiagonal(wordSearchHorizontal);

    vector<string> wordSearchComplete;
    wordSearchComplete.insert(wordSearchComplete.end(), wordSearchHorizontal.begin(), wordSearchHorizontal.end());
    wordSearchComplete.insert(wordSearchComplete.end(), wordSearchVertical.begin(), wordSearchVertical.end());
    wordSearchComplete.insert(wordSearchComplete.end(), wordSearchPosDiagonal.begin(), wordSearchPosDiagonal.end());
    wordSearchComplete.insert(wordSearchComplete.end(), wordSearchNegDiagonal.begin(), wordSearchNegDiagonal.end());

    regex xmas("XMAS");
    int totalOccurences = 0;
    for (string &line : wordSearchComplete) {
        totalOccurences += distance(
            sregex_iterator(line.begin(), line.end(), xmas),
            sregex_iterator()
        );
        reverse(line.begin(), line.end());
        totalOccurences += distance(
            sregex_iterator(line.begin(), line.end(), xmas),
            sregex_iterator()
        );
    }
    cout << totalOccurences << endl;
    
    int totalX_masOccurences = 0;
    for (int i = 1; i < wordSearchHorizontal.size() - 1; i++) {
        for (int j = 1; j < wordSearchHorizontal.size() - 1; j++) {
            if (wordSearchHorizontal[i].at(j) == 'A') {
                char upRight = wordSearchHorizontal[i-1].at(j+1);
                char upLeft = wordSearchHorizontal[i-1].at(j-1);
                char downRight = wordSearchHorizontal[i+1].at(j+1);
                char downLeft = wordSearchHorizontal[i+1].at(j-1);
                if ((upRight == 'M' && downLeft == 'S' || upRight == 'S' && downLeft == 'M') && 
                    (upLeft == 'M' && downRight == 'S' || upLeft == 'S' && downRight == 'M')) {
                        totalX_masOccurences++;
                    }
            }
        }
    }
    cout << totalX_masOccurences << endl;

}