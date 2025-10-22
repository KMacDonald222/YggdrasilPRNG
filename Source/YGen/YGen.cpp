// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/Nodes.h>

#include <iostream>
#include <bitset>

// YGen module functions

int main() {
    LFSRNode lfsr;
    lfsr.seed("Hello World!", 0);
    for (size_t i = 0; i < 64; i++) {
        std::cout << std::bitset<8>(lfsr.generate());
        std::cout.flush();
    }
    std::cout << std::endl;
    lfsr.clear();
    return 0;
}