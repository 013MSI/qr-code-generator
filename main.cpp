// Includes
#include "QRCode.h"
#include "Menu.h"
#include "checksum.h"
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
    const string LINK = "https://013msi.github.io/qr-code-generator/";
    // other variable declarations
    Menu menu;
    char option;
    string paletteSelection;
    string path;

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
            char isCorrectMessage = 'n';
            string text;
            while (isCorrectMessage == 'n') {
                text = getText("Text: ");
                cout << "The message to encode is \'" << text << "\'" << endl;
                cout << "Is that correct? (\'y\' to confirm, 'n' to enter a new message)" << endl;
                isCorrectMessage = getYesNo(PROMPT);
            }

            // get color palette of qr code
            cout << "Select a color palette:" << endl;
            QRCode::printPalettes();
            paletteSelection = getText(PROMPT);
            while (!isInPalettes(paletteSelection)) {
                paletteSelection = getText(PROMPT);
            }

            // gen qr code
            // FIXME : add check for text length, text must be < 100 characters to make a QR code for it
            QRCode qrCode(text);
            cout << paletteSelection << endl;
            qrCode.setPalette(paletteSelection);

            qrCode.generate();

            // color args for logo
            qrCode.print(Color(255, 255, 255), Color(0, 0, 0));
            // checksum
            cout << "Checksum: " << checksum(text) << endl;
            cout << "Save the checksum so you can verify your message later" << endl;
            cout << "Check out this website to learn about how your qr code was generated: " << LINK << endl << endl;

            // ask if want to download
            cout << "Download? (\'y\' or \'n\')" << endl;
            char download = getYesNo(PROMPT);

            if (download == 'y') {
                cout << "Enter a location to save your qr code: (ex. /home/myUser/qrCode.bmp)" << endl;
                path = getText(PROMPT);
                bool isDownload = qrCode.download(path, Color(255, 255, 255), Color(0, 0, 0));
                while (isDownload == false && path != "q") {
                    cout << "Sorry we couldn't download your qr code to that location :(" << endl;
                    cout << "Double check that your path exists or enter \'q\' to quit." << endl;
                    path = getText(PROMPT);
                }
                if (isDownload) {
                    cout << "Downloaded successfully!" << endl;
                    cout << "Check " << path << " to view your beautiful qr code." << endl;
                }
            }
        } else if (option == SCAN) {
            cout << "Enter the location of your qr code: (ex. /home/myUser/qrCode.bmp)" << endl;
            path = getText(PROMPT);
            cout << "Scanning..." << endl;
            string decodedText = QRCode::scan(path);
            while (decodedText == "" && path != "q") {
                cout << "Sorry we couldn't find your qr code :(" << endl;
                cout << "Double check that your path is correct or enter \'q\' to quit." << endl;
                path = getText(PROMPT);

                string decodedText = QRCode::scan(path);
            }
            if (path != "q") {
                cout << "Your message is \"" << decodedText << "\"" << endl;
                cout << "Checksum: " << checksum(decodedText) << endl;
                cout << "Compare this checksum with the checksum generated for your text when you generated your qr code." << endl;
                cout << "  - If the checksums match, the qr code was not tampered with." << endl;
                cout << "  - If they don't, someone messed with your qr code and you cannot trust the decoded data." << endl;
            }
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
