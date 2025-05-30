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
    input = openFile("encode");

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


// ─── Encode a file by building a huffman tree ───
void encodeWord(const string  codes[]) {
    
    bool   valid;
    string word;

    while (true) {
        cout << "\nEnter a word to encode : ";
        
        if (!getline(cin, word)){
            // I/O error: clear state and retry
            cin.clear(); 
            continue;                    
        }
        
        valid = true;
        
        string result;
        string ascii;
        for (unsigned char c : word) {
            int idx = c - 32;
            if (codes[idx].empty()) {
                cout << "Error: no Huffman code for character '" << c 
                     << "'. Please try again.\n";
                valid = false;
                break;
            }

            // Merging the huffman codes
            result += codes[idx];

            // Merging the ascii binary codes
            for (int bit = 7; bit >= 0; --bit) {
                ascii += ((c >> bit) & 1) ? '1' : '0';
            }
        }
        
        if (valid) {
            cout << "Huffman encoding: " << result << "\n\n";
            cout << "ASCII Binary representation : " << ascii << '\n';
            waitForEnter();
            break;
        }
    }
}

