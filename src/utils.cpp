#include "utils.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

char getCharFromUser(const vector<char> &validChars) {
    string input;
    cout << "> ";
    getline(cin, input);
    while (input.length() != 1 || !found(tolower(input.at(0)), validChars)) {
        cout << "> ";
        getline(cin, input);
    }
    return input.at(0);
}

bool found(char c, const vector<char> &chars) {
    for (int i = 0; i < chars.size(); i++) {
        if (c == chars.at(i)) {
            return true;
        }
    }
    return false;
}
