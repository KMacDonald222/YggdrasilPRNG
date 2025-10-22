// File:        ORNode.cpp
// Author:      Keegan MacDonald
// Created:     2025.10.22@13:57ADT

#include "Nodes.h"
#include "Utilities.h"

// ORNode member functions

void ORNode::seed(const std::string& seed, unsigned int layerCount) {
    // Generate this node's children
    std::vector<bool> seedHash = hashBinary(seed);
    if (layerCount > 1) {
        // Generate 1-2 XOR node children
        uint8_t XORCount = (uint8_t)seedHash[509] + 1;
        for (size_t i = 0; i < XORCount; i++) {
            m_children.push_back(new XORNode);
        }
        XORCount = 0x00;
        // Generate 0-1 AND node children
        uint8_t ANDCount = (uint8_t)seedHash[510];
        for (size_t i = 0; i < ANDCount; i++) {
            m_children.push_back(new ANDNode);
        }
        ANDCount = 0x00;
        // Generate 1-2 matrix node children
        uint8_t matrixCount = (uint8_t)seedHash[511] + 1;
        for (size_t i = 0; i < matrixCount; i++) {
            m_children.push_back(new MatrixNode);
        }
        matrixCount = 0x00;
    } else {
        // Generate 2-5 LFSR node children
        uint8_t LFSRCount = 0x00;
        for (size_t i = 0; i < 2; i++) {
            LFSRCount = (LFSRCount << 1) | (uint8_t)(seedHash[510 + i]);
        }
        LFSRCount += 2;
        for (size_t i = 0; i < LFSRCount; i++) {
            m_children.push_back(new LFSRNode);
        }
        LFSRCount = 0x00;
    }
    // Seed this node's children
    Node::seed(seed, layerCount);
}

uint8_t ORNode::generate() {
    // Ensure that there are children to sample from
    if (m_children.empty()) {
        return 0x00;
    }
    // Compute the OR combination of the outputs of all children
    uint8_t byte = m_children[0]->generate();
    for (size_t i = 1; i < m_children.size(); i++) {
        byte |= m_children[i]->generate();
    }
    return byte;
}