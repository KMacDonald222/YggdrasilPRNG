// File:        Utilities.h
// Author:      Keegan MacDonald (KMacDonald222)
// Created:     2025.10.16@15:04ADT

#ifndef YGGDRASILPRNG_UTILITIES_H
#define YGGDRASILPRNG_UTILITIES_H

#include <vector>
#include <string>

/*
Compute the SHA-512 hash of a string represented in binary
Parameter: const std::string& input - The string to compute the SHA-512 hash of
Returns: std::vector<bool> - The binary representation of the hash
*/
extern std::vector<bool> hashBinary(const std::string&);
/*
Compute the SHA-512 hash of a string represented in hexadecimal
Parameter: const std::string& input - The string to compute the SHA-512 hash of
Returns: std::string - The hexadecimal representation of the hash
*/
extern std::string hashHexadecimal(const std::string&);
/*
Pad and permute a string according to its SHA-512 hash
Parameter: const std::string& input - The string to be padded and permuted
Returns: std::string - The padded and permuted string
*/
extern std::string permuteString(const std::string&);

#endif