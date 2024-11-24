#include "Menu.h"
#include "utils.h"

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

Menu* Menu::addItem(char option, string description) {
    options.push_back(option);
    descriptions.push_back(description);
    return this;
}

void Menu::display() {
    cout << "---MENU---" << endl;
    for (int i = 0; i < options.size(); i++) {
        cout << options.at(i) << ": " << descriptions.at(i) << endl;
    }
    cout << endl;
}

char Menu::getOption() {
    return getCharFromUser("> ", options);
}
