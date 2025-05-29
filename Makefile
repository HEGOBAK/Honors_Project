# /* **************************************** */
# /*                                          */
# /*     Project: CIS22C Huffman Encoding     */
# /*     Authors: Jeriel & Chu                */
# /*                                          */
# /* **************************************** */

# Makefile for CIS22C Huffman Encoding project

COMPILE  = g++
CFLAGS   = -std=c++17 -Wall -Wextra -Iinclude

SRCDIR   = src
BUILDDIR = build
# Grab every .cpp file in the src directory
SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
# For each src/xyz.cpp, produce build/xyz.o
OBJECTS  = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TARGET   = huffman

.PHONY: all re clean

all: $(TARGET)

# Link step
$(TARGET): $(OBJECTS)
	$(COMPILE) $(CFLAGS) $^ -o $@

# Compile step, creating build/ if needed
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(COMPILE) $(CFLAGS) -c $< -o $@

# Ensure build/ exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# "re" will clean then rebuild
re: clean all

# Remove everything
clean:
	rm -rf $(BUILDDIR) $(TARGET)
