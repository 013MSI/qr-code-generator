// Bitmap.h

// SOURCE: https://stackoverflow.com/questions/5776910/what-does-pragma-once-mean-in-c
// DESCRIPTION: #pragma once precomplier annotation replaces header guards in modern C++ compliers
#pragma once

#include "Color.h"
#include "Image.h"
#include <cstdint>
#include <vector>

using namespace std;

// SOURCE: https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html
// DESCRIPTION: Detailed description of the BMP file format.

// SOURCE: https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/ (article)
//         https://github.com/sol-prog/cpp-bmp-images/blob/master/BMP.h (github)
// DESCRIPTION: Article describing reading and writing BMP files in C++.
// Code for header structs + implementation of download and load methods of Bitmap class are adapted from the the contents of the article.

// SOURCE: https://stackoverflow.com/questions/44620755/c-the-compiler-is-changing-the-alignment-of-my-structures-how-can-i-prevent-t
// DESCRIPTION: Use of pragma pack prevent the compiler from automatically padding the structure to align the data in memory differently.
// Ensure that the below struct takes up exactly 14 bytes.
#pragma pack(1)
struct BitmapFileHeader {
    uint16_t fileType = 0x4D42;     // Always BM to declare this a .bmp file.
    uint32_t size = 0;              // Size of file in bytes.
    uint16_t reserved1 = 0;         // Must always be set to zero.
    uint16_t reserved2 = 0;         // Must always be set to zero.
    uint32_t offSet = 0;            // The number of bytes from the beginning where the pixel data begins.
};

// Ensures that the below struct takes up exactly 40 bytes.
struct BitmapInfoHeader {
    uint32_t size = 40;             // Size of info header, in bytes.
    uint32_t width = 0;             // Width of image, in pixels.
    uint32_t height = 0;            // Height of image, in pixels.
    uint16_t planes = 1;            // Typically set to 1.
    uint16_t bitsPerPixel = 24;     // Specifies the number of bits per pixel, 24 for RGB (8 per color channel).
    uint32_t compression = 0;       // Usually set to 0.
    uint32_t imageSize = 0;         // If no compression, valid to set to 0.
    uint32_t xPixelsPerMeter = 0;   // Usually set to 0.
    uint32_t yPixelsPerMeter = 0;   // Usually set to 0.
    uint32_t numColors = 0;         // If set to zero the number of colors is calculated using bitsPerPixel.
    uint32_t numImportantColors = 0;// Set to 0 if all colors are important.
};
#pragma pack()

/*
 * Represents a Bitmap image, providing functionality for loading and saving BMP files.
 */
class Bitmap {
    public:
        /*
        * Loads a BMP file from the specified path and converts it into an Image object.
        *
        * param:
        *   path - The path of the BMP file to load.
        * return: An Image object containing the pixel data.
        * throws std::ios_base::failure. Reasons for exception include:
        *   - invalid path to BMP file passed as argument
        *   - file can't be opened (perhaps because the path does not exist)
        *   - failure to read from file
        *   - file is not a BMP file
        */

        // SOURCE: https://en.cppreference.com/w/cpp/io/ios_base/failure
        // DESCRIPTION: Documentation for std::ios_base::failure exception

        // SOURCE: https://www.geeksforgeeks.org/static-member-function-in-cpp/#
        // DESCRIPTION: Syntax for C++ static class member functions
        static Image load(const string& path);

        /*
        * Constructs a Bitmap object from an Image object.
        *
        * param:
        *   image - An Image object containing pixel data to be stored in the Bitmap.
        */
        Bitmap(const Image& image);

        /*
        * Saves the Bitmap object to a BMP file at the specified path.
        *
        * param:
        *   path - The file path to save the BMP file to.
        * throws std::ios_base::failure. Reasons for exception include:
        *   - invalid path to BMP file passed as argument
        *   - file can't be opened or created (perhaps because the path does not exist)
        *   - failure to write to file
        */
        void download(const string& path);

    private:
        /*
        * Validates the given file path for a BMP file.
        *
        * param:
        *   path - The file path to validate.
        * return true if the path is valid, false if the path is invalid.
        */
        static bool isValidPath(const string& path);

        /*
        * Calculates the padding needed for a row of pixel data in a BMP file.
        * Rows are aligned to 4-byte boundaries in BMP files.
        *
        * param:
        *   rowLength - The length of the row in bytes.
        * return The number of padding bytes required.
        */
        static int calculatePadding(int rowLength);

        // File header containing general file information.
        BitmapFileHeader bmfh;
        // Info header containing image-specific details.
        BitmapInfoHeader bmih;
        // The pixel data of the Bitmap, stored as an Image object.
        Image image;
        // Padding required for 4-byte alignment of rows in the BMP file.
        int padding;
};
