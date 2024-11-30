// Color.h

#pragma once

/*
 * Represents a RGB (red, green, blue) color.
 *
 * Allows for the creation, manipulation, and comparison of colors.
 * NOTE: Internally, it stores colors in BGR (blue, green, red) order, as required by the BMP file format.
 * This class is designed to be used in conjunction with the Bitmap class.
 */
class Color {
    public:
        /*
        * Creates a color initialized to black, ie. rgb(0, 0, 0).
        */
        Color();

        /*
        * Creates a color with the specified RGB values.
        *
        * params:
        *   r - The red component (0-255).
        *   g - The green component (0-255).
        *   b - The blue component (0-255).
        */
        Color(int r, int g, int b);

        /*
        * Prints a square of the color to the console.
        */
        void print() const;

        /*
        * Determines if two Color objects are equal.
        *
        * If the RGB components of both objects match, the Colors are considered equal.
        *
        * param:
        *   other - The Color object to compare with.
        * return true if the colors are equal, false if the colors are not equal.
        */
        // SOURCE: https://www.geeksforgeeks.org/how-to-overload-operator-in-cpp/#
        // DESCRIPTION: overloading == operator
        bool operator==(const Color& other) const;

        /*
        * Determines if two Color objects are not equal.
        *
        * Compares two Color objects for inequality by checking if their RGB components differ.
        *
        * param:
        *   other - The Color object to compare with.
        * return true if the colors are not equal, false if the colors are equal.
        */
        bool operator!=(const Color& other) const;

        // Public instance variables representing the RGB components of the color.
        int r;  // Red component (0-255).
        int g;  // Green component (0-255).
        int b;  // Blue component (0-255).
};
