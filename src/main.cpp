
#include "Huffman.h"
using namespace std;

int main() {
    Huffman huff;
    int choice;

    while (true) {

        // Clear screen & show menu
        clearScreen();
        printMenu();

        choice = getMenuChoice();

        // enforce that option 7 (encodeFile) comes before 1..6
        if (!huff.fileEncoded() && choice != 7 && choice != 9) {
            cout << "⚠  Please choose option 7 first to load & encode a file.\n";
            waitForEnter();
            continue;
        }

        switch (choice) {
            case 1:
                huff.showCharFreq();
                break;

            case 2:
                huff.printTree();
                break;

            case 3:
                huff.printHuffmanCodes();
                break;

            case 4:
                huff.showCharCode();
                break;

            case 5:
                huff.encodeWord();
                break;

            case 6:
                huff.decodeText();
                break;

            case 7:
                huff.encodeFile();
                break;

            case 8:
                huff.decodeFile();
                break;

            case 9:
                if (huff.fileEncoded()) {
                    bool q = quitting();
                    if (q) {
                        return 0;
                    }
                    // Restart by clearing existing Huffman state
                    huff.clearState();
                }
                else {
                    return 0;
                }
                break;

            default:
                cout << "Invalid option, please try again.\n";
                waitForEnter();
                break;
        }
    }
    return 0;
}
