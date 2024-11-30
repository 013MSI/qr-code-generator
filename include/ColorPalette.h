#pragma once

#include "Color.h"
#include <vector>

using namespace std;

class ColorPalette {
    public:
        // instance methods
        void addColor(const Color& color);
        Color getColor(int index) const;
        int size() const;
        void print() const;
    private:
        // instance variable
        vector<Color> colors;
};
