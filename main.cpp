#include <iostream>
#include "QRCode.h"

using namespace std;

int main() {
    QRCode::describeProcess();

    cout << endl;

    QRCode qrCode1("My text to turn into a QR Code");

    cout << "QR Code 1: " << endl;
    qrCode1.getText();
    qrCode1.print();
    qrCode1.download();

    return 0;
}
