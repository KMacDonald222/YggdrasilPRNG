// File:        YggdrasilPRNG.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include "YggdrasilPRNG.h"

// YggdrasilPRNG member functions

void YggdrasilPRNG::seed(const std::string& seed, unsigned int layerCount) {
    m_root.seed(seed, layerCount - 1);
}

uint8_t YggdrasilPRNG::generate() {
    return m_root.generate();
}

void YggdrasilPRNG::clear() {
    m_root.clear();
}