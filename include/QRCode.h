// SOURCE: https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
// SOURCE DESCRIPTION: #pragma once precomplier annotation replaces header guards in new C++ complier
#pragma once

#include <string>
#include <vector>

using namespace std;

class QRCode {
    public:
        QRCode(string);
        // void regenerate(string); is this worth adding to the interface?
        // void setColor(string); hexadecimal color foreground
        // void setShape(string); set shape of the squares (circle, square, start, triangle, heart)
        string getText() const;
        void print() const;
        void download() const;

        // SOURCE: https://www.geeksforgeeks.org/static-member-function-in-cpp/#
        // SOURCE DESCRIPTION: sytax for C++ static class member functions
        static void describeProcess();
        static string scan(string);
        static void checksum(QRCode, string); // change name to verify?
    private:
        string text;
        // string color = "black";
        // string shape = "square";
        vector< vector <bool> > qrCode;
        void encode();
};
