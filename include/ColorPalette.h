// ColorPalette.h

#pragma once

#include "Color.h"
#include <vector>

using namespace std;

/*
 * Manages a collection of Color objects.
 *
 * Provides functionality to add colors, retrieve colors by index,
 * get the number of colors in the palette, and print the palette to the console.
 */
class ColorPalette {
    public:
        /*
        * Adds a new color to the palette.
        *
        * param:
        *   color - The Color object add.
        */
        void addColor(const Color& color);

        /*
        * Retrieves the color at the specified index.
        *
        * Color are indexed using the order they are added.
        * The first Color that is added to the palette is at index 0.
        *
        *
        * param:
        *   index - The zero-based index of the color in the palette.
        * return The Color object at the specified index.
        */
        Color getColor(int index) const;

        /*
        * Gets the number of colors in the palette.
        *
        * return The size of the color palette as an integer.
        */
        int size() const;

        /*
        * Prints all the colors in the palette to the console.
        */
        void print() const;

    private:
        // Collection of colors managed by the palette.
        vector<Color> colors;
};
