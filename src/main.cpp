/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

/* Purpose : Menu */

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// declarations
void printMenu();
void printCharacterFrequencies();
void printTree();
void printHuffmanCodes();
void showSingleCharCode();
void encodeWord();
void decodeText();
void encodeFile();
void decodeFile();

int main() {
    int choice;

    while (true) {
		printMenu();

        if (!(cin >> choice)) {
            cin.clear();                       // clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');            // discard chars until newline
			cout << "\n<=============================>\n";
            cout << "Invalid input; please enter a number between 1 and 9\n";
            continue;
        }

        // clear any leftover input after a valid number
        cin.ignore(numeric_limits<streamsize>::max(), '\n');                // discard chars until newline
		cout << "\n<=============================>\n";

        switch (choice) {
            case 1:
                printCharacterFrequencies();
                break;
            case 2:
                printTree();
                break;
            case 3:
                printHuffmanCodes();
                break;
            case 4:
                showSingleCharCode();
                break;
            case 5:
                encodeWord();
                break;
            case 6:
                decodeText();
                break;
            case 7:
                encodeFile();
                break;
            case 8:
                decodeFile();
                break;
            case 9:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option, please try again.\n";
				break;
        }
    }
    return 0;
}

void printMenu() {
	cout << "\n===== Huffman Coding Menu =====\n";
	cout << "1. Print Character Frequencies\n";
	cout << "2. Print Tree (Right-Root-Left Traversal)\n";
	cout << "3. Print Huffman Codes\n";
	cout << "4. Enter One Character and See its Huffman Code\n";
	cout << "5. Enter a Word and Encode It\n";
	cout << "6. Enter Encoded Text and Decode It\n";
	cout << "7. Enter File Name to Encode Text and Save It\n";
	cout << "8. Enter Encoded File Name to Decode and Save It\n";
	cout << "9. Quit\n";
	cout << "Select an option (1-9) : ";
}

// definitions
void printCharacterFrequencies() {
    cout << "[1] Print Character Frequencies - not implemented yet\n";
}

void printTree() {
    cout << "[2] Print Tree - not implemented yet\n";
}

void printHuffmanCodes() {
    cout << "[3] Print Huffman Codes - not implemented yet\n";
}

void showSingleCharCode() {
    cout << "[4] Single Character Code - not implemented yet\n";
}

void encodeWord() {
    cout << "[5] Encode Word - not implemented yet\n";
}

void decodeText() {
    cout << "[6] Decode Text - not implemented yet\n";
}

void encodeFile() {
    cout << "[7] Encode File - not implemented yet\n";
}
void decodeFile() {
    cout << "[8] Decode File - not implemented yet\n";
}
