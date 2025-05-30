/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// ─── Decode an entire file of bits into plain text ───
void decodeFile(SingleNode* root) {

	char bit;
	int bits_on_line = 0;
	const int max_bits_per_line = 50;

    // open the encoded input file
    ifstream in = openFile("decode");

    // open the decoded‐output file
    ofstream out(DECODED_FILE);
    if (!out) {
        cerr << "Error: could not open " << DECODED_FILE << " for writing\n";
        in.close();
        return;
    }

    // traverse bit by bit
    SingleNode* curr = root;
    while (in.get(bit)) {
        // skip anything but '0' or '1'
        if (bit != '0' && bit != '1') 
            continue;

		// traversing down the tree
        curr = (bit == '0') ? curr->leftChild : curr->rightChild;
        if (!curr) {
            cerr << "Error: invalid encoding encountered in file.\n";
            break;
        }

        // leaf reached → write the character and reset
        if (!curr->leftChild && !curr->rightChild) {
            out.put(curr->ch);
            if (++bits_on_line >= max_bits_per_line) {
                out.put('\n');
                bits_on_line = 0;
            }
            curr = root;
        }
    }
    cout << "Decoded text saved to " << DECODED_FILE << "\n";
    in.close();
    out.close();
    waitForEnter();
}

// ─── Decode interactively from the terminal ───
void decodeText(SingleNode* root) {

    string bits;
    while (true) {

        cout << "\nEnter Huffman bit-string to decode (or Q to quit): ";
       
		if (!getline(cin, bits)) {
			// I/O error: clear state and retry
            cin.clear();
			continue;
        }
        
		if (bits == "Q" || bits == "q") {
            break;
        }

        string decoded;
        SingleNode* curr = root;
        bool valid = true;

        for (char bit : bits) {
            if (bit == '0') {
                curr = curr->leftChild;
            }
            else if (bit == '1') {
                curr = curr->rightChild;
            }
            else {
                cout << "Error: invalid character '" << bit 
                     << "'. Only '0' or '1' allowed.\n";
                valid = false;
                break;
            }

            if (!curr) {
                cout << "Error: path led to null—this bit-string is not valid.\n";
                valid = false;
                break;
            }

            // leaf? append and reset
            if (!curr->leftChild && !curr->rightChild) {
                decoded += curr->ch;
                curr = root;
            }
        }

        if (valid) {
            cout << "Decoded text: " << decoded << "\n";
        }
    }
}