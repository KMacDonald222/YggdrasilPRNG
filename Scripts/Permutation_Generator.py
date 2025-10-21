# File:     Permutation_Generator.py
# Author:   Keegan MacDonald (KMacDonald222)
# Created:  2025.10.18@00:56ADT

import random

# Get parameters
n = int(input("Object count: "))
p = int(input("Permutation count: "))

# Initialize memory
selections = []
i = 0

# Generate p permutations of n objects
while i < p:
    objects = list(range(int(n)))
    permutation = []
    # Generate permutation
    for j in range(n):
        r = random.randint(0, len(objects) - 1)
        permutation.append(objects[r])
        del objects[r]
    # Detect duplicates
    if not permutation in selections:
        selections.append(permutation)
        i += 1

# Output permutations to console
for i in range(len(selections)):
    print("{ ", end = "")
    for j in range(n):
        print(selections[i][j], ", ", sep = "", end = "")
    print("},")