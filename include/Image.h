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
        void setPixel(int y, int x, const Color& c);
        Color getPixel(int y, int x) const;
        int getWidth() const;
        int getHeight() const;
        // return a pointer where the first element of the row begins
        uint8_t* getRowAddress(int rowIndex);
        int getRowLength() const;
        // TODO: delete this
        void print() const;
    private:
        vector<uint8_t> pixels;
        int width;
        int height;
        int rowLength;
        static const int COLOR_WIDTH = 3;
};
