#pragma once

#include "Color.h"
#include "Image.h"

#include <cstdint>
#include <vector>

using namespace std;

// SOURCE: https://stackoverflow.com/questions/44620755/c-the-compiler-is-changing-the-alignment-of-my-structures-how-can-i-prevent-t
// used to prevent the compiler from automatically padding the structure to align the data in memory differently
// eg. we want to ensure that the below struct takes up exactly 14 bytes
#pragma pack(1)
struct BitmapFileHeader {
    uint16_t fileType = 0x4D42;     // always BM to declare this a .bmp file
    uint32_t size = 0;              // size of file in bytes
    uint16_t reserved1 = 0;         // must always be set to zero
    uint16_t reserved2 = 0;         // must always be set to zero
    uint32_t offSet = 0;            // the number of bytes from the beginning where the pixel data begins
};

// 40 bytes
struct BitmapInfoHeader {
    uint32_t size = 40;             // size of info header, in bytes
    uint32_t width = 0;             // width of image, in pixels
    uint32_t height = 0;            // height of image, in pixels
    uint16_t planes = 1;            // typically set to 1
    uint16_t bitsPerPixel = 24;     // specifies the number of bits per pixel, 24 for rgb (8 per color channel)
    uint32_t compression = 0;       // usually set to 0
    uint32_t imageSize = 0;         // if no compression, valid to set to 0
    uint32_t xPixelsPerMeter = 0;   // usually set to 0
    uint32_t yPixelsPerMeter = 0;   // usually set to 0
    uint32_t numColors = 0;        // if set to zero the number of colors is calculated using bitsPerPixel
    uint32_t numImportantColors = 0;// set to 0 if all colors are important
};
#pragma pack()

class Bitmap {
    public:
        Bitmap(Image image);
        bool download(string fileName);
        static Image load(string fileName);
    private:
        BitmapFileHeader bmfh;
        BitmapInfoHeader bmih;
        Image image;
        int padding;
        static int calculatePadding(int rowLength);
};
