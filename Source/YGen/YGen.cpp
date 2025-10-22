// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/Nodes.h>

#include <iostream>
#include <bitset>

// YGen module functions

int main() {
    MatrixNode matrix;
    matrix.seed("Hello World!", 1);
    for (size_t i = 0; i < 3; i++) {
        std::cout << "Output byte " << i << ": "
            << std::bitset<8>(matrix.generate()) << std::endl;
    }
    matrix.clear();
    return 0;
}