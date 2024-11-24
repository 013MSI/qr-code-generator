#include "ColorPalette.h"
#include "Color.h"

#include <iostream>

using namespace std;

void ColorPalette::addColor(Color color) {
    colors.push_back(color);
}

Color ColorPalette::get(int index) {
    return colors.at(index);
}

int ColorPalette::size() {
    return colors.size();
}

void ColorPalette::print() {
    for (int i = 0; i < colors.size(); i++) {
        colors.at(i).print();
    }
}
