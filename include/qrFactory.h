// qrFactory.cpp

#pragma once

#include <vector>

using namespace std;

/*
 * Creates a logo template for the QR code.
 *
 * return A 2D vector of integers representing the logo template.
 */
vector<vector<int> > makeLogoTemplate();

/*
 * Creates a reserved area map for a QR code.
 *
 * The reserved map indicates which regions of the QR code grid are reserved for metadata elements,
 * such as orientation squares, size data, etc.
 *
 * return A 2D vector of boolean values where `true` indicates a reserved area.
 */
vector<vector<bool> > makeReserved();

/*
 * Creates an empty QR code grid.
 *
 * The grid is initialized with default values and represents the structure of a QR code
 * before encoding any data.
 *
 * return A 2D vector of integers representing an empty QR code.
 */
vector<vector<int> > makeEmptyQrCode();
