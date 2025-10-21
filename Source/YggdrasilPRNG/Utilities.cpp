// File:        Utilities.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.16@15:12ADT

#include "Utilities.h"

#include <SHA/SHA512.h>

#include <cstdint>

// Utilities module variables

// Randomly selected set of permutations of 4 objects
std::vector<std::vector<size_t>> PERMUTATIONS_4 = {
    { 2, 3, 1, 0, },
    { 1, 0, 2, 3, },
    { 0, 3, 1, 2, },
    { 0, 2, 1, 3, },
    { 2, 0, 1, 3, },
    { 3, 1, 2, 0, },
    { 2, 0, 3, 1, },
    { 3, 2, 1, 0, },
    { 1, 2, 3, 0, },
    { 1, 0, 3, 2, },
    { 0, 3, 2, 1, },
    { 3, 0, 1, 2, },
    { 3, 2, 0, 1, },
    { 2, 1, 3, 0, },
    { 1, 3, 0, 2, },
    { 2, 1, 0, 3, },
};
// Randomly selected set of permutations of 8 objects
std::vector<std::vector<size_t>> PERMUTATIONS_8 = {
    { 6, 0, 7, 2, 1, 4, 3, 5, },
    { 3, 2, 4, 6, 0, 7, 5, 1, },
    { 1, 5, 0, 3, 6, 2, 7, 4, },
    { 0, 6, 2, 7, 3, 5, 4, 1, },
    { 2, 3, 7, 5, 0, 4, 6, 1, },
    { 2, 6, 5, 3, 0, 4, 1, 7, },
    { 2, 0, 1, 5, 3, 4, 7, 6, },
    { 2, 0, 1, 5, 4, 6, 7, 3, },
    { 5, 0, 1, 6, 3, 4, 7, 2, },
    { 5, 2, 7, 1, 3, 6, 0, 4, },
    { 3, 1, 7, 2, 5, 0, 6, 4, },
    { 3, 0, 5, 6, 1, 7, 2, 4, },
    { 2, 0, 5, 1, 6, 3, 7, 4, },
    { 1, 4, 7, 2, 6, 3, 5, 0, },
    { 3, 0, 5, 1, 7, 6, 4, 2, },
    { 6, 7, 5, 1, 0, 2, 4, 3, },
};

// Utilities module functions

std::vector<bool> hashBinary(const std::string& input) {
    const std::string hashSymbols = "0123456789abcdef";
    // Get the hexadecimal hash from the SHA vendor library
    std::string hashHex = hashHexadecimal(input);
    std::vector<bool> hashBin(512);
    for (size_t i = 0; i < hashHex.length(); i++) {
        // Find the binary representation of the next 4-bit hex symbol
        uint8_t j = 0x00;
        for (; j < 0xff; j++) {
            if (hashHex[i] == hashSymbols[j]) {
                break;
            }
        }
        // Add the binary to the boolean representation
        for (size_t k = 0; k < 4; k++) {
            hashBin[(i * 4) + k] = (j >> (4 - k - 1)) & 0x01;
        }
    }
    return hashBin;
}

std::string hashHexadecimal(const std::string& input) {
    // Use vendor library to compute hash
    SHA512 sha512;
    return sha512.hash(input);
}

std::string permuteString(const std::string& input) {
    std::string hashHex = hashHexadecimal(input);
    // Pad the input to the next multiple if 8 in length
    std::string paddedInput = input;
    size_t paddingIndex = 0;
    do {
        paddedInput += hashHex[paddingIndex++];
    } while (paddedInput.length() % 8 != 0);
    // Break input into 4-character chunks
    std::vector<std::string> chunks4;
    for (size_t i = 0; i < paddedInput.length(); i += 4) {
        chunks4.push_back(paddedInput.substr(i, 4));
    }
    // Clear the padded input copy
    for (size_t i = 0; i < paddedInput.length(); i++) {
        paddedInput[i] = '\0';
    }
    paddedInput.clear();
    // Permute each chunk
    for (size_t i = 0; i < chunks4.size(); i++) {
        std::vector<bool> chunkHash = hashBinary(chunks4[i]);
        // Find the index of the permutation to use by the hash
        uint8_t permIndex = 0x00;
        for (size_t j = 0; j < 4; j++) {
            permIndex = (permIndex << 1)
                | (uint8_t)chunkHash[(chunkHash.size() - 4) + j];
        }
        // Clear the chunk hash from memory
        for (size_t x = 0; x < chunkHash.size(); x++) {
            chunkHash[x] = '\0';
        }
        chunkHash.clear();
        // Perform permutation
        std::string permChunk = "";
        for (size_t j = 0; j < 4; j++) {
            permChunk += chunks4[i][PERMUTATIONS_4[permIndex][j]];
        }
        chunks4[i] = permChunk;
        // Clear the permutation index and permuted chunk from memory
        permIndex = 0x00;
        for (size_t x = 0; x < permChunk.length(); x++) {
            permChunk[x] = '\0';
        }
        permChunk.clear();
    }
    // Concatenate the chunks into the 4-permuted string
    std::string permuted4Input = "";
    for (size_t i = 0; i < chunks4.size(); i++) {
        permuted4Input += chunks4[i];
    }
    // Clear the 4-character chunks from memory
    for (size_t i = 0; i < chunks4.size(); i++) {
        for (size_t j = 0; j < chunks4[i].length(); j++) {
            chunks4[i][j] = '\0';
        }
        chunks4[i].clear();
    }
    chunks4.clear();
    // Break the 4-permuted string into 8 chunks
    std::vector<std::string> chunks8;
    for (size_t i = 0; i < permuted4Input.size();
            i += permuted4Input.size() / 8) {
        chunks8.push_back(permuted4Input.substr(i, permuted4Input.size() / 8));
    }
    // Permute the 8 chunks and concatenate them into the output
    std::string output = "";
    std::vector<bool> permHash = hashBinary(permuted4Input);
    // Clear the 4-permuted input from memory
    for (size_t i = 0; i < permuted4Input.length(); i++) {
        permuted4Input[i] = '\0';
    }
    permuted4Input.clear();
    // Compute the 8-permutation index from the hash
    uint8_t permIndex = 0x00;
    for (size_t i = 0; i < 4; i++) {
        permIndex = (permIndex << 1)
            | (uint8_t)permHash[(permHash.size() - 4) + i];
    }
    // Perform the 8-permutation
    for (size_t i = 0; i < 8; i++) {
        output += chunks8[PERMUTATIONS_8[permIndex][i]];
    }
    // Clear the 8 chunks and permutation index from memory
    for (size_t i = 0; i < chunks8.size(); i++) {
        for (size_t j = 0; j < chunks8[i].length(); j++) {
            chunks8[i][j] = '\0';
        }
        chunks8[i].clear();
    }
    chunks8.clear();
    permIndex = 0x00;
    return output;
}