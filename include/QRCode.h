// SOURCE: https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
// SOURCE DESCRIPTION: #pragma once precomplier annotation replaces header guards in new C++ complier
#pragma once

#include "ColorPalette.h"
#include "Color.h"
#include "Image.h"

#include <string>
#include <vector>

using namespace std;

class QRCode {
    public:
        // static variables
        static const int SIZE = 21;
        static const int MAX_LEN = 109;

        // static methods
        // SOURCE: https://www.geeksforgeeks.org/static-member-function-in-cpp/#
        // SOURCE DESCRIPTION: sytax for C++ static class member functions
        static string scan(const string& path);

        // constructor
        QRCode(string);

        // instance methods
        string getText() const;
        void print(const ColorPalette& palette, const Color& c1, const Color& c2) const;
        bool download(const string& path, const ColorPalette& palette, const Color& c1, const Color& c2) const;
    private:
        // static variables
        static vector<vector<int>> logoTemplate;
        static vector<vector<bool>> reserved;
        // how many pixels each qr code square should be when it is downloaded
        // eg. 25 pixels by 25 pixels
        static const int SQUARE_SIZE = 10;
        static const int LOGO_START_INDEX = 7;
        static const int LOGO_END_INDEX = 13;

        // static helper methods
        // encoding
        static vector<int> letterToDigits(char letter);
        static bool inLogoArea(int row, int col);
        static void expandToPixels(Image& image, int row, int col, const Color& c);
        static void writeLogoToImage(Image& image, const Color& c1, const Color& c2);
        // deocoding
        static Image rotateImage(const Image& image, int);
        static vector<vector<int>> minimizeToData(const Image& image, const ColorPalette& palette);
        static bool checkOrientationSquares(const vector<vector<int>>& data);
        static char digitsToLetter(const vector<int>& digits);
        static int decodeColor(const ColorPalette& palette, const Color& c);
        static bool contains(const vector<Color>& colors, const Color& c);
        // both
        static bool isValidPalette(const ColorPalette& palette);

        // instance variables
        string text;
        vector<vector<int>> qrCode;
};
