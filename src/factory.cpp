#include "QRCode.h"
#include "factory.h"
#include "ColorPalette.h"
#include "Color.h"

#include <vector>
#include <string>

using namespace std;

// SOURCE: https://stackoverflow.com/questions/3701903/initialisation-of-static-vector
// SOURCE DESCRIPTION: How to initialize a static vector attribute
vector<string> makePaletteNames() {
    vector<string> names;
    names.push_back("grayscale");
    names.push_back("autumn");
    names.push_back("ocean");

    return names;
}

vector<ColorPalette> makePalettes() {
    vector<ColorPalette> palettes;

    // Palette 1: "Grayscale"
    ColorPalette p = ColorPalette();
    p.addColor(Color(0, 0, 0));       // Black
    p.addColor(Color(28, 28, 28));   // Very dark gray
    p.addColor(Color(56, 56, 56));   // Dark gray
    p.addColor(Color(85, 85, 85));   // Medium dark gray
    p.addColor(Color(113, 113, 113));// Medium gray
    p.addColor(Color(141, 141, 141));// Medium light gray
    p.addColor(Color(170, 170, 170));// Light gray
    p.addColor(Color(198, 198, 198));// Lighter gray
    p.addColor(Color(216, 216, 216));// Very light gray
    p.addColor(Color(225, 225, 225));// Near white
    p.addColor(Color(255, 255, 255));// White
    palettes.push_back(p);

    // Palette 2: "Autumn"
    p = ColorPalette();
    p.addColor(Color(218, 56, 50));  // Red
    p.addColor(Color(239, 133, 50)); // Orange
    p.addColor(Color(246, 196, 69));  // Yellow
    p.addColor(Color(48, 54, 147)); // Dark Blue
    p.addColor(Color(82, 180, 234)); // Light Blue
    p.addColor(Color(181, 228, 77));  // Lime Green
    p.addColor(Color(85, 174, 88)); // Green
    p.addColor(Color(140, 26, 50));    // Burgandy
    //p.addColor(Color(103, 53, 147));   // Purple
    p.addColor(Color(241, 166, 177));   // Pink
    p.addColor(Color(218, 248, 193));  // Light Green
    p.addColor(Color(89, 108, 139));  // Slate BLue
    palettes.push_back(p);

    // Palette 3: "Ocean"
    p = ColorPalette();
    p.addColor(Color(70, 130, 180));  // Steel blue
    p.addColor(Color(100, 149, 237)); // Cornflower blue
    p.addColor(Color(65, 105, 225));  // Royal blue
    p.addColor(Color(0, 105, 148));   // Deep sea blue
    p.addColor(Color(30, 144, 255));  // Dodger blue
    p.addColor(Color(0, 191, 255));   // Deep sky blue
    p.addColor(Color(72, 209, 204));  // Medium turquoise
    p.addColor(Color(135, 206, 235)); // Sky blue
    p.addColor(Color(0, 178, 238));   // Rich blue
    p.addColor(Color(175, 238, 238)); // Pale turquoise
    p.addColor(Color(85, 128, 176)); // Alice blue
    palettes.push_back(p);


    return palettes;
}

vector<vector<bool> > makeReserved() {
    vector<vector<bool> > reserved;
    reserved.resize(QRCode::size);
    for (int i = 0; i < reserved.size(); i++) {
        reserved.at(i).resize(QRCode::size);
    }
    //reserve horizontal parts of the orientation squares
    for (int i = 0; i < 5; i++) {
        // row at index 0
        reserved.at(0).at(i) = true;
        reserved.at(0).at(reserved.size() - 1 - i) = true;
        // row at index 4
        reserved.at(4).at(i) = true;
        reserved.at(4).at(reserved.size() - 1 - i) = true;
        // row at index 16
        reserved.at(16).at(i) = true;
        // row at index 20
        reserved.at(20).at(i) = true;
    }

    //reserve vertical parts the orientation squares
    for (int i = 1; i < 4; i++) {
        // column at index 0 top and bottom squares
        reserved.at(i).at(0) = true;
        reserved.at(reserved.size() - 1 - i).at(0) = true;
        // column at index 4 top and bottom squares
        reserved.at(i).at(4) = true;
        reserved.at(reserved.size() - 1 - i).at(4) = true;
        // column at index 16 - third square
        reserved.at(i).at(16) = true;
        // column at index 20 - third square
        reserved.at(i).at(20) = true;
    }

    // reserve middle dots of the orienation squares
    reserved.at(2).at(2) = true;
    reserved.at(2).at(18) = true;
    reserved.at(18).at(2) = true;

    // reserve color boxes
    for (int i = 0; i <= 10; i++) {
        reserved.at(reserved.size() - 1 - i).at(reserved.size() - 1) = true;
    }

    // reserve length boxes
    for (int i = 0; i < 3; i++) {
        reserved.at(reserved.size() - 12 - i).at(reserved.size() - 1) = true;
    }

    return reserved;
}
