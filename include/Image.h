#pragma once

#include "Color.h"

#include <vector>
#include <cstdint>

using namespace std;

// color image
class Image {
    public:
        Image();
        Image(int width, int height);
        void setPixel(int y, int x, Color c);
        Color getPixel(int y, int x);
        // vector<uint8_t> getPixels();
        int getWidth();
        int getHeight();
        // return a pointer where the first element of the row begins
        uint8_t* getRowAddress(int rowIndex);
        int getRowLength();
        void print();
        // void toBGR();
        // void toRGB();
    private:
        vector<uint8_t> pixels;
        int width;
        int height;
        int rowLength;
        static const int COLOR_WIDTH = 3;
};
