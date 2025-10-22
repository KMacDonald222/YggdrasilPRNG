// File:        MatrixNode.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.22@10:34ADT

#include "Nodes.h"
#include "Utilities.h"

// MatrixNode member functions

void MatrixNode::seed(const std::string& seed, unsigned int layerCount) {
    // Generate this node's children
    std::vector<bool> seedHash = hashBinary(seed);
    if (layerCount > 1) {
        // Generate 1-4 XOR node children
        uint8_t XORCount = 0x00;
        for (size_t i = 0; i < 2; i++) {
            XORCount = (XORCount << 1) | (uint8_t)(seedHash[507 + i]);
        }
        XORCount += 1;
        for (size_t i = 0; i < XORCount; i++) {
            // Placeholder
        }
        XORCount = 0x00;
        // Generate 0-1 AND node children
        uint8_t ANDCount = (uint8_t)seedHash[509];
        for (size_t i = 0; i < ANDCount; i++) {
            // Placeholder
        }
        ANDCount = 0x00;
        // Generate 0-1 OR node children
        uint8_t ORCount = (uint8_t)seedHash[510];
        for (size_t i = 0; i < ORCount; i++) {
            // Placeholder
        }
        ORCount = 0x00;
        // Generate 1-2 matrix node children
        uint8_t matrixCount = (uint8_t)seedHash[511] + 1;
        for (size_t i = 0; i < matrixCount; i++) {
            m_children.push_back(new MatrixNode);
        }
        matrixCount = 0x00;
    } else {
        // Generate 5-8 LFSR node children
        uint8_t LFSRCount = 0x00;
        for (size_t i = 0; i < 2; i++) {
            LFSRCount = (LFSRCount << 1) | (uint8_t)(seedHash[510 + i]);
        }
        LFSRCount += 5;
        for (size_t i = 0; i < LFSRCount; i++) {
            m_children.push_back(new LFSRNode);
        }
        LFSRCount = 0x00;
    }
    // Seed this node's children
    Node::seed(seed, layerCount);
    // Populate the transformation matrix
    m_matrix.resize(8);
    for (size_t r = 0; r < m_matrix.size(); r++) {
        m_matrix[r].resize(8);
        for (size_t c = 0; c < m_matrix[r].size(); c++) {
            m_matrix[r][c] = 0;
        }
    }
    for (size_t i = 0; i < 8; i++) {
        shiftMatrix();
    }
}

uint8_t MatrixNode::generate() {
    // Shift matrix and get byte to transform
    shiftMatrix();
    uint8_t byte = m_children[m_populatingChild]->generate();
    std::vector<int> bits(8);
    for (size_t i = 0; i < 8; i++) {
        bits[i] = ((bool)((byte >> (8 - i - 1)) & 0x01)) ? 1 : 0;
    }
    byte = 0x00;
    // Transform the byte by multiplication with the matrix
    std::vector<int> product(8);
    for (size_t r = 0; r < m_matrix.size(); r++) {
        product[r] = 0;
        for (size_t c = 0; c < m_matrix[r].size(); c++) {
            product[r] += (m_matrix[r][c] * bits[c]);
        }
    }
    // Modify output byte by the product
    std::vector<int> output(8);
    for (size_t i = 0; i < 8; i++) {
        output[i] = bits[i];
        if (product[i] > 2) {
            output[i] = 1;
        } else if (product[i] < -2) {
            output[i] = 0;
        }
    }
    // Clear initial bits and product bits from memory
    for (size_t i = 0; i < bits.size(); i++) {
        bits[i] = 0;
    }
    bits.clear();
    for (size_t i = 0; i < product.size(); i++) {
        product[i] = 0;
    }
    product.clear();
    // Reconstitute the transformed bits back into output
    uint8_t outByte = 0x00;
    for (size_t i = 0; i < 8; i++) {
        outByte = (outByte << 1) | ((uint8_t)output[i]);
    }
    // Clear output bits from memory
    for (size_t i = 0; i < output.size(); i++) {
        output[i] = 0;
    }
    output.clear();
    return outByte;
}

void MatrixNode::clear() {
    // Clear the transformation matrix from memory
    for (size_t r = 0; r < m_matrix.size(); r++) {
        for (size_t c = 0; c < m_matrix[r].size(); c++) {
            m_matrix[r][c] = 0;
        }
        m_matrix[r].clear();
    }
    m_matrix.clear();
    m_populatingChild = 0;
    // Clear this node's children
    Node::clear();
}

void MatrixNode::shiftMatrix() {
    // Determine the next matrix populating child node
    uint8_t popDet = m_children[m_populatingChild]->generate();
    m_populatingChild = (size_t)popDet % m_children.size();
    popDet = 0x00;
    // Shift matrix columns right
    for (size_t r = 0; r < m_matrix.size(); r++) {
        for (size_t c = m_matrix[r].size() - 1; c > 0; c--) {
            m_matrix[r][c] = m_matrix[r][c - 1];
        }
    }
    // Populate the leftmost column
    uint8_t colByte = m_children[m_populatingChild]->generate();
    for (size_t r = 0; r < m_matrix.size(); r++) {
        m_matrix[r][0] = ((bool)((colByte >> (m_matrix.size() - r - 1)) & 0x01))
            ? 1 : -1;
    }
    colByte = 0x00;
}