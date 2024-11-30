// factory.h

#pragma once

#include "ColorPalette.h"
#include <vector>

using namespace std;

/*
 * Creates three color palettes, each with a different theme.
 *
 * return A vector of ColorPalette objects
 */
vector<ColorPalette> makePalettes();
