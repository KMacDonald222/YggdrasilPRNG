// File:        Nodes.h
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

// PRNG tree LFSR node class
class LFSRNode : public Node {
public:
    /*
    Initialize this LFSR node's memory
    Parameter: const std::string& seed - Seed data to define this LFSR node's
    initial state
    Parameter: unsigned int - Unused
    */
    void seed(const std::string&, unsigned int) override;
    /*
    Get a pseudo-random byte of data from this LFSR node
    Returns: uint8_t - A pseudo-random byte of LFSR output
    */
    uint8_t generate() override;
    /*
    Free this LFSR node's memory
    */
    void clear() override;

private:
    // The current state of this node's LFSR
    std::vector<bool> m_state;
    // The tap mask of this node's LFSR
    std::vector<bool> m_taps;
};

// PRNG tree matrix node class
class MatrixNode : public Node {
public:
    /*
    Initialize this matrix node's and its childrens' memory
    Parameter: const std::string& seed - Seed data to define this matrix node's
    initial state and pass to its children
    Parameter: unsigned int layerCount - The number of layers in the PRNG tree
    to generate below this matrix node
    */
    void seed(const std::string&, unsigned int) override;
    /*
    Get a pseudo-random byte of output from this matrix node
    Returns: uint8_t - A pseudo-random byte
    */
    uint8_t generate() override;
    /*
    Free this matrix node's and its childrens' memory
    */
    void clear() override;

private:
    // The rows of this matrix node's transformation matrix
    std::vector<std::vector<int>> m_matrix;
    // The index of the child currently producing output used to populate the
    // transformation matrix
    size_t m_populatingChild = 0;

    /*
    Shift/update the columns of this matrix node's transformation matrix using
    the output of its children
    */
    void shiftMatrix();
};

// PRNG tree XOR node class
class XORNode : public Node {
public:
    /*
    Generate and seed this XOR node's children
    Parameter: const std::string& seed - Seed data to determine the number of
    children of each type to generate
    Parameter: unsigned int layerCount - The number of PRNG tree layers to
    generate below this XOR node
    */
    void seed(const std::string&, unsigned int) override;
    /*
    Get a pseudo-random byte of output by XOR of the outputs of all children
    Returns: uint8_t - A pseudo-random byte
    */
    uint8_t generate() override;
};

// PRNG tree AND node class
class ANDNode : public Node {
public:
    /*
    Generate and seed this AND node's children
    Parameter: const std::string& seed - Seed data to determine the number of
    children of each type to generate
    Parameter: unsigned int layerCount - The number of PRNG tree layers to
    generate below this AND node
    */
    void seed(const std::string&, unsigned int) override;
    /*
    Get a pseudo-random byte of output by AND of the outputs of all children
    Returns: uint8_t - A pseudo-random byte
    */
    uint8_t generate() override;
};

// PRNG tree OR node class
class ORNode : public Node {
public:
    /*
    Generate and seed this OR node's children
    Parameter: const std::string& seed - Seed data to determine the number of
    children of each type to generate
    Parameter: unsigned int layerCount - The number of PRNG tree layers to
    generate below this OR node
    */
    void seed(const std::string&, unsigned int) override;
    /*
    Get a pseudo-random byte of output by OR of the outputs of all children
    Returns: uint8_t - A pseudo-random byte
    */
    uint8_t generate() override;
};

#endif