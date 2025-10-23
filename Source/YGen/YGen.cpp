// File:        YGen.cpp
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.15@10:15ADT

#include <YggdrasilPRNG/YggdrasilPRNG.h>

#include <iostream>
#include <fstream>
#include <chrono>

// YGen module variables

const unsigned int FILE_SIZE = 128502;
const std::string CHARS = "abcdefghijklmnopqrstuvwxyz`1234567890-=[]\\;',./"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ~!@#$%^&*()_+{}|:\"<>?";

// YGen module functions

int main() {
    srand((unsigned int)time(0));
    std::vector<unsigned int> times;
    unsigned int index = 0;
    while (true) {
        // Open output file stream
        std::cout << "Writing " << index << ".bin" << std::endl;
        std::ofstream outputFile("../../Tests/Statistical_Tests/Data/"
            + std::to_string(index++) + ".bin", std::ios::binary);
        YggdrasilPRNG yggd;
        std::string seed = "";
        for (unsigned int i = 0; i < 64; i++) {
            seed += CHARS[rand() % CHARS.length()];
        }
        std::cout << "Seed: \"" << seed << "\"" << std::endl;
        yggd.seed(seed, 4);
        // Generate data
        std::cout << "Generating" << std::endl;
        std::chrono::steady_clock::time_point start
            = std::chrono::steady_clock::now();
        bool progress[10];
        for (int i = 0; i < 10; i++) {
            progress[i] = false;
        }
        for (unsigned int i = 0; i < FILE_SIZE; i++) {
            uint8_t byte = yggd.generate();
            outputFile.write((const char*)(&byte), 1);
            for (int x = 0; x < 10; x++) {
                if ((float)i / (float)FILE_SIZE > (float)x / 10.0f
                    && !progress[x]) {
                    progress[x] = true;
                    std::cout << (x * 10) << "%, ";
                    std::cout.flush();
                }
            }
        }
        std::cout << std::endl;
        std::chrono::steady_clock::time_point end
            = std::chrono::steady_clock::now();
        unsigned int elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            end - start).count();
        std::cout << elapsed << "s elapsed" << std::endl;
        times.push_back(elapsed);
        float averageTime = 0.0f;
        for (size_t i = 0; i < times.size(); i++) {
            averageTime += (float)times[i];
        }
        averageTime /= (float)times.size();
        std::cout << "Average time: " << averageTime << "s" << std::endl;
        std::cout << "Clearing" << std::endl;
        yggd.clear();
        outputFile.close();
    }
}