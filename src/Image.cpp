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

void Image::setPixel(int y, int x, const Color& color) {
    int pixelIndex = (y * rowLength) + (Image::COLOR_WIDTH * x);
    pixels.at(pixelIndex + 2) = color.r;
    pixels.at(pixelIndex + 1) = color.g;
    pixels.at(pixelIndex    ) = color.b;
}

Color Image::getPixel(int y, int x) const {
    Color color;
    int pixelIndex = (y * rowLength) + (Image::COLOR_WIDTH * x);
    color.r = pixels.at(pixelIndex + 2);
    color.g = pixels.at(pixelIndex + 1);
    color.b = pixels.at(pixelIndex    );
    return color;
}

int Image::getRowLength() const {
    return rowLength;
}

uint8_t* Image::getRowAddress(int rowIndex) {
    // calculate the start address of a row of pixel data
    // SOURCE: https://cplusplus.com/reference/vector/vector/data/
    // DESCRIPTION: vector.data() returns a direct pointer to the memory array used internally by the vector to store its owned elements
    return pixels.data() + (rowIndex * rowLength);
}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}
