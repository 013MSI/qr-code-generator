#include "Bitmap.h"
#include "ColorPalette.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// SOURCE: https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
// SOURCE DESCRIPTION: bitmap code adapted from Minhas Kamal's responce

// pass a reference to data to the code
// a copy of data argument is assigned to the data attribute of the object
Bitmap::Bitmap(vector<vector<int> > data, int squareSize, ColorPalette p) {
    this->data = data;
    this->squareSize = squareSize;
    this->palette = p;

    this->height = data.size() * squareSize;
    this->width = data.at(0).size() * squareSize;
}

void Bitmap::download(string file) {
    // each row in the data 2D vector from the bottom
    unsigned char bmp[height][width][BYTES_PER_PIXEL];
    for (int i = data.size() - 1; i >= 0; i--) {
        for (int r = 0; r < squareSize; r++) {
            for (int j = 0; j < data[0].size(); j++) {
                Color c = palette.get(data.at(i).at(j));
                for (int p = 0; p < squareSize; p++) {
                    int y = (data.size() - 1 - i) * squareSize + r;
                    int x = j * squareSize + p;
                    bmp[y][x][2] = (unsigned char) (c.r);  //red
                    bmp[y][x][1] = (unsigned char) (c.g);  //green
                    bmp[y][x][0] = (unsigned char) (c.b); //blue
                }
            }
        }
    }

    writeImage((unsigned char*) bmp, file);
}

void Bitmap::writeImage(unsigned char* image, string file) {
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE* imageFile = fopen(file.c_str(), "wb");

    unsigned char* fileHeader = createFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char* infoHeader = createInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < height; i++) {
        fwrite(image + (i*widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char* Bitmap::createFileHeader (int height, int stride) {
    int fileSize = Bitmap::FILE_HEADER_SIZE + Bitmap::INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
    };

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(Bitmap::FILE_HEADER_SIZE + Bitmap::INFO_HEADER_SIZE);

    return fileHeader;
}

unsigned char* Bitmap::createInfoHeader (int height, int width)
{
    static unsigned char infoHeader[] = {
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    infoHeader[ 0] = (unsigned char)(Bitmap::INFO_HEADER_SIZE);
    infoHeader[ 4] = (unsigned char)(width      );
    infoHeader[ 5] = (unsigned char)(width >>  8);
    infoHeader[ 6] = (unsigned char)(width >> 16);
    infoHeader[ 7] = (unsigned char)(width >> 24);
    infoHeader[ 8] = (unsigned char)(height      );
    infoHeader[ 9] = (unsigned char)(height >>  8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(Bitmap::BYTES_PER_PIXEL*8);

    return infoHeader;
}

vector<vector<int> > Bitmap::decode(string path) {
    vector<vector<int> > data;
    return data;
}
