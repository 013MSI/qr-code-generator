#pragma once

#include <string>
#include <vector>

using namespace std;

class Menu {
    public:
        // return pointer to self from addItem so that the Menu can be built by chaining .addItem calls
        Menu* addItem(char option, string description);
        void print() const;
        char getOption() const;
    private:
        vector<char> options;
        vector<string> descriptions;
};
