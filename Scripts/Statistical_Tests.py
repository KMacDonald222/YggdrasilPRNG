# File:     Statistical_Tests.py
# Author:   Keegan MacDonald (KMacDonald222)
# Created:  2025.10.23@10:36ADT

import os

# Define useful paths
wdir = "../../Tests/Statistical_Tests/"
scr = "sp800_22_tests/sp800_22_tests.py"
# Run test on each file in the Data directory
for fileName in os.listdir(wdir + "Data/"):
    # Set up file names
    fullFileName = wdir + "Data/" + fileName
    print("Running tests on \"" + fullFileName + "\"")
    resultsName = wdir + "Results/" + fileName + ".txt"
    # Run test command
    cmd = "python3 " + wdir + scr + " " + fullFileName + " > " + resultsName
    print("> " + cmd)
    os.system(cmd)