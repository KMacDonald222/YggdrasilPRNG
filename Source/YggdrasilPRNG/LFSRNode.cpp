// File:        LFSRNode.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.21@18:48ADT

#include "Nodes.h"
#include "Utilities.h"

// LFSRNode module variables

// Set of pre-defined LFSR width and tap configurations
std::vector<std::vector<size_t>> LFSR_CONFIGURATIONS = {
    { 4096, 4095, 4094, 4080, 4068, },
    { 2048, 2047, 2034, 2033, 2028, },
    { 1024, 1023, 1014, 1001, 1000, },
    { 777, 776, 775, 766, 760, },
    { 777, 776, 747, },
    { 666, 665, 663, 658, 655, },
    { 555, 554, 550, 545, 544, },
    { 444, 443, 434, 431, 430, },
    { 419, 418, 414, 413, 403, },
    { 404, 403, 399, 397, 396, },
    { 404, 403, 214, },
    { 333, 332, 330, 328, 324, },
    { 333, 332, 330, },
    { 303, 302, 296, 290, 289, },
    { 256, 255, 253, 250, 245, },
    { 222, 221, 219, 216, 213, },
};

// LFSRNode member functions

void LFSRNode::seed(const std::string& seed, unsigned int) {
    std::vector<bool> binHash = hashBinary(seed);
    // Find the permutation index from the last four bits of the seed hash
    uint8_t configIndex = 0x00;
    for (size_t i = 0; i < 4; i++) {
        configIndex = (configIndex << 1)
            | (uint8_t)(binHash[(binHash.size() - 4) + i]);
    }
    // Get the LFSR width from the configuration
    size_t width = LFSR_CONFIGURATIONS[configIndex][0];
    // Populate the state buffer
    m_state.resize(width);
    for (size_t i = 0; i < width; i++) {
        m_state[i] = binHash[i % binHash.size()];
    }
    // Populate the taps buffer
    m_taps.resize(width);
    for (size_t i = 0; i < width; i++) {
        m_taps[i] = false;
    }
    for (size_t i = 1; i < LFSR_CONFIGURATIONS[configIndex].size(); i++) {
        m_taps[width - LFSR_CONFIGURATIONS[configIndex][i] - 1] = true;
    }
}

uint8_t LFSRNode::generate() {
    uint8_t output = 0x00;
    for (size_t i = 0; i < 8; i++) {
        // Get output bit and shift state buffer
        bool bit = m_state[m_state.size() - 1];
        output = (output << 1) | (uint8_t)bit;
        for (size_t j = m_state.size() - 1; j > 0; j--) {
            m_state[j] = m_state[j - 1];
        }
        m_state[0] = false;
        // Apply the XOR tap mask
        if (bit) {
            for (size_t j = 0; j < m_taps.size(); j++) {
                m_state[j] = m_state[j] ^ m_taps[j];
            }
        }
    }
    return output;
}

void LFSRNode::clear() {
    // Overwrite and free state and taps buffers
    for (size_t i = 0; i < m_state.size(); i++) {
        m_state[i] = false;
    }
    m_state.clear();
    for (size_t i = 0; i < m_taps.size(); i++) {
        m_taps[i] = false;
    }
    m_taps.clear();
}