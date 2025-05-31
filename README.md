# Huffman Encoding Project

A simple C++ implementation of the Huffman encoding algorithm, wrapped in a menu-driven console interface.

## What It Does

1. **Reads** any text file.
2. **Counts** the frequency of each printable ASCII character (32–126).
3. **Builds** a Huffman tree from those frequencies.
4. **Generates** variable-length binary codes for each character.
5. **Encodes** and **decodes** text or entire files.
6. **Saves** encoded output to disk and can reload it for decoding.

---

## Prerequisites

- A C++17-capable compiler (e.g. `g++`)
- Make (GNU Make)

---

## Building with the Makefile

We provide a simple Makefile so you don’t have to type long compile commands.

**How to use**  
- make -- compile everything and create an exe name "huffman"
- make clean-all -- deletes everything
- make re -- make clean then make


