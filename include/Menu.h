// Menu.h

#pragma once

#include <string>
#include <vector>

using namespace std;

/*
 * Provides a text-based menu which allows adding options with descriptions and printing the menu.
 * Contains built-in functionality to retrive valid menu options based on user input via the console.
 */
class Menu {
    public:

        /*
        * Adds an option to the menu with a corresponding description.
        *
        * param:
        *   option - A character representing a menu option
        *   description - A brief description of the option's functionality.
        * return A pointer to the Menu instance, allowing chained calls to `addItem`.
        */
        Menu* addItem(char option, string description);

        /*
        * Prints the menu to the console, showing each option with its description.
        */
        void print() const;

        /*
        * Prompts the user to select an option from the menu.
        *
        * return The character representing the selected menu option.
        */
        char getOption() const;

    private:
        // A list of characters representing the menu options.
        vector<char> options;
        // A list of descriptions corresponding to the menu options.
        vector<string> descriptions;
};
