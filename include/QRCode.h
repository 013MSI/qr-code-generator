// QRCode.h

#pragma once

#include "ColorPalette.h"
#include "Color.h"
#include "Image.h"

#include <string>
#include <vector>

using namespace std;

/*
 * Represents a QR code and provides functionality for encoding, decoding, rendering, and saving QR codes.
 */
class QRCode {
    public:
        /*
        * The size of the QR code grid (number of squares in one dimension).
        */
        static const int SIZE = 21;

        /*
        * The maximum length of text that can be encoded in the QR code.
        */
        static const int MAX_LEN = 109;

        /*
        * Decodes the text from a QR code image (a BMP file) located at the given path.
        *
        * param:
        *   path - The file path to the QR code BMP file.
        * return The text encoded in the QR code.
        * throws std::ios_base::failure. Exceptions occur if
        *   - invalid path to bmp file passed as argument
        *   - file can't be read (perhaps bc the path does not exist)
        *   - fail to read file contents
        *.  - file is not a .bmp file
        */
        static string scan(const string& path);

        /*
        * Creates a QRCode object with the specified text.
        *
        * param:
        *   text - The text to encode in the QR code. Text may not exceed QRCode::MAX_LEN.
        */
        QRCode(string);

        /*
        * Gets the text in the QRCode.
        *
        * return The QRCode text.
        */
        string getText() const;

        /*
        * Prints a visual representation of the QR code using the specified color palette and logo colors.
        *
        * params:
        *   palette - The colors to use for coloring the QR code.
        *   c1 - First color for the logo.
        *   c2 - Second color for the logo.
        */
        void print(const ColorPalette& palette, const Color& c1, const Color& c2) const;

        /*
        * Downloads the QR code as an BMP file.
        *
        * params:
        *   path - The file path where the QR code image will be saved.
        *   palette - The color palette to use for the QR code.
        *   c1 - First color for the logo.
        *   c2 - Second color for the logo.
        * throws std::ios_base::failure. Reasons for exception include:
        *   - invalid path to BMP file passed as argument
        *   - file can't be opened or created (perhaps because the path does not exist)
        *   - failure to write to file
        */
        void download(const string& path, const ColorPalette& palette, const Color& c1, const Color& c2) const;
    private:
        // Template for the logo area of the QR code. The logo bg is represented with 2, the first color with 1, and the second color with 0
        // Creating a logo template allows the logo colors to be changed easily
        static vector<vector<int>> logoTemplate;
        // Mark reserved areas in the QR code grid for metadata.
        static vector<vector<bool>> reserved;
        // The size of each square in the QR code when rendered as an image, in pixels.
        static const int SQUARE_SIZE = 10;
        // Start and end indices for the logo area in the QR code grid
        static const int LOGO_START_INDEX = 7;
        static const int LOGO_END_INDEX = 13;

        // =============================================================================================== //
        // ==================================== STATIC HELPER METHODS ==================================== //
        // =============================================================================================== //
        /*
        * Converts a character to its numeric encoding for the QR code.
        *
        * param:
        *   letter - The character to encode.
        * return A vector of integers representing the character's 3 width encoding.
        */
        static vector<int> letterToDigits(char letter);

        /*
        * Checks if a given position is within the logo area of the QR code.
        *
        * params:
        *   row - The row index.
        *   col - The column index.
        * return true if the position is in the logo area, otherwise false.
        */
        static bool inLogoArea(int row, int col);

        /*
        * Expands a logical QR code element into a pixel representation.
        *
        * params:
        *   image - The Image object to modify.
        *   row - The row index of the QR code element.
        *   col - The column index of the QR code element.
        *   c - The color to use for the expanded pixel square.
        */
        static void expandToPixels(Image& image, int row, int col, const Color& c);

        /*
        * Writes a logo into the QR code image.
        *
        * params:
        *   image - The Image object to modify.
        *   c1 - The first logo color.
        *   c2 - The second logo color.
        */
        static void writeLogoToImage(Image& image, const Color& c1, const Color& c2);

        /*
        * Created a rotated copy of an image. Rotates by 90, 180, or 270 degrees counter-clockwise.
        *
        * params:
        *.  image - The image to rotate.
        *   angle - The angle of rotation, in degrees..
        * return The copy of the image data rotated by the specified degrees.
        */
        static Image rotateImage(const Image& image, int);

        /*
        * Reduces an image to its QR code data representation.
        *
        * params:
        *  image - The image to process.
        *  palette - The color palette used in the image.
        * return A 2D vector representing the QR code data.
        */
        static vector<vector<int>> minimizeToData(const Image& image, const ColorPalette& palette);

        /*
        * Verifies the orientation squares in a QR code data grid.
        *
        * param:
        *   data - The QR code data as a 2D grid.
        * return true if the orientation markers are valid, otherwise false.
        */
        static bool checkOrientationSquares(const vector<vector<int>>& data);

        /*
        * Converts a vector of integers to a character.
        *
        * param:
        *.  digits - The numeric encoding of the character.
        * return The decoded character.
        */
        static char digitsToLetter(const vector<int>& digits);

        /*
        * Maps a Color to an integer.
        *
        * params:
        *   palette - The color palette used in the image.
        *   c - The color to decode.
        * return The integer corresponding to the color or -1 if mapping not found.
        */
        static int decodeColor(const ColorPalette& palette, const Color& c);

        /*
        * Checks if a color is contained in a vector of colors.
        *
        * params:
        *   colors - The vector of colors to search.
        *   c - The color to check for.
        * return true if the color is found, otherwise false.
        */
        static bool contains(const vector<Color>& colors, const Color& c);

        /*
        * Validates the compatibility of a color palette with the QR code.
        * A valid palette contains 11 unique colors.
        *
        * param:
        *   palette - The color palette to validate.
        * return true if the palette is valid, otherwise false.
        */
        static bool isValidPalette(const ColorPalette& palette);

        // The text to encode into a QR code.
        string text;
        // A 2D representation of the QR code grid, with integer values.
        vector<vector<int>> qrCode;
};
