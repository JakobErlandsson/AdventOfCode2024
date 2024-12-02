#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

std::vector<std::string> readFileContentsIntoStringVector(std::string);
std::vector<std::string> split(std::string s, std::string delimiter);
int sign(int n);

#endif 