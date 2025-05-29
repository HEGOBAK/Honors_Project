/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */


#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdio>


using namespace std;

// Global Variable
#define NUM_PRINTABLE 95
#define ENCODED_FILE "output/encodedFile.txt"

// “SingleNode” holds one character + its frequency (and child pointers) ───
class SingleNode {
public:
    char          ch;     // the character (only valid in a leaf)
    int           freq;   // how many times it appeared
    SingleNode*   leftChild;   // left child in the Huffman tree
    SingleNode*   rightChild;  // right child in the Huffman tree

    // leaf constructor
    SingleNode(char c, int f) 
    {
        ch = c;
        freq = f;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    // internal‐node constructor (merging two children)
    SingleNode(SingleNode* l, SingleNode* r)
    {
        ch = '\0';
        freq = (l->freq + r->freq);
        leftChild = l;
        rightChild = r;
        
    }
};

// "LinkedList" is one element of our singly-linked list (the “tree”) ───
class LinkedList {
public:
    SingleNode* characterNode;  // pointer to that one‐character node
    LinkedList*   next;        // next element in the list

    // Initial constructor
    LinkedList(SingleNode* temp) 
    {
        characterNode = temp;
        next = nullptr;
    }
};

// ========== huffman.cpp ========== //
ifstream openFile();
void countFrequencies(ifstream& in, int hash_table[]);
void insertSorted(LinkedList*& treeHead, SingleNode* node_toInsert);
LinkedList* makeLinkedList(int hash_table[]);
SingleNode* buildTree(LinkedList*& treeHead);
void generateCodes(SingleNode* node, const string& path, string codes[]);
void deleteTree(SingleNode* node);

// ========== display.cpp ========== //
template<typename T>
void hash_display(const T table[]);
void linkedList_display(LinkedList* treeHead);
void preorder_display(SingleNode* node, int level);
void inorder_display(SingleNode* node, int level);
void postorder_display(SingleNode* node, int level);

// ========== encodeFile.cpp ========== //
void encodeFile(SingleNode*& root, int freq[], string codes[]);

// ========== printTree.cpp ========== //
void printTree(SingleNode* root);

// ========== showChar.cpp ========== //
template<typename T>
void showChar(const T table[], const string output);

// ========== outFile.cpp ========== //
void outFile(const string codes[]);

// ========== utilities.cpp ========== //
void printMenu();
int getMenuChoice();
void showCharFreq(const int freq[]);
void showCharCode(const string codes[]);
void printHuffmanCodes(const string codes[]);
void clearState(SingleNode*& root, int freq[], string codes[]);
bool quitting();
void clearScreen();
void waitForEnter();

#endif // HUFFMAN_H
