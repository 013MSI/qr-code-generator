#pragma once

#include <vector>
using namespace std;

char getCharFromUser(const string& prompt, const vector<char>& validChars);
bool found(char c, const vector<char> &chars);
string lowerString(const string);
string trim(string);
string getText(const string& prompt);
char getYesNo(const string& prompt);
