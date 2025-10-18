// File:        YggdrasilPRNG.h
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#ifndef YGGDRASILPRNG_YGGDRASILPRNG_H
#define YGGDRASILPRNG_YGGDRASILPRNG_H

#include <string>
#include <cstdint>

// Main wrapper class of the Yggdrasil PRNG library
class YggdrasilPRNG {
public:
    /*
    Initialize the PRNG tree's memory
    Parameter: const std::string& seed - Seed data to defined the structure and
    initial state of the tree
    Parameter: unsigned int layerCount - The number of layers of the tree to
    generate
    */
    void seed(const std::string&, unsigned int);
    /*
    Get a pseudo-random byte from the PRNG tree
    Returns: uint8_t - A pseudo-random byte
    */
    uint8_t generate();
    /*
    Free the PRNG tree's memory
    */
    void clear();
};

#endif