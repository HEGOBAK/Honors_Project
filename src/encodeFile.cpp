/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// ─── Encode a file by building a huffman tree ───
void encodeFile(SingleNode*& root, int freq[], string codes[])
{
	// get an open file stream
    ifstream input;
    input = openFile();

    // count freqs
    countFrequencies(input, freq);

    // build list (“tree”) of single nodes
    LinkedList* treeHead = makeLinkedList(freq);

    // merge into one Huffman tree (root is a SingleNode)
    root = buildTree(treeHead);

    // generate codes
    generateCodes(root, "", codes);

    // Save the Huffman Codes into an output file
    outFile(input, codes);
    
    input.close();     // Close the input file
}