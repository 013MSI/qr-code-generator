#pragma once

#include "QRCode.h"
#include "ColorPalette.h"
#include <string>

using namespace std;

void generate();
void scan();

// generate helpers
string getMessage();
ColorPalette getPalette();
void downloadQRCode(QRCode& qrCode, ColorPalette& palette);
