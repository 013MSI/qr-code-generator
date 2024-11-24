#pragma once

#include "Color.h"

#include <vector>

using namespace std;

class ColorPalette {
    public:
        void addColor(Color);
        Color get(int);
        int size();
        void print();
    private:
        vector<Color> colors;
};
