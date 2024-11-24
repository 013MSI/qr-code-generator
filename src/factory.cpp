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
    names.push_back("sunset");
    names.push_back("rainbow");
    names.push_back("sky");

    return names;
}

vector<ColorPalette> makePalettes() {
    vector<ColorPalette> palettes;

    // create first palette
    ColorPalette p = ColorPalette();
    p.addColor(Color(0, 0, 0));
    p.addColor(Color(1, 2, 3));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    palettes.push_back(p);

    // create second palette
    p = ColorPalette();
    p.addColor(Color(1, 1, 1));
    p.addColor(Color(1, 2, 3));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    palettes.push_back(p);

    // create third palette
    p = ColorPalette();
    p.addColor(Color(2, 2, 2));
    p.addColor(Color(1, 2, 3));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
    p.addColor(Color(255, 255, 255));
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
