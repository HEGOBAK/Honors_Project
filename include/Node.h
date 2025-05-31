
#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

// “SingleNode” holds one character + its frequency (and child pointers)
class SingleNode {
public:
    char          ch;          // the character (only valid in a leaf)
    int           freq;        // how many times it appeared
    SingleNode*   leftChild;   // left child in the Huffman tree
    SingleNode*   rightChild;  // right child in the Huffman tree

    // ── leaf constructor ──
    SingleNode(char c, int f)
    {
        ch = c;
        freq = f;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    // ── internal‐node constructor (merging two children) ──
    SingleNode(SingleNode* l, SingleNode* r)
    {
        ch = '\0';
        freq = (l->freq + r->freq);
        leftChild = l;
        rightChild = r;
    }
};

#endif // NODE_H
