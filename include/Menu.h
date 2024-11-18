#pragma once

#include <string>
#include <vector>

using namespace std;

class Menu {
    public:
        Menu* addItem(char, string); // Ayesha knows about pointers
        void display();
        char getOption();
    private:
        vector<char> options;
        vector<string> descriptions;
};
