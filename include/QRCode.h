// SOURCE: https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
// SOURCE DESCRIPTION: #pragma once precomplier annotation replaces header guards in new C++ complier
#pragma once

#include "ColorPalette.h"

#include <string>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

class QRCode {
    public:
        // static variables
        static vector<string> paletteNames;
        static const int size = 21;

        // static methods
        // SOURCE: https://www.geeksforgeeks.org/static-member-function-in-cpp/#
        // SOURCE DESCRIPTION: sytax for C++ static class member functions
        static void describeProcess();
        static string scan(string);
        static void checksum(QRCode, string); // FIXME : should it be in this class?
        static void printPalettes();

        // constructor
        QRCode(string);

        // instance methods
        // void regenerate(string); is this worth adding to the interface?
        // void setColor(string); hexadecimal color foreground
        string getText() const;
        void setPalette(string);
        void generate();
        void printNumerical() const;
        void print() const;
        void download() const;
    private:
        // static variables
        static vector<vector<bool> > reserved;
        static vector<ColorPalette> palettes;
        static vector<int> letterToNums(char letter);

        // instance variables
        int paletteIndex;
        string text;
        vector< vector <int> > qrCode;

        // instance methods
};
