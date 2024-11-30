#include "utils.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

char getChar(const string& prompt, const vector<char>& validChars) {
    string input;
    cout << prompt;
    getline(cin, input);
    while (input.length() != 1 || !found(tolower(input.at(0)), validChars)) {
        cout << prompt;
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

string lowerString(const string text) {
    string lowered;
    for (int i = 0; i < text.length(); i++) {
        lowered += tolower(text.at(i));
    }
    return lowered;
}

string trim(string text) {
    string trimmed = "";

    // find index to start copying characters from
    int start = 0;
    for (int i = 0; i < text.length(); i++){
        if (text.at(i) != ' ') {
            start = i;
            break;
        }
    }

    // find index to end copying
    // Why -1? If empty string or string of all spaces, start = 0, end = -1,
    // so following for loop does not execute and we return ""
    int end = -1;
    for (int i = text.length() - 1; i >= start; i--){
        if (text.at(i) != ' ') {
            end = i;
            break;
        }
    }

    // trim text, ie copy characters from start to end index into new string
    for (int i = start; i <= end; i++) {
        trimmed += text.at(i);
    }

    return trimmed;
}


// get non empty input text and trimming leading and trailing whitespace
string getText(const string& prompt) {
    string text;
    cout << prompt;
    getline(cin, text);
    text = trim(text);
    while (text == "") {
        cout << prompt;
        getline(cin, text);
        text = trim(text);
    }
    return text;
}


// FIXME : return bool?
char getYesNo(const string& prompt) {
    vector<char> chars;
    char validChar;

    chars.push_back('y');
    chars.push_back('n');

    validChar = getChar(prompt, chars);
    return validChar;

}
