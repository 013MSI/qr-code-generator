// checksum.h

#pragma once

#include <string>

using namespace std;

// SOURCE: https://www.geeksforgeeks.org/error-detection-code-checksum/?ref=oin_asr4
// DESCRIPTION: What are checksums and how do they work?

/*
 * Computes a checksum for the given text.
 *
 * The checksum function calculates a unique hash-like value for a given string, which can be used
 * to verify data integrity or ensure the uniqueness of the input.
 *
 * param:
 *   text - The input string to calcualte the checksum for.
 * return: A string representing the computed checksum.
 */
string checksum(string text);
