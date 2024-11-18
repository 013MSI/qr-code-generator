#include "QRCode.h"
#include <string>
#include <iostream>

using namespace std;

QRCode::QRCode() {
    cout << "Default constructor" << endl;
}

QRCode::QRCode(string text) {
    cout << "Single argument constructor with text" << endl;
}

void QRCode::print() {
    cout << "Printing QR Code" << endl;
}

void QRCode::download() {
    cout << "Downloading QR Code..." << endl;
}
