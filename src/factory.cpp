#include "ColorPalette.h"
#include "Color.h"
#include <vector>

using namespace std;

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
    p.addColor(Color(218, 56, 50));  // fire_brick
    p.addColor(Color(239, 133, 50)); // Orange
    p.addColor(Color(246, 196, 69));  // Yellow
    p.addColor(Color(48, 54, 147)); // Dark Blue
    p.addColor(Color(82, 180, 234)); // Light Blue
    p.addColor(Color(181, 228, 77));  // Lime medium_sea_green
    p.addColor(Color(85, 174, 88)); // medium_sea_green
    p.addColor(Color(140, 26, 50));    // Burgandy
    p.addColor(Color(241, 166, 177));   // Pink
    p.addColor(Color(218, 248, 193));  // Light medium_sea_green
    p.addColor(Color(89, 108, 139));  // Slate BLue
    palettes.push_back(p);

    // Palette 3: "Ocean"
    p = ColorPalette();
    p.addColor(Color(70, 130, 180));  // Steel blue
    p.addColor(Color(100, 149, 237)); // Cornflower blue
    p.addColor(Color(65, 105, 225));  // Royal blue
    p.addColor(Color( 0, 105, 148));   // Deep sea blue
    p.addColor(Color(30, 144, 255));  // Dodger blue
    p.addColor(Color( 0, 191, 255));   // Deep sky blue
    p.addColor(Color(72, 209, 204));  // Medium turquoise
    p.addColor(Color(135, 206, 235)); // Sky blue
    p.addColor(Color( 0, 178, 238));   // Rich blue
    p.addColor(Color(175, 238, 238)); // Pale turquoise
    p.addColor(Color(85, 128, 176)); // Alice blue
    palettes.push_back(p);

    return palettes;
}
