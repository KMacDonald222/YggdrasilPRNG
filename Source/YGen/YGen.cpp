// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/YggdrasilPRNG.h>

#include <iostream>
#include <bitset>

// YGen module functions

int main() {
    YggdrasilPRNG yprng;
    std::cout << "Seeding Yggdrasil PRNG with \"Hello World!\"" << std::endl;
    yprng.seed("Hello World!", 5);
    std::cout << "Generating 512B:" << std::endl;
    for (size_t i = 0; i < 512; i++) {
        std::cout << std::bitset<8>(yprng.generate());
        std::cout.flush();
    }
    std::cout << std::endl << "Clearing memory" << std::endl;
    yprng.clear();
    return 0;
}