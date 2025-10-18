// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/Utilities.h>

#include <iostream>

// YGen module functions

int main() {
    std::string input = "Hello World!";
    std::string hexHash = hashHexadecimal(input);
    std::vector<bool> binHash = hashBinary(input);
    std::cout << "SHA-512(\"" << input << "\") = " << hexHash << std::endl;
    for (size_t i = 0; i < binHash.size(); i++) {
        std::cout << (int)binHash[i];
    }
    std::cout << std::endl;
    return 0;
}