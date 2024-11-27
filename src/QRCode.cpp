#include "QRCode.h"
#include "utils.h"
#include "Color.h"
#include "ColorPalette.h"
#include "factory.h"
#include "Bitmap.h"
#include "Image.h"

#include <fmt/color.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int decodeColor(ColorPalette, Color);

vector<string> QRCode::paletteNames = makePaletteNames();
vector<ColorPalette> QRCode::palettes = makePalettes();
vector<vector<bool> > QRCode::reserved  = makeReserved();
const int QRCode::SQUARE_SIZE = 25;

/*
* Contructor
* args:
*   - string text
*/
QRCode::QRCode(string text) {
    paletteIndex = 0;
    this->text = text;
    qrCode.resize(QRCode::size);
    for (int i = 0; i < qrCode.size(); i++) {
        qrCode.at(i).resize(QRCode::size);
    }
}

/*
* getText - gets QR code text
* args:
* return: string
*/
string QRCode::getText() const {
    cout << "Your Text" << endl;
    return text;
}

void QRCode::setPalette(string palette){
    for (int i = 0; i < paletteNames.size(); i++) {
        if (lowerString(palette) == paletteNames.at(i)) {
            paletteIndex = i;
            break;
        }
    }
}

void QRCode::printPalettes() {
    for (int i = 0; i < QRCode::paletteNames.size(); i++){
        cout << setw(9) << left << QRCode::paletteNames.at(i) << ": ";
        palettes.at(i).print();
        cout << endl << endl;
    }
}

/*
* print - prints the QR code to the terminal
* args:
* return: void
*/
void QRCode::printNumerical() const {
    cout << "Printing QR Code" << endl;
    cout << "Palette: " << QRCode::paletteNames.at(paletteIndex) << endl;;
    for (int i = 0; i < qrCode.size(); i++) {
        for (int j = 0; j < qrCode.size(); j++) {
            cout << setw(2) << qrCode.at(i).at(j) << " ";
        }
        cout << endl;
    }
}

void QRCode::print() const {
    ColorPalette palette = QRCode::palettes.at(paletteIndex);
    for (int i = 0; i < qrCode.size(); i++) {
        for (int j = 0; j < qrCode.size(); j++) {
            Color color = palette.get(qrCode.at(i).at(j));
            color.print();
        }
        cout << endl;
    }
}

/*
* download - downloads the QR code
* args:
* return: void
*/
void QRCode::download() const {
    cout << "Downloading QR Code..." << endl;
    ColorPalette palette = QRCode::palettes.at(paletteIndex);
    const int PIXELS = qrCode.size() * QRCode::SQUARE_SIZE;
    Image image(PIXELS, PIXELS);
    cout << PIXELS << endl;
    for (int row = 0; row < qrCode.size(); row++) {
        for (int col = 0; col < qrCode.size(); col++) {
            Color color = palette.get(qrCode.at(row).at(col));
            for (int y = 0; y < QRCode::SQUARE_SIZE; y++) {
                for (int x = 0; x < QRCode::SQUARE_SIZE; x++) {
                    int yPixelIndex = row * QRCode::SQUARE_SIZE + y;
                    int xPixelIndex = col * QRCode::SQUARE_SIZE + x;
                    image.setPixel(yPixelIndex, xPixelIndex, color);
                }
            }
        }
    }

    Bitmap bitmap(image);
    bitmap.download("qrCode.bmp");

    cout << "Finished!" << endl;
}

/*
* describeProcess - outputs a description of the QR code process
* args:
* return: void
*/
void QRCode::describeProcess() {
    cout << "Here is how the QR code is created" << endl;
}

/*
* decode - decodes the QR code given a bitmap
* args:
*   - string path
* return: string
*/
string QRCode::scan(string fileName) {
    Image image = Bitmap::load(fileName);

    // validate if image can be decoded into a qrcode

    // check orientation

    // create vector to store the qrcode data in
    vector<vector<int> > qrCode;
    qrCode.resize(QRCode::size);
    for (int i = 0; i < qrCode.size(); i++) {
        qrCode.at(i).resize(QRCode::size);
    }

    // get color palette used for the qr code from the image data
    ColorPalette palette;
    for (int i = 0; i < 11; i++) {
        Color c = image.getPixel((image.getHeight() - 1) - (i * QRCode::SQUARE_SIZE), image.getWidth() - 1);
        palette.addColor(c);
    }
    cout << "Palette:";
    palette.print();
    cout << endl;

    // minimize the pixel data into qr code data dimensions and decode each color to an integer btw 0-11
    for (int i = 0; i < qrCode.size(); i++) {
        for (int j = 0; j < qrCode.size(); j++) {
            int y = QRCode::SQUARE_SIZE * i;
            int x = QRCode::SQUARE_SIZE * j;
            Color c = image.getPixel(y, x);
            qrCode.at(i).at(j) = decodeColor(palette, c);
        }
    }

    // print text version of qr code
    for (int i = 0; i < qrCode.size(); i++) {
        for (int j = 0; j < qrCode.size(); j++) {
            cout << setw(2) << qrCode.at(i).at(j) << " ";
        }
        cout << endl;
    }

    string decodedText = "";
    // getting message length
    vector<int> digits(3);
    int textLength = 0;
    for (int i = 0; i < 3; i++) {
        int lengthDigit = qrCode.at(qrCode.size() - 12 - i).at(qrCode.size() - 1);
        digits.at(i) = lengthDigit;
    }
    textLength = digits.at(0) + (digits.at(1) * 10) + (digits.at(2) * 100);
    cout << "Text Length: " << textLength << endl;

    // decoding the message
    bool fromBottom = true;
    int digitIndex = 0;

    // traversing qr code grid from the last column to the first column
    for (int col = qrCode.size() - 1; col >= 0; col--) {
        // walks up a column
        for (int row = qrCode.size() - 1; fromBottom && (row >= 0); row--) {
            // getting each char which occupies 3 spaces
            if (!reserved.at(row).at(col)) {
                digits.at(digitIndex) = qrCode.at(row).at(col);
                digitIndex++;
                if (digitIndex == 3) {
                    // covert the 3 digit number to a letter and append it
                    decodedText += QRCode::numsToLetter(digits);
                    // removes all elements fro the vector and gives the vector a size of 0
                    // digits.clear(); // SOURCE: https://cplusplus.com/reference/vector/vector/clear/
                    digitIndex = 0;
                    if (decodedText.size() == textLength) {
                        cout << "Your text is: " << decodedText << endl;
                        return decodedText;
                    }
                }
            }
        }

        // walks down a column
        for (int row = 0; !fromBottom && row < qrCode.size(); row++) {
            // getting each char which occupies 3 spaces
            if (!reserved.at(row).at(col)) {
                digits.at(digitIndex) = qrCode.at(row).at(col);
                digitIndex++;
                if (digitIndex == 3) {
                    // covert the 3 digit number to a letter and append it
                    decodedText += QRCode::numsToLetter(digits);
                    // removes all elements fro the vector and gives the vector a size of 0
                    // digits.clear(); // SOURCE: https://cplusplus.com/reference/vector/vector/clear/
                    digitIndex = 0;

                    if (decodedText.size() == textLength) {
                        cout << "Your text is: " << decodedText << endl;
                        return decodedText;
                    }
                }
            }
        }
        fromBottom = !fromBottom;
    }

    // get test from qr code
    return "";
}

// using the '&' due to suggestion from chatGPT because passing a vector by reference using
// the '&' symbol means that you are passing the memory address of the vector to the function,
// rather than creating a copy of the vector, which is more efficient.
char QRCode::numsToLetter(const vector<int>& digits) {
    int value = digits.at(0) + (digits.at(1) * 10) + (digits.at(2) * 100);
    return static_cast<char>(value);
}

int decodeColor(ColorPalette palette, Color c) {
    for (int i = 0; i < palette.size(); i++) {
        Color color = palette.get(i);
        if (color.r == c.r && color.g == c.g && color.b == c.b) {
            // cout << "decoded: " << i << endl;
            return i;
        }
    }
    return -1;
}

/*
* checksum - verifies that QR code comes from specifed text
* args:
*   - QRCode qr
*   - string text
* return: void
*/
void QRCode::checksum(QRCode qr, string text) {
    cout << "Checksum" << endl;
}


void QRCode::generate() {
    // set the orientation squares

    //set horizontal parts to color 10 of the orientation squares
    for (int i = 0; i < 5; i++) {
        // row at index 0
        qrCode.at(0).at(i) = 10;
        qrCode.at(0).at(qrCode.size() - 1 - i) = 10;
        // row at index 4
        qrCode.at(4).at(i) = 10;
        qrCode.at(4).at(qrCode.size() - 1 - i) = 10;
        // row at index 16
        qrCode.at(16).at(i) = 10;
        // row at index 20
        qrCode.at(20).at(i) = 10;
    }

    //set vertical parts to color 10 of the orientation squares
    for (int i = 1; i < 4; i++) {
        // column at index 0 top and bottom squares
        qrCode.at(i).at(0) = 10;
        qrCode.at(qrCode.size() - 1 - i).at(0) = 10;
        // column at index 4 top and bottom squares
        qrCode.at(i).at(4) = 10;
        qrCode.at(qrCode.size() - 1 - i).at(4) = 10;
        // column at index 16 - third square
        qrCode.at(i).at(16) = 10;
        // column at index 20 - third square
        qrCode.at(i).at(20) = 10;
    }

    // middle dots of the orienation squares
    qrCode.at(2).at(2) = 10;
    qrCode.at(2).at(18) = 10;
    qrCode.at(18).at(2) = 10;

    // set the colors and
    for (int i = 0; i <= 10; i++) {
        qrCode.at(qrCode.size() - 1 - i).at(qrCode.size() - 1) = i;
    }
    // set message length in the qr code
    int textLength = text.size();
    for (int i = 0; i < 3; i++) {
        int digit = textLength % 10;
        textLength /= 10;
        qrCode.at(qrCode.size() - 12 - i).at(qrCode.size() - 1) = digit;
    }

    // put the message in
    bool fromBottom = true;
    int letterIndex = 0;
    int digitIndex = 0;
    vector<int> digits = QRCode::letterToNums(text.at(letterIndex));

    // traversing qr code grid from the last column to the first column
    for (int col = qrCode.size() - 1; col >= 0; col--) {
        // walks up a column
        for (int row = qrCode.size() - 1; fromBottom && (row >= 0); row--) {
            // setting each box in the qr code grid to the digit representation of the letter, each taking 3 spaces
            if (!reserved.at(row).at(col)) {
                if (letterIndex == text.size()) {
                    //generate random num btw 0 - 9 to fill the rest
                    qrCode.at(row).at(col) = rand() % 10;
                }
                else {
                    qrCode.at(row).at(col) = digits.at(digitIndex);
                    digitIndex++;
                    if (digitIndex == 3) {
                        digitIndex = 0;
                        letterIndex++;
                        if (letterIndex != text.size()) {
                            digits = QRCode::letterToNums(text.at(letterIndex));
                        }
                    }
                }
            }
        }
        // walks down a column
        for (int row = 0; !fromBottom && row < qrCode.size(); row++) {
            // setting each box in the qr code grid to the digit representation of the letter, each taking 3 spaces
            if (!reserved.at(row).at(col)) {
                if (letterIndex == text.size()) {
                    //generate random num btw 0 - 9 to fill the rest
                    qrCode.at(row).at(col) = rand() % 10;
                }
                else {
                    qrCode.at(row).at(col) = digits.at(digitIndex);
                    digitIndex++;
                    if (digitIndex == 3) {
                        digitIndex = 0;
                        letterIndex++;
                        if (letterIndex != text.size()) {
                            digits = QRCode::letterToNums(text.at(letterIndex));
                        }
                    }
                }
            }
        }
        fromBottom = !fromBottom;
    }
}

vector<int> QRCode::letterToNums(char letter) {
    int digits = letter;
    vector<int> digitVector(3);
    for (int i = 0; i < 3; i++) {
        int digit = digits % 10;
        digits /= 10;
        digitVector.at(i) = digit;
    }
    return digitVector;
}
