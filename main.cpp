#include <iostream>
#include "QRCode.h"
#include "include/QRCode.h"

using namespace std;

int main() {
    QRCode qrCode1;
    QRCode qrCode2("My text to turn into a QR Code");

    cout << "QR Code 1: " << endl;
    qrCode1.print();
    qrCode1.download();

    cout << endl;

    cout << "QR Code 2: " << endl;
    qrCode2.print();
    qrCode2.download();
    return 0;
}
