# File:     Results_Compiler.py
# Author:   Keegan MacDonald (KMacDonald222)
# Created:  2025.10.23@13:24ADT

# Initialize memory
pass_counts = [ 0 ] * 15
path = "../../Tests/Statistical_Tests/Results/"
test_names = [ ]
test_names.append("monobit")
test_names.append("frequency within block")
test_names.append("runs")
test_names.append("longest run ones in a block")
test_names.append("binary matrix rank")
test_names.append("dft")
test_names.append("non-overlapping template matching")
test_names.append("overlapping template matching")
test_names.append("maurer's universal")
test_names.append("linear complexity")
test_names.append("serial")
test_names.append("approximate entropy")
test_names.append("cumulative sums")
test_names.append("random excursion")
test_names.append("random excursion variant")

# Iterate through files
for index in range(100):
    file = open(path + str(index) + ".bin.txt", "r")
    lines = file.readlines()
    file.close()
    for i in range(len(lines)):
        lines[i] = lines[i].strip()
    for i in range(15):
        if lines[len(lines) - 15 + i].endswith("PASS"):
            pass_counts[i] += 1

# Print results
for i in range(15):
    print(test_names[i] + " test: " + str(pass_counts[i]) + "%")