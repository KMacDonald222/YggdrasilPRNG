// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/Utilities.h>

#include <iostream>

// YGen module functions

int main() {
    std::string input = "Hello World!";
    std::string permuted = permuteString(input);
    std::cout << "Permute(\"" << input << "\") = \"" << permuted << "\""
        << std::endl;
    return 0;
}