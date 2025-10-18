// File:        Utilities.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.16@15:12ADT

#include "Utilities.h"

#include <SHA/SHA512.h>

#include <cstdint>

// Utilities module functions

std::vector<bool> hashBinary(const std::string& input) {
    const std::string hashSymbols = "0123456789abcdef";
    // Get the hexadecimal hash from the SHA vendor library
    std::string hashHex = hashHexadecimal(input);
    std::vector<bool> hashBin(512);
    for (size_t i = 0; i < hashHex.length(); i++) {
        // Find the binary representation of the next 4-bit hex symbol
        uint8_t j = 0x00;
        for (; j < 0xff; j++) {
            if (hashHex[i] == hashSymbols[j]) {
                break;
            }
        }
        // Add the binary to the boolean representation
        for (size_t k = 0; k < 4; k++) {
            hashBin[(i * 4) + k] = (j >> (4 - k - 1)) & 0x01;
        }
    }
    return hashBin;
}

std::string hashHexadecimal(const std::string& input) {
    SHA512 sha512;
    return sha512.hash(input);
}

std::string permuteString(const std::string& input) {
    // Placeholder
    return input;
}