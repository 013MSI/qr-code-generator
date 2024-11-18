#include "QRCode.h"
#include <string>
#include <iostream>

using namespace std;

/*
* Contructor
* args:
*   - string text
*/
QRCode::QRCode(string text) {
    cout << "Single argument constructor with text" << endl;
    cout << text << endl << endl;
}

/*
* encode - coverts text into QR code
* args:
* return: void
*/
void QRCode::encode() {
    cout << "Encode the string" << endl;
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

/*
* print - prints the QR code to the terminal
* args:
* return: void
*/
void QRCode::print() const {
    cout << "Printing QR Code" << endl;
}

/*
* download - downloads the QR code
* args:
* return: void
*/
void QRCode::download() const {
    cout << "Downloading QR Code..." << endl;
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
string QRCode::scan(string path) {
    cout << "Decoding..." << endl;
    cout << "Your text is: " << endl;
    return "";
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
