# File:			Makefile
# Author:		Keegan MacDonald (KMacDonald222)
# Created:		2025.10.15@10:17ADT

# Define build constants
Compiler = g++ -Wall -Wextra -pedantic -O3 -std=c++20
Archiver = ar rcs
# Define YggdrasilPRNG library paths
YggdrasilPRNG_Source = ../../Source/YggdrasilPRNG/
YggdrasilPRNG_Include = -I../../Vendor/Include/ -I../../Include/YggdrasilPRNG/
YggdrasilPRNG_Target = ../../Binaries/Linux/libYggdrasilPRNG.a
# Define YGen driver program paths
YGen_Source = ../../Source/YGen/
YGen_Include = -I../../Include/
YGen_Libraries = -L../../Binaries/Linux/ -lYggdrasilPRNG \
	-L../../Vendor/Libraries/ -lsha
YGen_Target = ../../Binaries/Linux/YGen
# Define YCipher driver program paths
YCipher_Source = ../../Source/YCipher/
YCipher_Include = -I../../Include/
YCipher_Libraries = -L../../Binaries/Linux/ -lYggdrasilPRNG \
	-L../../Vendor/Libraries/ -lsha
YCipher_Target = ../../Binaries/Linux/YCipher

# Build YggdrasilPRNG library and all driver programs
all:
	make $(YggdrasilPRNG_Target)
	make $(YGen_Target)
	make $(YCipher_Target)

# Build YggdrasilPRNG library
$(YggdrasilPRNG_Target): $(YggdrasilPRNG_Source)YggdrasilPRNG.o \
		$(YggdrasilPRNG_Source)Utilities.o $(YggdrasilPRNG_Source)Node.o \
		$(YggdrasilPRNG_Source)LFSRNode.o $(YggdrasilPRNG_Source)MatrixNode.o \
		$(YggdrasilPRNG_Source)XORNode.o $(YggdrasilPRNG_Source)ANDNode.o \
		$(YggdrasilPRNG_Source)ORNode.o
	$(Archiver) $(YggdrasilPRNG_Target) $(YggdrasilPRNG_Source)YggdrasilPRNG.o \
		$(YggdrasilPRNG_Source)Utilities.o $(YggdrasilPRNG_Source)Node.o \
		$(YggdrasilPRNG_Source)LFSRNode.o $(YggdrasilPRNG_Source)MatrixNode.o \
		$(YggdrasilPRNG_Source)XORNode.o $(YggdrasilPRNG_Source)ANDNode.o \
		$(YggdrasilPRNG_Source)ORNode.o

$(YggdrasilPRNG_Source)YggdrasilPRNG.o: $(YggdrasilPRNG_Source)YggdrasilPRNG.cpp
	$(Compiler) $(YggdrasilPRNG_Include) \
		-o $(YggdrasilPRNG_Source)YggdrasilPRNG.o \
		-c $(YggdrasilPRNG_Source)YggdrasilPRNG.cpp

$(YggdrasilPRNG_Source)Utilities.o: $(YggdrasilPRNG_Source)Utilities.cpp
	$(Compiler) $(YggdrasilPRNG_Include) -o $(YggdrasilPRNG_Source)Utilities.o \
		-c $(YggdrasilPRNG_Source)Utilities.cpp

$(YggdrasilPRNG_Source)Node.o: $(YggdrasilPRNG_Source)Node.cpp
	$(Compiler) $(YggdrasilPRNG_Include) -o $(YggdrasilPRNG_Source)Node.o \
		-c $(YggdrasilPRNG_Source)Node.cpp

$(YggdrasilPRNG_Source)LFSRNode.o: $(YggdrasilPRNG_Source)LFSRNode.cpp
	$(Compiler) $(YggdrasilPRNG_Include) -o $(YggdrasilPRNG_Source)LFSRNode.o \
		-c $(YggdrasilPRNG_Source)LFSRNode.cpp

$(YggdrasilPRNG_Source)MatrixNode.o: $(YggdrasilPRNG_Source)MatrixNode.cpp
	$(Compiler) $(YggdrasilPRNG_Include) \
		-o $(YggdrasilPRNG_Source)MatrixNode.o \
		-c $(YggdrasilPRNG_Source)MatrixNode.cpp

$(YggdrasilPRNG_Source)XORNode.o: $(YggdrasilPRNG_Source)XORNode.cpp
	$(Compiler) $(YggdrasilPRNG_Include) -o $(YggdrasilPRNG_Source)XORNode.o \
		-c $(YggdrasilPRNG_Source)XORNode.cpp

$(YggdrasilPRNG_Source)ANDNode.o: $(YggdrasilPRNG_Source)ANDNode.cpp
	$(Compiler) $(YggdrasilPRNG_Include) -o $(YggdrasilPRNG_Source)ANDNode.o \
		-c $(YggdrasilPRNG_Source)ANDNode.cpp

$(YggdrasilPRNG_Source)ORNode.o: $(YggdrasilPRNG_Source)ORNode.cpp
	$(Compiler) $(YggdrasilPRNG_Include) -o $(YggdrasilPRNG_Source)ORNode.o \
		-c $(YggdrasilPRNG_Source)ORNode.cpp

# Build YGen driver program
$(YGen_Target): $(YGen_Source)YGen.o
	$(Compiler) -o $(YGen_Target) $(YGen_Source)YGen.o $(YGen_Libraries)

$(YGen_Source)YGen.o: $(YGen_Source)YGen.cpp
	$(Compiler) $(YGen_Include) -o $(YGen_Source)YGen.o \
		-c $(YGen_Source)YGen.cpp

# Build YCipher driver program
$(YCipher_Target): $(YCipher_Source)YCipher.o
	$(Compiler) -o $(YCipher_Target) $(YCipher_Source)YCipher.o \
		$(YCipher_Libraries)

$(YCipher_Source)YCipher.o: $(YCipher_Source)YCipher.cpp
	$(Compiler) $(YCipher_Include) -o $(YCipher_Source)YCipher.o \
		-c $(YCipher_Source)YCipher.cpp

# Clear all build files
clean:
	-rm $(YggdrasilPRNG_Source)*.o
	-rm $(YggdrasilPRNG_Target)
	-rm $(YGen_Source)*.o
	-rm $(YGen_Target)
	-rm $(YCipher_Source)*.o
	-rm $(YCipher_Target)