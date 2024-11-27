#pragma once

#include "ColorPalette.h"

#include <vector>
#include <string>

using namespace std;

vector<vector<int> > makeLogoTemplate();
vector<string> makePaletteNames();
vector<ColorPalette> makePalettes();
vector<vector<bool> > makeReserved();
