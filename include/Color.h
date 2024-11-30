#pragma once

class Color {
    public:
        Color();
        Color(int r, int g, int b);
        int r;
        int g;
        int b;
        void print() const;
        // SOURCE: https://www.geeksforgeeks.org/how-to-overload-operator-in-cpp/#
        // SOURCE DESCRIPTION: overloading == operator
        bool operator==(const Color&) const;
        bool operator!=(const Color&) const;
};
