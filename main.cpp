// Includes
#include "QRCode.h"
#include "Menu.h"
#include "include/QRCode.h"
#include "utils.h"

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

// Prototypes
void welcome();
Menu buildMenu();
string getText(string);
void exit();
char getYesNo(string);
bool isInPalettes(string);

// Main
int main() {




    // constants
    const char QUIT = 'q';
    const char GENERATE = 'g';
    const char SCAN = 's';
    const string PROMPT = "> ";
    // other variable declarations
    Menu menu;
    char option;
    string paletteSelection;

    // setup
    menu = buildMenu();

    // app start
    welcome();
    menu.display();
    option = menu.getOption();

    // main logic loop
    while (option != QUIT) {
        if (option == GENERATE) {
            // get message to encode
            // char isCorrectMessage = 'n';
            // string text;
            // while (isCorrectMessage == 'n') {
            //     text = getText("Text: ");
            //     cout << "The message to encode is \'" << text << "\'" << endl;
            //     cout << "Is that correct? (\'y\' to confirm, 'n' to enter a new message)" << endl;
            //     isCorrectMessage = getYesNo(PROMPT);
            // }

            // get color palette of qr code
            // cout << "Select a color palette:" << endl;
            QRCode::printPalettes();
            // paletteSelection = getText(PROMPT);
            // while (!isInPalettes(paletteSelection)) {
            //     paletteSelection = getText(PROMPT);
            // }

            // gen qr code
            // FIXME : add check for text length, text must be < 100 characters to make a QR code for it
            // QRCode qrCode(text);
            // qrCode.setPalette(paletteSelection);

            // TESTING /////??//////
            QRCode qrCode("text");
            qrCode.setPalette("autumn");
            qrCode.generate();

            // describeProcess - github pages :)
            // print qr code
            // validate (checksum thingy) - run auto
            qrCode.printNumerical();
            qrCode.print();

            // ask if want to download
            // cout << "Download? (\'y\' or \'n\')" << endl;
            // char download = getYesNo(PROMPT);

            // if (download == 'y') {
            //     qrCode.download();
            // }

        } else if (option == SCAN) {
            //scan
            cout << "Scanning..." << endl;
            // get path
            // do the scan and output the text
        }
        menu.display();
        option = menu.getOption();
    }

    exit();

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

    validChar = getCharFromUser(prompt, chars);
    return validChar;

}

// get non empty input text and trimming leading and trailing whitespace
string getText(string prompt) {
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


bool isInPalettes(string palette) {
    bool in = false;
    for (int i = 0; i < QRCode::paletteNames.size() && !in; i++) {
        if (lowerString(palette) == QRCode::paletteNames.at(i)) {
            in = true;
        }
    }
    return in;
}


void exit() {
    cout << "Bye bye" << endl;
}
