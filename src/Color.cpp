#include "Color.h"

#include <fmt/color.h>

#include <iostream>

using namespace std;

Color::Color() {
    r = g = b = 0;
}

Color::Color(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::print() {
    string square = fmt::format(bg(fmt::rgb(r, g, b)), "   ");
    fmt::print("{}", square);
}
