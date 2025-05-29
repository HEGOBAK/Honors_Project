/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

/* Purpose : Menu + wiring Huffman state through options */

#include "../include/huffman.h"

// --- our menu‐action (Left-Over) ---
// void encodeWord();
// void decodeText(SingleNode* root);
// void decodeFile(SingleNode* root);

int main() {
    int     choice;
    bool    fileEncoded = false;     // This ensure that at least one file has been encoded
    SingleNode* root      = nullptr;       // Huffman‐tree root
    int     freq[NUM_PRINTABLE];     // frequency hash table
    string  codes[NUM_PRINTABLE];    // Huffman code hash table

    while (true) {
        
        // Clear the screen
        clearScreen();

        // List out the menu 
        printMenu();

        // Get user's choice
        choice = getMenuChoice();

        // enforce that file must be encoded first
        if (!fileEncoded && choice != 7 && choice != 9) {
            cout << "⚠  Please choose option 7 first to load & encode a file.\n";
            waitForEnter();
            continue;
        }

        switch (choice) {
            case 1:
                showCharFreq(freq);
                break;
            case 2:
                printTree(root);
                break;
            case 3:
                printHuffmanCodes(codes);
                break;
            case 4:
                showCharCode(codes);
                break;
            case 5:
                // encodeWord();
                break;
            case 6:
                // decodeText(root);
                break;
            case 7:
                if (fileEncoded)
                {
                    clearState(root, freq, codes);
                    fileEncoded = false;
                }
                encodeFile(root, freq, codes);
                fileEncoded = true;
                break;
            case 8:
                // decodeFile(root);
                break;
            case 9:
                if (fileEncoded) {
                    clearState(root, freq, codes);
                    fileEncoded = false;
                    if (quitting()) return 0;
                    waitForEnter();
                }
                else
                    return 0;
                break;
            default:
                cout << "Invalid option, please try again.\n";
                break;
        }
    }
    return 0;
}
