// File:        Node.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.16@14:58ADT

#include "Nodes.h"
#include "Utilities.h"

// Node member functions

void Node::seed(const std::string& seed, unsigned int layerCount) {
    // Initialize permuted seed value
    std::string workingSeed = seed;
    // Seed all children with different permutations
    for (size_t i = 0; i < m_children.size(); i++) {
        m_children[i]->seed(workingSeed, layerCount - 1);
        workingSeed = permuteString(workingSeed);
    }
}

void Node::clear() {
    // Call clear on each child node and remove their pointers
    for (size_t i = 0; i < m_children.size(); i++) {
        m_children[i]->clear();
        m_children[i] = 0;
    }
    m_children.clear();
}