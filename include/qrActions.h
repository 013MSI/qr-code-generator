// qrActions.h

#pragma once

#include "QRCode.h"
#include "ColorPalette.h"
#include <string>

using namespace std;

/*
 * Guides the user through the process of creating a QR code,
 * including getting a message, selecting a color palette, and downloading the QR code.
 */
void generate();

/*
 * Simulates the scanning of a QR code, reading a valid BMP file and decodign
 * it embedded data back into text.
 */
void scan();

// =============================================================================================== //
// ====================================== HELPER FUNCTIONS ======================================= //
// =============================================================================================== //
// Gets a message from the user for the QR code.
string getMessage();
// Gets a user selected color palette.
ColorPalette getPalette();
// Downloads the generated QR code with the selected color palette to a file.
void downloadQRCode(QRCode& qrCode, ColorPalette& palette);
