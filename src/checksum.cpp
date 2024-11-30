// checksum.cpp

#include <iostream>
#include <string>

using namespace std;

// ------------------ HOW IT WORKS ------------------
// 1. pad string if its length it not a multiple of 5
// 2. divide the string into substrings of length 5
// 3. calculate the sum of the characters in each substring
// 4. map each sum to a number from 33 - 127
// 5. concvert each number to a character with that ascii value
// 6. concatenate these ascii characters together to form the checksum
string checksum(string data) {
    const int SUBSTRING_LENGTH = 5;

    // pad
    int padding = (data.length() % SUBSTRING_LENGTH == 0) ? 0 : SUBSTRING_LENGTH - (data.length() % SUBSTRING_LENGTH);
    for (int i = 0; i < padding; i++) {
        data += '!';
    }

    // map each substring to a single character
    string checksum = "";
    for (int i = 0; i < data.length(); i+= SUBSTRING_LENGTH) {
        int sum = 0;
        for (int j = 0; j < SUBSTRING_LENGTH; j++) {
            sum += data.at(i+j);
        }
        checksum += (sum % 94) + 33; // characters from ! to ~ from ASCII table
    }

    return checksum;
}
