/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

/* Purpose : Menu + wiring Huffman state through options */

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// --- our menu‐actio ---
void printMenu();
void printCharacterFrequencies(const int freq[]);
void printTree(SingleNode* root);
void printHuffmanCodes(const string codes[]);
void showSingleCharCode(const string codes[]);
void encodeWord();
void decodeText(SingleNode* root);
void encodeFile(int freq[], SingleNode*& root, string codes[]);
void decodeFile(SingleNode* root);

int main() {
    // --- this “state” lives across menu calls ---
    bool      fileEncoded = false;
    int       freq[128]   = {0};           // character counts
    SingleNode* root      = nullptr;       // Huffman‐tree root
    string    codes[128];                  // bit-strings for each ASCII

    int choice;
    while (true) {
        printMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n<=============================>\n";
            cout << "Invalid input; please enter a number between 1 and 9\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n<=============================>\n";

        // block everything except (7) load-and-encode and (9) quit
        if (!fileEncoded && choice != 7 && choice != 9) {
            cout << "⚠  Please choose option 7 first to load & encode a file.\n";
            continue;
        }

        switch (choice) {
            case 1:
                printCharacterFrequencies(freq);
                break;
            case 2:
                printTree(root);
                break;
            case 3:
                printHuffmanCodes(codes);
                break;
            case 4:
                showSingleCharCode(codes);
                break;
            case 5:
                encodeWord();
                break;
            case 6:
                decodeText(root);
                break;
            case 7:
                encodeFile(freq, root, codes);
                fileEncoded = true;
                break;
            case 8:
                decodeFile(root);
                break;
            case 9:
                cout << "Exiting program. Goodbye!\n";
                // clean up
                deleteTree(root);
                return 0;
            default:
                cout << "Invalid option, please try again.\n";
                break;
        }
    }
    return 0;
}
