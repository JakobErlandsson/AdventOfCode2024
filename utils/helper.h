#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

std::vector<std::string> readFileContentsIntoStringVector(std::string);
std::map<std::tuple<int, int>, char> readFileContentsIntoCoordinateMap(std::string);
std::vector<std::string> split(std::string s, std::string delimiter);
int sign(int n);
std::vector<std::tuple<int, int>> getSurrounding(std::tuple<int, int> node);
bool inside(std::tuple<int, int> pos, int width, int height);

#endif 