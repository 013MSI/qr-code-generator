#pragma once

#include "ColorPalette.h"
#include <iostream>
#include <vector>

using namespace std;

class Bitmap {
    public:
        Bitmap(vector<vector<int> >, int, ColorPalette);
        void download(string);
        static vector<vector<int> > decode(string);
    private:
        void writeImage(unsigned char*, string);
        unsigned char* createFileHeader (int, int);
        unsigned char* createInfoHeader (int, int );

        vector<vector<int> > data;
        int height;
        int width;
        int squareSize;
        ColorPalette palette;

        static const int BYTES_PER_PIXEL = 3; /// red, green, & blue
        static const int FILE_HEADER_SIZE = 14;
        static const int INFO_HEADER_SIZE = 40;
};
