/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// ─── Print menu ───
void printMenu() {
    cout << "\n========================================\n";
    cout << "       Huffman Encoding Main Menu      \n";
    cout << "========================================\n";
    cout << " 1. Print character weights (frequencies)\n";
    cout << " 2. Print tree (Right-Root-Left format)\n";
    cout << " 3. Print all Huffman codes\n";
    cout << " 4. Enter a character and show its code\n";
    cout << " 5. Enter a word → ASCII + Huffman codes\n";
    cout << " 6. Enter encoded text and decode it\n";
    cout << " 7. Load & encode a file\n";
    cout << " 8. Decode a file\n";
    cout << " 9. Quit / Restart\n";
    cout << "========================================\n";
}

// ─── Prompt until the user picks a valid option (1–9) ───
int getMenuChoice() {
    string line;
    int choice;
    while (true) {
        cout << "Select an option (1-9): ";
        if (!getline(cin, line)) {
            // input error, clear state and retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
			// input empty just continue
            continue;
        }
		// attempt to convert the input string to an integer
        try {
            choice = stoi(line);
        } catch (...) {
			// non‐numeric input: ask again
            cout << "Invalid input; please enter a number between 1 and 9.\n";
            continue;
        }
		// ensure the choice is within the valid menu range
        if (choice < 1 || choice > 9) {
            cout << "Please enter a number between 1 and 9.\n";
            continue;
        }
        return choice;
    }
}

// ─── Print out each character's frequency ───
void showCharFreq(const int freq[]) {
	showChar(freq, "Frequency");
}

// ─── Print out each character's Huffman Code ───
void showCharCode(const string codes[]) {
	showChar(codes, "Huffman Codes");
}


// ─── Print out each character's Huffman code ───
void printHuffmanCodes(const string codes[]) {
	hash_display(codes);
}

// ─── Reset all of our Huffman state ───
void clearState(SingleNode*& root, int freq[], string codes[]) {
    // free any existing tree
    if (root) {
        deleteTree(root);
        root = nullptr;
    }
    // zero out the frequency table
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        freq[i] = 0;
    }
    // clear all the code strings
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        codes[i].clear();
    }

    // delete the output file
    remove(ENCODED_FILE);    // From <cstdio>
}

// ─── Prompt user to Quit (Q/q) or Restart (R/r) ───
bool quitting() {
    string line;
    while (true) {
        cout << "Enter 'Q' to quit or 'R' to restart: ";
        if (!getline(cin, line)) {
            // I/O error: clear and retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
            // input empty just continue
            continue;
        }

        char c = line[0];
        if (c == 'q' || c == 'Q') {
            return true;    // user chose to quit
        }
        if (c == 'r' || c == 'R') {
            return false;   // user chose to restart
        }
        cout << "Invalid input. Please enter Q or R.\n";
    }
}

// ─── Clear the terminal (ANSI escape sequence) ───
void clearScreen() {
    // 2J clears the screen, H moves cursor to home
    cout << "\033[2J\033[H";
}

// wait for the user to hit ENTER
void waitForEnter() {
    cout << "\n(Press ENTER to continue)";
    cin.ignore();
}