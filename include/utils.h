#pragma once

#include <vector>
using namespace std;

// io utils
char getChar(const string& prompt, const vector<char>& validChars);
string getText(const string& prompt);
char getYesNo(const string& prompt);

// string manip
string lowerString(const string);
string trim(string);

// char util
bool found(char c, const vector<char> &chars);
