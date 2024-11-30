// utils.h

#pragma once

#include <vector>
using namespace std;

// Input/Output
char getChar(const string& prompt, const vector<char>& validChars);
string getText(const string& prompt);
char getYesNo(const string& prompt);

// String Manip
string lowerString(const string& text);
string trim(const string& text);

// Char Search
bool found(char c, const vector<char>& chars);
