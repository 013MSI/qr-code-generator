// Menu.cpp

#include "Menu.h"
#include "utils.h"
#include "fmt/color.h"
#include <string>

using namespace std;

Menu* Menu::addItem(char option, string description) {
    options.push_back(option);
    descriptions.push_back(description);
    return this;
}

void Menu::print() const {
    for (int i = 0; i < options.size(); i++) {
        fmt::print(fmt::emphasis::bold, "{}: ", options.at(i));
        fmt::print("{}\n", descriptions.at(i));
    }
    fmt::print("\n");
}

char Menu::getOption() const {
    return getChar("> ", options);
}
