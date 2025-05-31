
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define NUM_PRINTABLE 95        // printable ASCII from 32..126

// constants for file names
#define ENCODED_FILE  "output/encodedFile.txt"
#define DECODED_FILE  "output/decodedFile.txt"

// ──────────────────────────────────────────────────────────────────────────
// printMenu: displays the main menu choices
// ──────────────────────────────────────────────────────────────────────────
void printMenu();

// ──────────────────────────────────────────────────────────────────────────
// getMenuChoice: prompt until the user enters an integer 1-9
// ──────────────────────────────────────────────────────────────────────────
int getMenuChoice();

// ──────────────────────────────────────────────────────────────────────────
// showCharFreq: wrapper to call showChar for int hash table
// ──────────────────────────────────────────────────────────────────────────
void showCharFreq(const int freq[]);

// ──────────────────────────────────────────────────────────────────────────
// showCharCode: wrapper to call showChar for string hash table
// ──────────────────────────────────────────────────────────────────────────
void showCharCode(const string codes[]);

// ──────────────────────────────────────────────────────────────────────────
// printHuffmanCodes: wrapper to call hash_display for string hash table
// ──────────────────────────────────────────────────────────────────────────
void printHuffmanCodes(const string codes[]);

// ──────────────────────────────────────────────────────────────────────────
// quitting: prompt user to enter Q/q (quit) or R/r (restart).
// ──────────────────────────────────────────────────────────────────────────
bool quitting();

// ──────────────────────────────────────────────────────────────────────────
// clearScreen: ANSI escape to clear screen                                   
// waitForEnter: pause until user hits ENTER                                  
// ──────────────────────────────────────────────────────────────────────────
void clearScreen();
void waitForEnter();

// ──────────────────────────────────────────────────────────────────────────
// showChar<T>: prompt for one char, then display its “value” (freq or code).
//   If T=int: uses “Frequency”; if T=string: uses “Huffman Codes”.
// ──────────────────────────────────────────────────────────────────────────
template<typename T>
void showChar(const T table[], const string output);

// ──────────────────────────────────────────────────────────────────────────
// hash_display<T>: print non‐empty entries of a T‐table side by side.
// ──────────────────────────────────────────────────────────────────────────
template<typename T>
void hash_display(const T table[]);

#endif // UTILITIES_H
