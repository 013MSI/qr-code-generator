// Includes
#include "QRCode.h"
#include "Menu.h"
#include "utils.h"

#include <iostream>
#include <cctype>

using namespace std;

// Prototypes
void welcome();
Menu buildMenu();
void exit();
char getYesNo(string);

// Main
int main() {
    // constants
    const char QUIT = 'q';
    const char GENERATE = 'g';
    const char SCAN = 's';

    // other variable declarations
    Menu menu;
    char option;

    // setup
    menu = buildMenu();

    // app start
    welcome();
    menu.display();
    option = menu.getOption();

    // main logic loop
    while (option != QUIT) {
        if (option == GENERATE) {
            // generate
            char response = getYesNo("Enter \'y \'or \'n\' to continue");
            cout << response << endl;
            cout << "Generated" << endl;

        } else if (option == SCAN) {
            //scan
            cout << "Scanning..." << endl;
        }
        menu.display();
        option = menu.getOption();
    }

    exit();

    // menu - scan or new qr code
        // new qr //
        //get the text
        //confimation if y cont else get text again
        // gen qr code
        // describeProcess
        // print - b&w version
        // validate (checksum thingy) - run auto
        // customize loop
            //color, shape
            // print out to see
            // download?
                // if download -
                    // if one just download it
                    // else list all and ask which one
                    // go back to menu
                // else custom again
        // menu again
        //
        // scan //
        // get path
        // do the scan and output the text
        // menu agian
    // menu again if q quit else do option
    // if q - bye bye

    return 0;
}

void welcome() {
    cout << "Welcome" << endl;
}

Menu buildMenu() {
    Menu menu;
    menu.addItem('g', "🛠  Generate")
        ->addItem('s', "🔍 Scan")
        ->addItem('q', "⤵️  Quit");
    return menu;
}

// FIXME : return bool?
char getYesNo(string prompt) {
    vector<char> chars;
    char validChar;

    chars.push_back('y');
    chars.push_back('n');

    cout << prompt << endl;
    validChar = getCharFromUser(chars);
    return validChar;

}

void exit() {
    cout << "Bye bye" << endl;
}
