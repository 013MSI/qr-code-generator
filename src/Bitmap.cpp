#include "Bitmap.h"
#include "Image.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

using namespace std;

Bitmap::Bitmap(Image image) {
    this->image = image;

    // calculate padding
    padding = Bitmap::calculatePadding(image.getRowLength());
    int paddedRowLength = image.getRowLength() + padding;

    // set bitmap information header
    bmih.width = image.getWidth();
    bmih.height = image.getHeight();
    bmih.imageSize = paddedRowLength * image.getHeight();
    // set file information header
    bmfh.offSet = sizeof(bmfh) + sizeof(bmih);
    bmfh.size = bmfh.offSet + bmih.imageSize;
}

bool Bitmap::download(string fileName) {
    // open / create file to write binary data into
    ofstream output(fileName.c_str(), ios::binary);

    // error opening / creating file
    if (!output) {
        cout << "Could not open file" << endl;
        return false;
    }

    cout << "BitmapFileHeader:" << endl;
    cout << "  fileType: " << hex << bmfh.fileType << endl;
    cout << "  size: " << dec << bmfh.size << endl;
    cout << "  reserved1: " << bmfh.reserved1 << endl;
    cout << "  reserved2: " << bmfh.reserved2 << endl;
    cout << "  offSet: " << bmfh.offSet << endl;

    // Print all fields of BitmapInfoHeader
    cout << "BitmapInfoHeader:" << endl;
    cout << "  size: " << bmih.size << endl;
    cout << "  width: " << bmih.width << endl;
    cout << "  height: " << bmih.height << endl;
    cout << "  planes: " << bmih.planes << endl;
    cout << "  bitsPerPixel: " << bmih.bitsPerPixel << endl;
    cout << "  compression: " << bmih.compression << endl;
    cout << "  imageSize: " << bmih.imageSize << endl;
    cout << "  xPixelsPerMeter: " << bmih.xPixelsPerMeter << endl;
    cout << "  yPixelsPerMeter: " << bmih.yPixelsPerMeter << endl;
    cout << "  numColors: " << bmih.numColors << endl;
    cout << "  numImportantColors: " << bmih.numImportantColors << endl;
    cout << "  padding: " << padding << endl;

    // write headers
    // & - the address-of operator
    // reinterpret_cast<unsigned char*>(&structInstance) - converts the pointer to a structure to a pointer of characters
    // ie, it causes the compiler the treat the underlying bits of the structure as if they were characters (1 byte chunks of data)
    // allowing it to be written byte by byte into a file
    output.write(reinterpret_cast<const char*>(&bmfh), sizeof(bmfh));
    output.write(reinterpret_cast<const char*>(&bmih), sizeof(bmih));

    // write pixel data with padding (bottom-to-top order)
    vector<uint8_t> paddingBytes(padding, 0);
    for (int rowIndex = image.getHeight() - 1; rowIndex >= 0; rowIndex--) {
        output.write(reinterpret_cast<const char*>(image.getRowAddress(rowIndex)), image.getRowLength());
        output.write(reinterpret_cast<const char*>(paddingBytes.data()), padding);
    }

    output.close();
    return true;
}

Image Bitmap::load(string fileName) {
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    ifstream input(fileName.c_str(), ios::binary);

    if (!input) {
        return Image(); // return empty Image
    }

    // read file information header
    // treat header struct as array of characters and read the appropriate number of bytes
    // (in this case 14) into the structure
    input.read(reinterpret_cast<char*>(&bmfh), sizeof(bmfh));

    // determine if the specified file is a bmp file
    if(bmfh.fileType != 0x4D42) {
        return Image(); // return empty Image
    }

    // read bitmap information header
    input.read(reinterpret_cast<char*>(&bmih), sizeof(bmih));

    cout << "BitmapFileHeader:" << endl;
    cout << "  fileType: " << hex << bmfh.fileType << endl;
    cout << "  size: " << dec << bmfh.size << endl;
    cout << "  reserved1: " << bmfh.reserved1 << endl;
    cout << "  reserved2: " << bmfh.reserved2 << endl;
    cout << "  offSet: " << bmfh.offSet << endl;

    // Print all fields of BitmapInfoHeader
    cout << "BitmapInfoHeader:" << endl;
    cout << "  size: " << bmih.size << endl;
    cout << "  width: " << bmih.width << endl;
    cout << "  height: " << bmih.height << endl;
    cout << "  planes: " << bmih.planes << endl;
    cout << "  bitsPerPixel: " << bmih.bitsPerPixel << endl;
    cout << "  compression: " << bmih.compression << endl;
    cout << "  imageSize: " << bmih.imageSize << endl;
    cout << "  xPixelsPerMeter: " << bmih.xPixelsPerMeter << endl;
    cout << "  yPixelsPerMeter: " << bmih.yPixelsPerMeter << endl;
    cout << "  numColors: " << bmih.numColors << endl;
    cout << "  numImportantColors: " << bmih.numImportantColors << endl;

    // calculate padding
    // FIXME : dont hardcode 3
    int padding = Bitmap::calculatePadding(bmih.width * 3);

    cout << "  padding: " << padding << endl;


    // jump to pixel data
    input.seekg(bmfh.offSet, input.beg);

    // create image of correct size
    Image image(bmih.width, bmih.height);

    // read each row of pixel data from the bitmap
    // the first row of the bitmap pixel data corresponds to the last row of the image pixel data
    // discard padding on each row
    for (int row = 1; row <= bmih.height; row++) {
        input.read(reinterpret_cast<char*>(image.getRowAddress(bmih.height - row)), image.getRowLength());
        input.ignore(padding);
    }

    input.close();
    return image;
}

int Bitmap::calculatePadding(int rowLength) {
    int paddedRowLength = rowLength;
    while (paddedRowLength % 4 != 0) {
        paddedRowLength++;
    }
    return paddedRowLength - rowLength;
}
