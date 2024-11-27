#include "Image.h"
#include "Color.h"

#include <vector>
#include <iostream>
#include <cstdint>

using namespace std;

Image::Image() {
    width = 0;
    height = 0;
}

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    rowLength = width * Image::COLOR_WIDTH;
    pixels.resize(rowLength * height);
}

void Image::setPixel(int y, int x, Color color) {
    int pixelIndex = (y * rowLength) + (Image::COLOR_WIDTH * x);
    pixels.at(pixelIndex + 2) = color.r;
    pixels.at(pixelIndex + 1) = color.g;
    pixels.at(pixelIndex    ) = color.b;

}

Color Image::getPixel(int y, int x) {
    Color color;
    int pixelIndex = (y * rowLength) + (Image::COLOR_WIDTH * x);
    color.r = pixels.at(pixelIndex + 2);
    color.g = pixels.at(pixelIndex + 1);
    color.b = pixels.at(pixelIndex    );
    return color;
}

// vector<uint8_t> Image::getPixels() {
//     return pixels;
// }

int Image::getRowLength() {
    return rowLength;
}

uint8_t* Image::getRowAddress(int rowIndex) {
    // calculate the start address of a row of pixel data
    // SOURCE: https://cplusplus.com/reference/vector/vector/data/
    // SOURCE DESCRIPTION: vector.data() returns a direct pointer to the memory array used internally by the vector to store its owned elements
    return pixels.data() + (rowIndex * rowLength);
}

int Image::getWidth() {
    return width;
}

int Image::getHeight() {
    return height;
}

void Image::print() {
    // for (int y = 0; y < height; y++) {
    //     for (int x = 0; x < width * 3; x+=3) {
    //         cout << "rgb(";
    //         cout << (int) pixels.at(y * (width * 3) + x + 2) << ", ";
    //         cout << (int) pixels.at(y * (width * 3) + x + 1) << ", ";
    //         cout << (int) pixels.at(y * (width * 3) + x) << ")";
    //         cout << "\t";
    //     }
    //     cout << "\n";
    // }

    for (int i = 0; i < pixels.size(); i++) {
        cout << (int) pixels.at(i) << " ";
        if ((i + 1) % (width * 3) == 0) {
            cout << endl;
        }
    }
}
