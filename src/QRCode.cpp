// QRCode.cpp

#include "QRCode.h"
#include "utils.h"
#include "Color.h"
#include "ColorPalette.h"
#include "qrFactory.h"
#include "Bitmap.h"
#include "Image.h"
#include <fmt/color.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// SOURCE: https://stackoverflow.com/questions/3701903/initialisation-of-static-vector
// DESCRIPTION: How to initialize a static vector attribute
vector<vector<int> > QRCode::logoTemplate = makeLogoTemplate();
vector<vector<bool> > QRCode::reserved = makeReserved();

QRCode::QRCode(string text) {
    // 21 x 21 grid = 441 boxes total
    // orientation squares = 3*(5+5+3+3+1) = 51
    // color data = 11
    // logo area = 7 x 7 = 49
    // size data = 3
    // meta data + logo takes up 114 boxes
    // boxes left for encoding = 327
    // each character is encoded using three boxes so, we can store 327 / 3 = 109 characters max

    // validate text length
    if (text.length() == 0 || text.length() > QRCode::MAX_LEN) {
        throw invalid_argument("invalid text length");
    }
    this->text = text;

    // create empty qrcode with meta data and pixelated logo
    qrCode = makeEmptyQrCode();

    // set message length
    int textLength = text.size();
    for (int i = 0; i < 3; i++) {
        // store current rightmost digit
        int digit = textLength % 10;
        // chop off current rightmost digit
        textLength /= 10;
        // add current rightmost digit to qr code grid
        qrCode.at(qrCode.size() - 12 - i).at(qrCode.size() - 1) = digit;
    }

    // encode message
    bool fromBottom = true;
    int letterIndex = 0, digitIndex = 0;
    vector<int> digits = QRCode::letterToDigits(text.at(letterIndex));

    // traverse qr code grid from the last column to the first column
    // walk up first column traversed and down second column traversed, keep switching direction of column traversal
    int row;
    for (int col = QRCode::SIZE - 1; col >= 0; col--) {
        row = fromBottom ? QRCode::SIZE - 1 : 0;
        while ((fromBottom && (row >= 0)) || (!fromBottom && row < qrCode.size())) {
            if (!reserved.at(row).at(col)) {
                // set the current qr code grid box to a random digit if we are done encoding every character in the message and stil have space
                if (letterIndex == text.size()) {
                    //generate random num btw 0 - 9 to fill the rest
                    qrCode.at(row).at(col) = rand() % 10;
                } else {  // set current box in the qr code grid to a digit from the 3 width ascii number representation of the current letter
                    qrCode.at(row).at(col) = digits.at(digitIndex);
                    digitIndex++;
                    // if the current character has been fully placed into the qr code grid, move on to the next character
                    if (digitIndex == 3) {
                        digitIndex = 0;
                        letterIndex++;
                        if (letterIndex != text.size()) {
                            digits = QRCode::letterToDigits(text.at(letterIndex));
                        }
                    }
                }
            }
            // move to next box (based on the direction of travel up or down the col)
            row = fromBottom ? row - 1 : row + 1;
        }
        // switch direction of travel for each row
        fromBottom = !fromBottom;
    }
}

string QRCode::getText() const {
    return text;
}

void QRCode::print(const ColorPalette& palette, const Color& c1, const Color& c2) const {

    // SOURCE: https://www.w3schools.com/cpp/cpp_exceptions.asp
    // DESCRIPTION: error handling in c++
    if (!QRCode::isValidPalette(palette) || c1 == c2) {
        throw invalid_argument("invalid color options");
    }

    Color color;
    for (int row = 0; row < QRCode::SIZE; row++) {
        for (int col = 0; col < QRCode::SIZE; col++) {
            int digit = qrCode.at(row).at(col);
            if (digit == 11) {          // first color of logo is encoded as 11
                color = c1;
            } else if (digit == 12) {   // second color of logo is encoded as 12
                color = c2;
            } else {
                color = palette.getColor(digit);
            }
            color.print();
        }
        cout << endl;
    }
}

void QRCode::download(const string& path, const ColorPalette& palette, const Color& c1, const Color& c2) const {

    if (!QRCode::isValidPalette(palette) || c1 == c2) {
        throw invalid_argument("invalid color options");
    }

    // create image for qr code
    // each element of the qr code will be expanded to a box of 10 x 10 pixels
    const int PIXELS = QRCode::SIZE * QRCode::SQUARE_SIZE;
    Image image(PIXELS, PIXELS);

    // create image from qr code data by expanding each qr code box into a larger box of pixels
    for (int row = 0; row < QRCode::SIZE; row++) {
        for (int col = 0; col < QRCode::SIZE; col++) {
            // determine what color for current box of the qr code
            Color color;
            // the logo area is a 7 x 7 box
            // set logo area qr code boxes to random colors to create a colorful background for the logo
            // the logo wil be written over this colorful background pixel by pixel for more detail
            if (QRCode::inLogoArea(row, col)) {
                color = palette.getColor(rand() % 10);
            } else { // encoding area
                color = palette.getColor(qrCode.at(row).at(col));
            }

            // expand each qrcode code box into a 7 x 7 grid of pixels
            QRCode::expandToPixels(image, row, col, color);
        }
    }

    // write logo to image using the specified colors
    QRCode::writeLogoToImage(image, c1, c2);
    // create a bitmap from the image which is used to write the pixels to a .bmp file
    Bitmap bitmap(image);
    // download bitmap
    bitmap.download(path); // return status of download
}

string QRCode::scan(const string& path) {

    // FIXME: Bitmap should throw error if the specified file is not a .bmp file
    Image image = Bitmap::load(path);

    // Four checks to determine if .bmp file contains a qr code generated from this class

    // Check 1: determine if dimensions indicate it is a valid qr code, ie: can it can be converted into a 21 x 21 data grid?
    if ((image.getWidth() / QRCode::SQUARE_SIZE)!= QRCode::SIZE
        ||(image.getHeight() / QRCode::SQUARE_SIZE) != QRCode::SIZE) {
         throw ios_base::failure("not a qr code: invalid size");
    }

    // assume image is a valid qr code, rotate image to proper orientation
    // image vertices are numbered 1, 2, 3, 4, clockwise starting from the upper left
    Color v1 = image.getPixel(0, 0);
    Color v2 = image.getPixel(0, image.getWidth() - 1);
    Color v3 = image.getPixel(image.getHeight() - 1, image.getWidth() - 1);
    Color v4 = image.getPixel(image.getHeight() - 1, 0);
    Image rotatedImage;

    if ((v1 == v2) && (v2 == v4) && (v4 != v3)) {
        // proper orientation already
        rotatedImage = image;
    } else if ((v1 == v2) && (v2 == v3) && (v3 != v4)) {
        // rotate counter-clockwise by 90deg
        rotatedImage = QRCode::rotateImage(image, 90);
    } else if ((v2 == v3) && (v3 == v4) && (v4 != v1)) {
        // rotate counter-clockwise by 180deg
        rotatedImage = QRCode::rotateImage(image, 180);
    } else if ((v1 == v3) && (v3 == v4) && (v4 != v2)) {
        // rotate counter-clockwise by 270deg
        rotatedImage = QRCode::rotateImage(image, 270);
    } else {
        throw ios_base::failure("not a qr code: three vertices do not have the same color");
    }

    // get color palette used for the qr code from the image data
    ColorPalette palette;
    for (int i = 0; i < 11; i++) {
        Color c = rotatedImage.getPixel((rotatedImage.getHeight() - 1) - (i * QRCode::SQUARE_SIZE), rotatedImage.getWidth() - 1);
        palette.addColor(c);
    }

    // Check 2: all colors should be unique
    if (!QRCode::isValidPalette(palette)) {
        throw ios_base::failure("not a qr code: invalid color palette");
    }

    // minimize the pixel data into a 21 x 21 data grid and map each color to an integer btw 0-11 based on the color palette
    vector<vector<int>> data = QRCode::minimizeToData(rotatedImage, palette);

    // Check 3: do orientation squares exist?
    if (!checkOrientationSquares(data)) {
        throw ios_base::failure("not a qr code: orientation squares do not exist");
    }

    // get message length
    vector<int> digits(3);
    for (int i = 0; i < 3; i++) {
        int lengthDigit = data.at(QRCode::SIZE - 12 - i).at(QRCode::SIZE - 1);
        digits.at(i) = lengthDigit;
    }
    int textLength = digits.at(0) + (digits.at(1) * 10) + (digits.at(2) * 100);

    // validate text length
    if (textLength == 0 || textLength > QRCode::MAX_LEN) {
        throw ios_base::failure("not a qr code: invalid text length");
    }

    // After these four checks, proceed with decoding assuming data represents a valid qr code.
    // If it is not a qr code, the "decoded text" will be meaningless. Otherwise, it will be valid text.

    // decode the message
    string decodedText = "";
    bool fromBottom = true;
    int digitIndex = 0;
    int row;
    // traverse qr code grid from the last column to the first column
    // walk up first column traversed and down second column traversed, keep switching direction of column traversal
    for (int col = QRCode::SIZE - 1; col >= 0 && decodedText.size() < textLength; col--) {
        row = fromBottom ? QRCode::SIZE - 1 : 0;
        while (((fromBottom && row >= 0) || (!fromBottom && row < QRCode::SIZE)) && decodedText.size() < textLength) {
            // read a digit from the data grid
            if (!reserved.at(row).at(col)) {
                // store digits until we've read three digits = a letter in the message
                digits.at(digitIndex) = data.at(row).at(col);
                digitIndex++;
                if (digitIndex == 3) {
                    // map the 3 digits to a  letter and append it to the message
                    decodedText += QRCode::digitsToLetter(digits);
                    digitIndex = 0;
                }
            }
            row = fromBottom ? row - 1 : row + 1;
        }
        fromBottom = !fromBottom;
    }
    return decodedText;
}

// =============================================================================================== //
// ==================================== STATIC HELPER METHODS ==================================== //
// =============================================================================================== //

// ========================================= ENCODING ============================================ //
char QRCode::digitsToLetter(const vector<int>& digits) {
    int value = digits.at(0) + (digits.at(1) * 10) + (digits.at(2) * 100);
    return static_cast<char>(value);
}

bool QRCode::inLogoArea(int rowIndex, int colIndex) {
    return (
        (rowIndex >= QRCode::LOGO_START_INDEX && rowIndex <=QRCode::LOGO_END_INDEX) &&
        (colIndex >= QRCode::LOGO_START_INDEX && colIndex <= QRCode::LOGO_END_INDEX)
    );
}

void QRCode::expandToPixels(Image& image, int row, int col, const Color& color) {
    for (int y = 0; y < QRCode::SQUARE_SIZE; y++) {
        for (int x = 0; x < QRCode::SQUARE_SIZE; x++) {
            int yPixelIndex = row * QRCode::SQUARE_SIZE + y;
            int xPixelIndex = col * QRCode::SQUARE_SIZE + x;
            image.setPixel(yPixelIndex, xPixelIndex, color);
        }
    }
}

void QRCode::writeLogoToImage(Image& image, const Color& c1, const Color& c2) {
    // pixel the logo region begins at in the image
    int logoRegionStart = QRCode::LOGO_START_INDEX * QRCode::SQUARE_SIZE;
    int logoSize = (QRCode::LOGO_END_INDEX - QRCode::LOGO_START_INDEX + 1) * QRCode::SQUARE_SIZE;
    int logoRegionEnd = logoRegionStart + logoSize;
    // write logo pixels
    for (int i = logoRegionStart; i < logoRegionEnd; i++) {
        for (int j = logoRegionStart; j < logoRegionEnd; j++) {
            int logoElement = QRCode::logoTemplate.at(i - logoRegionStart).at(j - logoRegionStart);
            Color c;
            if (logoElement == 1) {             // 1 is used as a placeholder for the first cat's main color
                image.setPixel(i, j, c1);
            } else if (logoElement == 0) {      // 0 is used as a placeholder for the second cat's main color
                image.setPixel(i, j, c2);
            }
        }
    }
}

// ========================================= DECODING ============================================ //
Image QRCode::rotateImage(const Image& image, int degrees) {

    Image rotatedImage(image.getWidth(), image.getHeight());

    switch (degrees) {
        case 90:
            // rotate counter-clockwise by 90deg
            // every row becomes a column on the left side
            for (int row = 0; row < image.getHeight(); row++) {
                for (int col = 0; col < image.getWidth(); col++) {
                    Color c = image.getPixel(row, col);
                    rotatedImage.setPixel(image.getHeight() - 1 - col, row, c);
                }
            }
            break;
        case 180:
            // rotate counter-clockwise by 180deg
            // every row becomes a bottom row with the direction reversed
            for (int row = 0; row < image.getHeight(); row++) {
                for (int col = 0; col < image.getWidth(); col++) {
                    Color c = image.getPixel(row, col);
                    rotatedImage.setPixel(image.getHeight() - 1 - row, image.getWidth() - 1 - col, c);
                }
            }
            break;
        case 270:
            // rotate counter-clockwise by 270deg
            // every row becomes a col on the right side
            for (int row = 0; row < image.getHeight(); row++) {
                for (int col = 0; col < image.getWidth(); col++) {
                    Color c = image.getPixel(row, col);
                    rotatedImage.setPixel(col, image.getWidth() - 1 - row, c);
                }
            }
            break;
        default:
            rotatedImage = image;
    }

    return rotatedImage;
}

vector<vector<int> > QRCode::minimizeToData(const Image& image, const ColorPalette& palette) {
    // create vector to store the qrcode data in
    vector<vector<int> > qrCode;
    qrCode.resize(QRCode::SIZE);
    for (int i = 0; i < QRCode::SIZE; i++) {
        qrCode.at(i).resize(QRCode::SIZE);
    }

    for (int i = 0; i < qrCode.size(); i++) {
        for (int j = 0; j < qrCode.size(); j++) {
            if (QRCode::inLogoArea(i, j))  {
                // ignore the logo area, set the logo boxes to 0
                qrCode.at(i).at(j) = 0;
            } else {    // set the qr code data boxes to the proper number value
                int y = QRCode::SQUARE_SIZE * i;
                int x = QRCode::SQUARE_SIZE * j;

                Color c = image.getPixel(y, x);
                qrCode.at(i).at(j) = decodeColor(palette, c);
            }
        }
    }
    return qrCode;
}

bool QRCode::checkOrientationSquares(const vector<vector<int>>& qrCode) {
    bool isValid = true;

    // middle dots of the orienation squares
    if (qrCode.at(2).at(2) != 10 ||
        qrCode.at(2).at(18) != 10 ||
        qrCode.at(18).at(2) != 10) {
            isValid = false;
    }

    for (int i = 0; i < 5 && isValid; i++) {
        // row at index 0
        if (qrCode.at(0).at(i) != 10 ||
            qrCode.at(0).at(qrCode.size() - 1 - i) != 10 ||
            qrCode.at(4).at(i) != 10 ||
            qrCode.at(4).at(qrCode.size() - 1 - i) != 10 ||
            qrCode.at(16).at(i) != 10 ||
            qrCode.at(20).at(i) != 10) {
            isValid = false;
        }
    }

    //set vertical parts to color 10 of the orientation squares
    for (int i = 1; i < 4 && isValid; i++) {
        if (qrCode.at(i).at(0) != 10 ||
            qrCode.at(qrCode.size() - 1 - i).at(0) != 10 ||
            qrCode.at(i).at(4) != 10 ||
            qrCode.at(qrCode.size() - 1 - i).at(4) != 10 ||
            qrCode.at(i).at(16) != 10 ||
            qrCode.at(i).at(20) != 10) {
                isValid = false;
            }
    }

    return isValid;
}

vector<int> QRCode::letterToDigits(char letter) {
    int digits = letter;
    vector<int> digitVector(3);
    for (int i = 0; i < 3; i++) {
        int digit = digits % 10;
        digits /= 10;
        digitVector.at(i) = digit;
    }
    return digitVector;
}

int QRCode::decodeColor(const ColorPalette& palette, const Color& c) {
    for (int i = 0; i < palette.size(); i++) {
        Color color = palette.getColor(i);
        if (color == c) {
            return i;
        }
    }
    return -1;
}

bool QRCode::contains(const vector<Color>& colors, const Color& color) {
    for (int i = 0; i < colors.size(); i++) {
        if (colors.at(i) == color) {
            return true;
        }
    }
    return false;
}

// =========================================== BOTH ==========================-==================== //
bool QRCode::isValidPalette(const ColorPalette& palette) {
    // check if there are exactly 11 colors
    if (palette.size() != 11) return false;

    // check if all colors are unique
    vector<Color> uniqueColors;
    for (int i = 0; i < palette.size(); i++) {
        Color c = palette.getColor(i);
        // duplicate found
        if (contains(uniqueColors, c)) {
            return false;
        }
        uniqueColors.push_back(c);
    }
    return true;
}
