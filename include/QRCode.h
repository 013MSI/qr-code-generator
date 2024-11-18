// SOURCE: https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
// SOURCE DESCRIPTION: #pragma once precomplier annotation replaces header guards in new c++ complier
#pragma once

#include <string>
#include <vector>

using namespace std;

class QRCode {
    public:
        QRCode();
        QRCode(string);
        void print();
        void download();
    private:
        vector< vector <bool> > qrCode;

};
