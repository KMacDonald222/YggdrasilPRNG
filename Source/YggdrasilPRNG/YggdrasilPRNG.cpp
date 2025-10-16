// File:        YggdrasilPRNG.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15

#include "YggdrasilPRNG.h"

#include <SHA/SHA512.h>

#include <iostream>

void YggdrasilPRNG::test(const std::string& input) {
    SHA512 sha;
    std::cout << "SHA512(\"" << input << "\") = " << sha.hash(input)
        << std::endl;
}