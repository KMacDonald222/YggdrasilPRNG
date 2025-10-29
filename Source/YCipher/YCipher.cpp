// File:        YCipher.cpp
// Author:      Keegan MacDonald
// Created:     2025.10.23@13:42ADT

#include <YggdrasilPRNG/YggdrasilPRNG.h>

#include <iostream>
#include <fstream>

// YCipher module variables

const std::string PRINTABLE_CHARS = "abcdefghijklmnopqrstuvwxyz`1234567890"
    "-=[]\\;',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

// YCipher module functions

/*
Main entry point for the YCipher driver program
Returns: int - The program's exit code
*/
int main() {
    srand((unsigned int)time(0));
    std::cout << "Yggdrasil PRNG Cipher" << std::endl << std::endl;
    // Take in seed
    std::cout << "Seed (empty for random): ";
    std::string seed = "";
    if (!std::getline(std::cin, seed)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        return EXIT_FAILURE;
    }
    if (seed.empty()) {
        // Generate random seed
        for (size_t i = 0; i < 32; i++) {
            seed += PRINTABLE_CHARS[rand() % PRINTABLE_CHARS.length()];
        }
        std::cout << "Random seed: \"" << seed << "\"" << std::endl;
    }
    // Take in PRNG tree layer count
    std::cout << "Tree layer count: ";
    std::string layerCountStr = "";
    if (!std::getline(std::cin, layerCountStr)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        for (size_t i = 0; i < layerCountStr.length(); i++) {
            layerCountStr[i] = '\0';
        }
        layerCountStr.clear();
        return EXIT_FAILURE;
    }
    int layerCount = std::atoi(layerCountStr.c_str());
    if (layerCount < 2) {
        std::cout << "Invalid tree layer count" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        for (size_t i = 0; i < layerCountStr.length(); i++) {
            layerCountStr[i] = '\0';
        }
        layerCountStr.clear();
        layerCount = 0;
        return EXIT_FAILURE;
    }
    // Clear memory
    for (size_t i = 0; i < layerCountStr.length(); i++) {
        layerCountStr[i] = '\0';
    }
    layerCountStr.clear();
    // Seed PRNG library
    YggdrasilPRNG yggd;
    yggd.seed(seed, layerCount);
    std::cout << std::endl << "Seeded Yggdrasil PRNG" << std::endl << std::endl;
    // Clear memory
    for (size_t i = 0; i < seed.length(); i++) {
        seed[i] = '\0';
    }
    seed.clear();
    layerCount = 0;
    // Take in input file name
    std::cout << "Input file name: ";
    std::string inputFileName = "";
    if (!std::getline(std::cin, inputFileName)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        yggd.clear();
        return EXIT_FAILURE;
    }
    // Open input file and read size
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cout << "Invalid input file" << std::endl;
        // Clear memory
        yggd.clear();
        return EXIT_FAILURE;
    }
    inputFile.seekg(0, std::ios::end);
    std::streampos inputFileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    inputFileSize -= inputFile.tellg();
    // Take in output file name
    std::cout << "Output file name: ";
    std::string outputFileName = "";
    if (!std::getline(std::cin, outputFileName)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        yggd.clear();
        return EXIT_FAILURE;
    }
    // Open output file
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.good()) {
        std::cout << "Invalid output file" << std::endl;
        // Clear memory
        yggd.clear();
        return EXIT_FAILURE;
    }
    std::cout << std::endl;
    // Combine input file data with PRNG data and write it to output file
    bool progress[10];
    for (int i = 0; i < 10; i++) {
        progress[i] = false;
    }
    uint8_t byte = 0x00;
    for (std::streampos i = 0; i < inputFileSize; i += 1) {
        // Convert data
        inputFile.read((char*)(&byte), 1);
        byte ^= yggd.generate();
        outputFile.write((const char*)(&byte), 1);
        // Update progress indicator
        for (int j = 0; j < 10; j++) {
            if ((float)i / (float)inputFileSize > (float)j / 10.0f
                && !progress[j]) {
                progress[j] = true;
                std::cout << (j * 10) << "%, ";
                std::cout.flush();
            }
        }
    }
    std::cout << "Done" << std::endl;
    // Clear memory
    byte = 0x00;
    yggd.clear();
    inputFile.close();
    outputFile.close();
    std::cout << std::endl << "Cleared memory" << std::endl;
    return EXIT_SUCCESS;
}