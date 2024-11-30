#pragma once

class Color {
    public:
        // constructors
        Color();
        Color(int r, int g, int b);

        // instance methods
        void print() const;
        // SOURCE: https://www.geeksforgeeks.org/how-to-overload-operator-in-cpp/#
        // SOURCE DESCRIPTION: overloading == operator
        bool operator==(const Color& other) const;
        bool operator!=(const Color& other) const;

        // instance variables
        int r;
        int g;
        int b;
};
