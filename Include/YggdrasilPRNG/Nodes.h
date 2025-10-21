// Files:       Nodes.h
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.16@14:49ADT

#ifndef YGGDRASILPRNG_NODES_H
#define YGGDRASILPRNG_NODES_H

#include <string>
#include <vector>
#include <cstdint>

// Abstract PRNG tree node class
class Node {
public:
    /*
    Virutalized destructor for clearing node memory
    */
    virtual ~Node();
    /*
    Initialize this node's and its childrens' memory
    Parameter: const std::string& seed - Seed data to define this node's initial
    state and the tree structure below it
    Parameter: unsigned int layerCount - The number of layers of the PRNG tree
    to generate below this node
    */
    virtual void seed(const std::string&, unsigned int);
    /*
    Get a pseudo-random byte of data from this node
    Returns: uint8_t - A pseudo-random byte
    */
    virtual uint8_t generate() = 0;
    /*
    Free this node's and its childrens' memory
    */
    virtual void clear();

protected:
    // Set of pointers to this node's children in the PRNG tree
    std::vector<Node*> m_children;
};

#endif