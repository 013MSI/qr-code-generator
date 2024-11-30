// Image.h

#pragma once

#include "Color.h"
#include <vector>
#include <cstdint>

using namespace std;

/*
 * Represents a 2D color image.
 *
 * Provides functionality to manipulate individual pixels, get image dimensions,
 * and retrive low level byte information.
 *
 * Designed to work with the Bitmap class.
 */
class Image {
    public:
        /*
        * Creates an empty image with zero width and height.
        */
        Image();

        /*
        * Creates an image with the specified dimensions.
        *
        * params:
        *   width - The width of the image in pixels.
        *   height - The height of the image in pixels.
        */
        Image(int width, int height);

        /*
        * Sets the color of a specific pixel in the image.
        *
        * params:
        *   y - The row (vertical) index of the pixel.
        *   x - The column (horizontal) index of the pixel.
        *   c - The Color object representing the pixel's color.
        */
        void setPixel(int y, int x, const Color& c);

        /*
        * Retrieves the color of a specific pixel in the image.
        *
        * params:
        *   y - The row (vertical) index of the pixel.
        *   x - The column (horizontal) index of the pixel.
        * return The Color object representing the pixel's color.
        */
        Color getPixel(int y, int x) const;

        /*
        * Gets the width of the image in pixels.
        *
        * return The width of the image.
        */
        int getWidth() const;

        /*
        * Gets the height of the image in pixels.
        *
        * return The height of the image.
        */
        int getHeight() const;

        /*
        * Retrieves a pointer to the first element of a specified row in the image.
        *
        * params:
        *   rowIndex - A (0-based) row index.
        * return A pointer to the first byte of the row's pixel data.
        */
        uint8_t* getRowAddress(int rowIndex);

        /*
        * Gets the length of a row in bytes
        * (the number of pixels in a row * 3 bytes per pixel for the color)
        *
        * return The length of a single row in the image, in bytes.
        */
        int getRowLength() const;

    private:
        /*
        * The number of bytes per color (Red, Green, Blue).
        */
        static const int COLOR_WIDTH = 3;

        // The raw pixel data of the image stored as a 1D vector.
        // Each pixel is represented by three consecutive bytes (B, G, R).
        vector<uint8_t> pixels;
        //The width of the image in pixels
        int width;
        // The height of the image in pixels.
        int height;
        // The length of a single row in the image, in bytes.
        int rowLength;
};
