#pragma once

#include <vector>
using namespace std;

char getCharFromUser(string prompt, const vector<char> &validChars);
bool found(char c, const vector<char> &chars);
string lowerString(string);
string trim(string);
