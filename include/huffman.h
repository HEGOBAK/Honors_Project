
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>       // for remove()
#include "Node.h"
#include "LinkedList.h"
#include "Utilities.h"
using namespace std;

// ──────────────────────────────────────────────────────────────────────────
// The Huffman class encapsulates all state & behavior needed to:
//   1) read an input file → count frequencies,
//   2) build a sorted linked list of single‐char SingleNode*,
//   3) merge into a Huffman tree,
//   4) generate codes[], 
//   5) encode/decode text and files,
//   6) display freq/tree/codes, etc.
//  
// ──────────────────────────────────────────────────────────────────────────

class Huffman {
private:

    // ── Private Variables ──
    int            freq_[NUM_PRINTABLE];   // frequency hash table
    string         codes_[NUM_PRINTABLE];  // Huffman code hash table
    SingleNode*    root_;                  // root of the Huffman tree
    LinkedList*    treeHead_;              // head of the sorted linked list
    bool           fileEncoded_;

    // ─── File I/O helpers ───
    ifstream openFile(const string usage) const;                // prompt & open file
    void     outFile(ifstream& in, const string codes[]) const; // write bits to ENCODED_FILE

    // ─── Frequency counting ───
    void countFrequencies(ifstream& in);  // fill freq_[]

    // ─── Linked‐list building ───
    LinkedList* makeLinkedList();                       // build sorted list from freq_[]
    void        insertSorted(LinkedList*& head,
                             SingleNode* nodeToInsert); // helper: insert one node

    // ─── Tree merging ───
    SingleNode* buildTree();  // merge list into a single Huffman tree, return root

    // ─── Code generation ───
    void generateCodes(SingleNode* node, const string& path); 
        // recursive: store “0”/“1” paths into codes_[] at leaves

    // ─── Tree deletion ───
    void deleteTree(SingleNode* node);  // recursively delete all nodes under node

    // ─── Tree display helpers ───
    void preorder_display(SingleNode* node, int level) const;
    void inorder_display(SingleNode* node, int level) const;
    void postorder_display(SingleNode* node, int level) const;
    void reverseInorder_display(SingleNode* node, int level) const;

public:
    // ── Constructor: zero-out freq_[], clear codes_[], set pointers to nullptr ──
    Huffman()
    {
        root_ = nullptr;
        treeHead_ = nullptr;
        fileEncoded_ = false;
        for (int i = 0; i < NUM_PRINTABLE; ++i) {
            freq_[i] = 0;
            codes_[i] = "";
        }
    }

    // ── Destructor: call clearState() to free everything and delete files ──
    ~Huffman()
    {
        clearState();
    }

    // ──────────────────────────────────────────────────────────────────────────
    // Menu actions (called by main()):
    //  1) showCharFreq()
    //  2) printTree()
    //  3) printHuffmanCodes()
    //  4) showCharCode()
    //  5) encodeWord()
    //  6) decodeText()
    //  7) encodeFile()
    //  8) decodeFile()
    //  9) (quit/restart is handled in main)
    // ──────────────────────────────────────────────────────────────────────────

    void showCharFreq() const {showChar(freq_, "Frequency");};         // option 1
    void printTree() const;            // option 2
    void printHuffmanCodes() const {hash_display(codes_);};     // option 3
    void showCharCode() const {showChar(codes_, "Huffman Codes");};         // option 4
    void encodeWord() const;           // option 5
    void decodeText() const;           // option 6
    void encodeFile();                 // option 7
    void decodeFile() const;           // option 8

    // ── returns true if encodeFile() has been called successfully ──
    bool fileEncoded() const {return fileEncoded_;}
	
	// ──────────────────────────────────────────────────────────────────────────
    // clearState(): delete the Huffman tree, delete any linked‐list wrappers,
    // zero out freq_/codes_, remove on-disk files, set fileEncoded_ = false.
    // ──────────────────────────────────────────────────────────────────────────
    void clearState();
};

#endif // HUFFMAN_H
