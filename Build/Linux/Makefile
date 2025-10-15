# File:			Makefile
# Author:		Keegan MacDonald (KMacDonald222)
# Created:		2025.10.15@10:17ADT

# Define build constants
Compiler = g++ -Wall -Wextra -pedantic -O3
Archiver = ar rcs
YggdrasilPRNG_Source = ../../Source/YggdrasilPRNG/
YggdrasilPRNG_Include = -I../../Include/YggdrasilPRNG/
YggdrasilPRNG_Target = ../../Binaries/Linux/libYggdrasilPRNG.a
YGen_Source = ../../Source/YGen/
YGen_Include = -I../../Include/
YGen_Libraries = -L../../Binaries/Linux/ -lYggdrasilPRNG
YGen_Target = ../../Binaries/Linux/YGen

# Build YggdrasilPRNG library and all driver programs
all:
	make $(YggdrasilPRNG_Target)
	make $(YGen_Target)

# Build YggdrasilPRNG library
$(YggdrasilPRNG_Target): $(YggdrasilPRNG_Source)YggdrasilPRNG.o
	$(Archiver) $(YggdrasilPRNG_Target) $(YggdrasilPRNG_Source)YggdrasilPRNG.o

$(YggdrasilPRNG_Source)YggdrasilPRNG.o: $(YggdrasilPRNG_Source)YggdrasilPRNG.cpp
	$(Compiler) $(YggdrasilPRNG_Include) \
		-o $(YggdrasilPRNG_Source)YggdrasilPRNG.o \
		-c $(YggdrasilPRNG_Source)YggdrasilPRNG.cpp

# Build YGen driver program
$(YGen_Target): $(YGen_Source)YGen.o
	$(Compiler) -o $(YGen_Target) $(YGen_Source)YGen.o $(YGen_Libraries)

$(YGen_Source)YGen.o: $(YGen_Source)YGen.cpp
	$(Compiler) $(YGen_Include) -o $(YGen_Source)YGen.o \
		-c $(YGen_Source)YGen.cpp

# Clear all build files
clean:
	-rm $(YggdrasilPRNG_Source)*.o
	-rm $(YggdrasilPRNG_Target)
	-rm $(YGen_Source)*.o
	-rm $(YGen_Target)