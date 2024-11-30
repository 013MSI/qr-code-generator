// qrActions.cpp

#include "qrActions.h"
#include "factory.h"
#include "constants.h"
#include "QRCode.h"
#include "checksum.h"
#include "ColorPalette.h"
#include "utils.h"
#include "fmt/color.h"
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>
#include <iomanip>

using namespace std;

// SOURCE: https://github.com/fmtlib/fmt/blob/master/include/fmt/color.h
// DESCRIPTION: fmt named colors

// SOURCE: https://github.com/fmtlib/fmt?tab=readme-ov-file
// DESCRIPTION: fmt github repo + documentation

// create color palette information
const vector<ColorPalette> palettes = makePalettes();
const vector<char> paletteIndices = {'1', '2', '3'};
const vector<string> paletteNames = {"grayscale", "autumn", "ocean"};

void generate() {
    string text = getMessage();
    ColorPalette palette = getPalette();
    fmt::print(fmt::emphasis::bold, "\nGenerating...\n\n");

    // create qr code with user message
    QRCode qrCode(text);
    // user specified palette + black and white for logo
    qrCode.print(palette, Color(255, 255, 255), Color(0, 0, 0));

    // print checksum info
    cout << endl << "Checksum: " << checksum(text) << endl;
    cout << "Save the checksum so you can verify your message later." << endl;
    cout <<"Check out this website to learn about how your qr code was generated: ";
    fmt::print(fmt::emphasis::italic, LINK);
    cout << endl << endl;

    downloadQRCode(qrCode, palette);
}

void scan() {
    bool tryScan = true;
    bool isFirstAttempt = true;
    string path;

    while (tryScan) {
        // SOURCE: https://www.w3schools.com/cpp/cpp_exceptions.asp
        // DESCRIPTION: Exception handling in c++
        try {

            if (isFirstAttempt) {
                cout << "Enter the location to your qr code (ex. ";
                fmt::print(fmt::emphasis::italic, "/Users/myUser/qrCode.bmp");
                cout << ") or \'q\' to abort scan.\n";
                path = getText(PROMPT);
            } else {
                path = getText("Type a new path or \'q\' to abort scan: ");
            }

            // quit case
            if (path.size() == 1 && path.at(0) == QUIT) {
                tryScan = false;
            } else { // if not quit, try to decode the .bmp file
                string decodedText = QRCode::scan(path);
                fmt::print(fmt::emphasis::bold, "\nScanning...\n\n");
                cout << "Your message is \"" << decodedText << "\"\n\n";
                cout << "Checksum: " << checksum(decodedText) << endl;
                cout << "Compare this checksum with the checksum generated for your text when you created your qr code.\n";
                cout << "  - If the checksums match, the qr code was not tampered with.\n";
                cout << "  - If they don't, someone messed with your qr code and you can\'t trust the decoded data.\n";
                tryScan = false;
            }

            if (isFirstAttempt) {
                isFirstAttempt = false;
            }

        } catch (const ios_base::failure& e) {

            if (isFirstAttempt) {
                fmt::print(fg(fmt::color::fire_brick), "{}\n",
                    "Sorry we couldn't find your qr code :(. Double check that your path is correct.");
            } else {
                fmt::print(fg(fmt::color::fire_brick), "Hmmm...we can\'t find your qr code...\n");
            }

            if (isFirstAttempt) {
                isFirstAttempt = false;
            }
        }
    }
}

string getMessage() {
    char isCorrectMessage = 'n';
    string text;
    while (isCorrectMessage == 'n') {
        text = getText("Text: ");
        if (text.length() > QRCode::MAX_LEN) {
            fmt::print(fg(fmt::color::dark_salmon), "Yikes! Your message is too long to encode. Try something shorter.\n");
        } else {
            cout << "The message to encode is \"" << text << "\"\n";
            cout << "Is that correct? (\'y\' to confirm, 'n' to enter a new message)\n";
            isCorrectMessage = getYesNo(PROMPT);
        }
    }
    return text;
}

ColorPalette getPalette() {
    // get color palette for qr code
    fmt::print(fmt::emphasis::underline, "\nSelect a color palette\n\n");
    // print palettes
    for (int i = 0; i < paletteNames.size(); i++){
        cout << "[" << paletteIndices.at(i) << "] ";
        cout << setw(9) << left << paletteNames.at(i) << ": ";
        palettes.at(i).print();
        cout << endl << endl;
    }
    char paletteIndex = getChar(PROMPT, paletteIndices);
    // SOURCE: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
    // DESCRIPTION: how to convert a number character to an integer
    ColorPalette palette = palettes.at(paletteIndex - '0' - 1);
    return palette;
}

void downloadQRCode(QRCode& qrCode, ColorPalette& palette) {
    string path;
    cout << "Download? (y/n)\n";
    char download = getYesNo(PROMPT);
    if (download == 'y') {
        bool tryDownload = true;
        bool isFirstAttempt = true;
        while (tryDownload) {
            try {

                if (isFirstAttempt) {
                    cout << "Enter a location to save your qr code (ex. ";
                    fmt::print(fmt::emphasis::italic, "/Users/myUser/qrCode.bmp");
                    cout << ") or \'q\' to stop download.\n";
                    path = getText(PROMPT);
                } else {
                    path = getText("Type a new path or \'q\' to stop download: ");
                }

                // quit case
                if (path.size() == 1 && path.at(0) == QUIT) {
                    tryDownload = false;
                } else { // if not quit, try to download to path
                    qrCode.download(path, palette, Color(255, 255, 255), Color(0, 0, 0));
                    fmt::print(fg(fmt::color::medium_sea_green), "\nDownloaded successfully!\n");
                    cout << "Check ";
                    fmt::print(fmt::emphasis::italic, path);
                    cout << " to view your new qr code.\n";
                    tryDownload = false;
                }

                if (isFirstAttempt) {
                    isFirstAttempt = false;
                }

            } catch (const ios_base::failure& e) {

                if (isFirstAttempt) {
                    fmt::print(fg(fmt::color::fire_brick), "{}\n{}\n",
                        "Sorry we couldn't download your qr code to that location :(",
                        "Double check that all the folders in your path exist and that you are specifying a .bmp file at the end.");
                } else {
                    fmt::print(fg(fmt::color::fire_brick), "Hmmm...we can\'t download your qr code to that location...\n");
                }

                if (isFirstAttempt) {
                    isFirstAttempt = false;
                }
            }
        }
    }
}
