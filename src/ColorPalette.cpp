// ColorPalette.cpp

#include "ColorPalette.h"
#include "Color.h"

#include <iostream>

using namespace std;

void ColorPalette::addColor(const Color& color) {
    colors.push_back(color);
}

Color ColorPalette::getColor(int index) const {
    return colors.at(index);
}

int ColorPalette::size() const {
    return colors.size();
}

void ColorPalette::print() const {
    for (int i = 0; i < colors.size(); i++) {
        colors.at(i).print();
    }
}
