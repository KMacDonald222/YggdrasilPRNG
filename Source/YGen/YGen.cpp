// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/YggdrasilPRNG.h>

#include <iostream>
#include <bitset>
#include <fstream>
#include <climits>

// YGen module variables

const std::string PRINTABLE_CHARS = "abcdefghijklmnopqrstuvwxyz`1234567890"
    "-=[]\\;',./ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";
const std::string HEX_DIGITS = "0123456789ABCDEF";

// YGen module functions

/*
Use the PRNG library to generate data and write it formatted as binary
Parameter: const int& count - The number of bytes to generate
Parameter: const std::string& fileName - The file to write output to
Parameter: YggdrasilPRNG& yggd - Reference to the seed PRNG library
*/
void genBin(const int& count, const std::string& fileName,
    YggdrasilPRNG& yggd) {
    std::cout << "Generating " << count << " bytes" << std::endl << std::endl;
    // Initialize memory
    uint8_t byte = 0x00;
    if (fileName.empty()) {
        // Generate and write to console
        for (int i = 0; i < count; i++) {
            byte = yggd.generate();
            std::cout << std::bitset<8>(byte);
            std::cout.flush();
        }
        std::cout << std::endl << std::endl;
    } else {
        // Open file and initialize progress flags
        std::ofstream file(fileName, std::ios::binary);
        bool progress[10];
        for (int i = 0; i < 10; i++) {
            progress[i] = false;
        }
        // Generate and write to file
        for (int i = 0; i < count; i++) {
            byte = yggd.generate();
            file.write((const char*)(&byte), 1);
            // Update progress indicator
            for (int j = 0; j < 10; j++) {
                if ((float)i / (float)count > (float)j / 10.0f
                    && !progress[j]) {
                    progress[j] = true;
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                }
            }
        }
        file.close();
    }
    // Clear memory
    byte = 0x00;
    std::cout << "Done" << std::endl;
}

/*
Use the PRNG library to generate data and write it formatted as hexadecimal
Parameter: const int& count - The number of hexadecimal digits to generate
Parameter: const std::string& fileName - The file to write output to
Parameter: YggdrasilPRNG& yggd - Reference to the seed PRNG library
*/
void genHex(const int& count, const std::string& fileName,
    YggdrasilPRNG& yggd) {
    std::cout << "Generating " << count << " hexadecimal digits" << std::endl
        << std::endl;
    // Initialize memory
    uint8_t byte = 0x00;
    uint8_t h1 = 0x00;
    uint8_t h2 = 0x00;
    if (fileName.empty()) {
        // Generate and write to console
        for (int i = 0; i < count;) {
            byte = yggd.generate();
            // Print first digit of byte
            h1 = byte >> 4;
            std::cout << HEX_DIGITS[h1];
            std::cout.flush();
            if (++i >= count) {
                break;
            }
            // Print second digit of byte
            h2 = byte & 0x0f;
            std::cout << HEX_DIGITS[h2];
            std::cout.flush();
            i++;
        }
        std::cout << std::endl << std::endl;
    } else {
        // Open output file and initialize progress flags
        std::ofstream file(fileName);
        bool progress[10];
        for (int i = 0; i < 10; i++) {
            progress[i] = false;
        }
        // Generate and write to file
        for (int i = 0; i < count;) {
            byte = yggd.generate();
            // Write first digit of byte
            h1 = byte >> 4;
            file << HEX_DIGITS[h1];
            if (++i >= count) {
                break;
            }
            // Write second digit of byte
            h2 = byte & 0x0f;
            file << HEX_DIGITS[h2];
            i++;
            // Update progress indicator
            for (int j = 0; j < 10; j++) {
                if ((float)i / (float)count > (float)j / 10.0f
                    && !progress[j]) {
                    progress[j] = true;
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                }
            }
        }
        file.close();
    }
    // Clear memory
    byte = 0x00;
    h1 = 0x00;
    h2 = 0x00;
    std::cout << "Done" << std::endl;
}

/*
Use the PRNG library to generate data and write it formatted as text
Parameter: const int& count - The number of characters to generate
Parameter: const std::string& fileName - The file to write output to
Parameter: YggdrasilPRNG& yggd - Reference to the seed PRNG library
Parameter: const std::string& charSet - The character set to sample from
*/
void genText(const int& count, const std::string& fileName, YggdrasilPRNG& yggd,
    const std::string& charSet) {
    std::cout << std::endl << "Generating " << count << " characters"
        << std::endl << std::endl;
    // Initialize memory
    uint32_t index = 0x00000000;
    if (fileName.empty()) {
        // Generate and write to console
        for (int i = 0; i < count; i++) {
            // Get and print random index in character set
            index = 0x00000000;
            for (int j = 0; j < 4; j++) {
                index <<= 8;
                index |= yggd.generate();
            }
            index %= charSet.length();
            std::cout << charSet[index];
            std::cout.flush();
        }
        std::cout << std::endl << std::endl;
    } else {
        // Open output file and initialize progress flags
        std::ofstream file(fileName);
        bool progress[10];
        for (int i = 0; i < 10; i++) {
            progress[i] = false;
        }
        // Generate and write to file
        for (int i = 0; i < count; i++) {
            // Get and write random index in character set
            index = 0x00000000;
            for (int j = 0; j < 4; j++) {
                index <<= 8;
                index |= yggd.generate();
            }
            index %= charSet.length();
            file << charSet[index];
            // Update progress indicator
            for (int j = 0; j < 10; j++) {
                if ((float)i / (float)count > (float)j / 10.0f
                    && !progress[j]) {
                    progress[j] = true;
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                }
            }
        }
        file.close();
    }
    // Clear memory
    index = 0x00000000;
    std::cout << "Done" << std::endl;
}

/*
Use the PRNG library to generate data and write it formatted as integers
Parameter: const int& count - The number of integers to generate
Parameter: const std::string& fileName - The file to write output to
Parameter: YggdrasilPRNG& yggd - Reference to the seed PRNG library
Parameter: const int& minimum - The minimum value to generate
Parameter: const int& maximum - The maximum value to generate
*/
void genInts(const int& count, const std::string& fileName, YggdrasilPRNG& yggd,
    const int& minimum, const int& maximum) {
    std::cout << std::endl << "Generating " << count << " integers" << std::endl
        << std::endl;
    // Initialize memory
    uint32_t d = 0x00000000;
    int range = maximum - minimum + 1;
    int integer = 0;
    if (fileName.empty()) {
        // Generate and write to console
        for (int i = 0; i < count; i++) {
            // Get and write random integer
            d = 0x00000000;
            for (int j = 0; j < 4; j++) {
                d <<= 8;
                d |= yggd.generate();
            }
            d %= range;
            integer = minimum + (int)d;
            std::cout << integer << ", ";
            std::cout.flush();
        }
        std::cout << std::endl << std::endl;
    } else {
        // Open output file and initialize progress flags
        std::ofstream file(fileName);
        bool progress[10];
        for (int i = 0; i < 10; i++) {
            progress[i] = false;
        }
        // Generate and write to file
        for (int i = 0; i < count; i++) {
            // Get and write random integer
            d = 0x00000000;
            for (int j = 0; j < 4; j++) {
                d <<= 8;
                d |= yggd.generate();
            }
            d %= range;
            integer = minimum + (int)d;
            file << integer << ", ";
            // Update progress indicator
            for (int j = 0; j < 10; j++) {
                if ((float)i / (float)count > (float)j / 10.0f
                    && !progress[j]) {
                    progress[j] = true;
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                }
            }
        }
        file.close();
    }
    // Clear memory
    d = 0x00000000;
    range = 0;
    integer = 0;
    std::cout << "Done" << std::endl;
}

/*
Use the PRNG library to generate data and write it formatted as floats
Parameter: const int& count - The number of floats to generate
Parameter: const std::string& fileName - The file to write output to
Parameter: YggdrasilPRNG& yggd - Reference to the seed PRNG library
Parameter: const float& minimum - The minimum value to generate
Parameter: const float& maximum - The maximum value to generate
*/
void genFloats(const int& count, const std::string& fileName,
    YggdrasilPRNG& yggd, const float& minimum, const float& maximum) {
    std::cout << "Generating " << count << " floats" << std::endl << std::endl;
    // Initialize memory
    float range = maximum - minimum;
    uint32_t r = 0x00000000;
    float d = 0.0f;
    float flt = 0.0f;
    if (fileName.empty()) {
        // Generate and write to console
        for (int i = 0; i < count; i++) {
            r = 0x00000000;
            for (int j = 0; j < 4; j++) {
                r <<= 8;
                r |= yggd.generate();
            }
            d = (float)r / (float)UINT_MAX;
            flt = minimum + (range * d);
            std::cout << flt << ", ";
            std::cout.flush();
        }
    } else {
        // Open output file and initialize progress flags
        std::ofstream file(fileName);
        bool progress[10];
        for (int i = 0; i < 10; i++) {
            progress[i] = false;
        }
        // Generate and write to file
        for (int i = 0; i < count; i++) {
            r = 0x00000000;
            for (int j = 0; j < 4; j++) {
                r <<= 8;
                r |= yggd.generate();
            }
            d = (float)r / (float)UINT_MAX;
            flt = minimum + (range * d);
            file << flt << ", ";
            // Update progress indicator
            for (int j = 0; j < 10; j++) {
                if ((float)i / (float)count > (float)j / 10.0f
                    && !progress[j]) {
                    progress[j] = true;
                    std::cout << (j * 10) << "%, ";
                    std::cout.flush();
                }
            }
        }
        file.close();
    }
    // Clear memory
    range = 0.0f;
    r = 0x00000000;
    d = 0.0f;
    flt = 0.0f;
    std::cout << "Done" << std::endl;
}

/*
Main entry point for the YGen driver program
Returns: int - The program's exit code
*/
int main() {
    srand((unsigned int)time(0));
    std::cout << "Yggdrasil PRNG Data Generator" << std::endl << std::endl;
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
    // Take in output symbol count
    std::cout << std::endl << "Output symbol count: ";
    std::string symbolCountStr = "";
    if (!std::getline(std::cin, symbolCountStr)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        layerCount = 0;
        return EXIT_FAILURE;
    }
    int symbolCount = std::atoi(symbolCountStr.c_str());
    if (symbolCount < 1) {
        std::cout << "Invalid output symbol count" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        layerCount = 0;
        return EXIT_FAILURE;
    }
    // Take in output file name
    std::cout << "Output file name (empty for console): ";
    std::string fileName = "";
    if (!std::getline(std::cin, fileName)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        layerCount = 0;
        return EXIT_FAILURE;
    }
    if (fileName.empty()) {
        std::cout << "Writing output to console" << std::endl;
    } else {
        // Ensure that output file is writable
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Invalid output file name" << std::endl;
            // Clear memory
            for (size_t i = 0; i < seed.length(); i++) {
                seed[i] = '\0';
            }
            seed.clear();
            layerCount = 0;
            return EXIT_FAILURE;
        }
        file.close();
    }
    // Take in output mode
    std::cout << std::endl << "1 - Binary" << std::endl << "2 - Hexadecimal"
        << std::endl << "3 - Text" << std::endl << "4 - Integers" << std::endl
        << "5 - Floats" << std::endl << "Output mode: ";
    std::string modeStr = "";
    if (!std::getline(std::cin, modeStr)) {
        std::cout << "Invalid input" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        layerCount = 0;
        return EXIT_FAILURE;
    }
    int mode = std::atoi(modeStr.c_str());
    // Ensure output mode selection is in bounds
    if (mode < 1 || mode > 5) {
        std::cout << "Invalid output mode" << std::endl;
        // Clear memory
        for (size_t i = 0; i < seed.length(); i++) {
            seed[i] = '\0';
        }
        seed.clear();
        layerCount = 0;
        return EXIT_FAILURE;
    }
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
    // Generate data
    switch (mode) {
        case 1: {
            genBin(symbolCount, fileName, yggd);
            break;
        }
        case 2: {
            genHex(symbolCount, fileName, yggd);
            break;
        }
        case 3: {
            // Take in the character set to sample from
            std::cout << "Character set (empty for default): ";
            std::string charSet = "";
            if (!std::getline(std::cin, charSet)) {
                std::cout << "Invalid input" << std::endl;
                return EXIT_FAILURE;
            }
            if (charSet.empty()) {
                charSet = PRINTABLE_CHARS;
                std::cout << "Default character set: \"" << charSet << "\""
                    << std::endl;
            }
            genText(symbolCount, fileName, yggd, charSet);
            break;
        }
        case 4: {
            // Take in minimum value
            std::cout << "Minimum value (empty for 0): ";
            std::string minimumStr = "";
            if (!std::getline(std::cin, minimumStr)) {
                std::cout << "Invalid input" << std::endl;
                return EXIT_FAILURE;
            }
            int minimum = std::atoi(minimumStr.c_str());
            // Take in maximum value
            std::cout << "Maximum value: ";
            std::string maximumStr = "";
            if (!std::getline(std::cin, maximumStr)) {
                std::cout << "Invalid input" << std::endl;
                return EXIT_FAILURE;
            }
            int maximum = std::atoi(maximumStr.c_str());
            if (maximum <= minimum) {
                std::cout << "Invalid maximum value" << std::endl;
                return EXIT_FAILURE;
            }
            genInts(symbolCount, fileName, yggd, minimum, maximum);
            break;
        }
        case 5: {
            // Take in minimum value
            std::cout << "Minimum value (empty for 0): ";
            std::string minimumStr = "";
            if (!std::getline(std::cin, minimumStr)) {
                std::cout << "Invalid input" << std::endl;
                return EXIT_FAILURE;
            }
            float minimum = std::atof(minimumStr.c_str());
            // Take in maximum value
            std::cout << "Maximum value: ";
            std::string maximumStr = "";
            if (!std::getline(std::cin, maximumStr)) {
                std::cout << "Invalid input" << std::endl;
                return EXIT_FAILURE;
            }
            float maximum = std::atof(maximumStr.c_str());
            if (maximum <= minimum) {
                std::cout << "Invalid maximum value" << std::endl;
                return EXIT_FAILURE;
            }
            genFloats(symbolCount, fileName, yggd, minimum, maximum);
            break;
        }
    }
    // Clear memory
    yggd.clear();
    std::cout << std::endl << "Cleared memory" << std::endl;
    return EXIT_SUCCESS;
}