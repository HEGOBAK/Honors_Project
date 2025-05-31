
#include "Utilities.h"
#include <limits>   // for numeric_limits

// ──────────────────────────────────────────────────────────────────────────
// printMenu: displays the main menu choices
// ──────────────────────────────────────────────────────────────────────────
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

// ──────────────────────────────────────────────────────────────────────────
// getMenuChoice: prompt until user enters a valid option
// ──────────────────────────────────────────────────────────────────────────
int getMenuChoice() {
    string line;
    int choice;
    while (true) {
        cout << "Select an option (1-9): ";
        if (!getline(cin, line)) {
            // clear error state and retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
            // input empty, retry
            continue;
        }
        try {
            choice = stoi(line);
        }
        catch (...) {
            // non‐numeric input
            cout << "Invalid input; please enter a number between 1 and 9.\n";
            continue;
        }
        if (choice < 1 || choice > 9) {
            cout << "Please enter a number between 1 and 9.\n";
            continue;
        }
        return choice;
    }
}

// ──────────────────────────────────────────────────────────────────────────
// showCharFreq: wrapper to call showChar<int>                    (option 1)
// ──────────────────────────────────────────────────────────────────────────
void showCharFreq(const int freq[]) {
    showChar(freq, "Frequency");
}

// ──────────────────────────────────────────────────────────────────────────
// showCharCode: wrapper to call showChar<string>                  (option 4)
// ──────────────────────────────────────────────────────────────────────────
void showCharCode(const string codes[]) {
    showChar(codes, "Huffman Codes");
}

// ──────────────────────────────────────────────────────────────────────────
// printHuffmanCodes: wrapper to call hash_display<string>         (option 3)
// ──────────────────────────────────────────────────────────────────────────
void printHuffmanCodes(const string codes[]) {
    hash_display(codes);
}

// ──────────────────────────────────────────────────────────────────────────
// quitting: prompt for Q or R (matches your original).               
// ──────────────────────────────────────────────────────────────────────────
bool quitting() {
    string line;
    while (true) {
        cout << "Enter 'Q' to quit or 'R' to restart: ";
        if (!getline(cin, line)) {
            // I/O error, retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
            continue;
        }
        char c = line[0];
        if (c == 'q' || c == 'Q') {
            return true;
        }
        if (c == 'r' || c == 'R') {
            return false;
        }
        cout << "Invalid input. Please enter Q or R.\n";
    }
}

// ──────────────────────────────────────────────────────────────────────────
// clearScreen: ANSI escape to clear screen                             
// ──────────────────────────────────────────────────────────────────────────
void clearScreen() {
    cout << "\033[2J\033[H";
}

// ──────────────────────────────────────────────────────────────────────────
// waitForEnter: pause until user hits ENTER                            
// ──────────────────────────────────────────────────────────────────────────
void waitForEnter() {
    cout << "\n(Press ENTER to continue)";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ──────────────────────────────────────────────────────────────────────────
// showChar<T>: prompt user for a single character, then print
// ──────────────────────────────────────────────────────────────────────────
template<typename T>
void showChar(const T table[], const string output) {
    string line;
    char ch;
    unsigned char uc;

    // keep prompting until we get a printable ASCII character or Q
    while (true) {
        cout << "Enter a single character : ";
        if (!getline(cin, line)) {
            // I/O error: retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
            continue;
        }

        ch = line[0];
        uc = static_cast<unsigned char>(ch);

        // check printable ASCII range
        if (uc < 32 || uc > 126) {
            cout << "Character out of printable ASCII range (32-126). Please try again.\n";
            continue;
        }

        int idx = uc - 32;
        // compare table[idx] to default T() to test “empty”
        if (table[idx] == T()) {
            cout << "Character '" << ch << "' not found.\n";
        }
        else {
            cout << output << " for '" << ch << "' is: " << table[idx] << "\n";
        }

		cout << "\n(Press Q to return to the menu, or any other key to look up again) : ";
		if (!getline(cin, line)) {
            // I/O error: retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
            continue;
        }
		if (line[0] == 'Q' || line[0] == 'q')
			break;
    }
}

// explicitly instantiate so linker finds them
template void showChar<int>(const int[], const string);
template void showChar<string>(const string[], const string);

// ──────────────────────────────────────────────────────────────────────────
// hash_display<T>: print hash table
// ──────────────────────────────────────────────────────────────────────────
template<typename T>
void hash_display(const T table[]) {
    int printed = 0;          // how many entries we've printed
    const int perLine = 10;
    char ch;

    cout << "\n <========= Hash Table =========> \n";
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        // skip “empty”: T() is 0 for int, "" for string
        if (table[i] == T()) continue;

        if (printed % perLine == 0) {
            cout << "|  ";
        }

        ch = static_cast<char>(i + 32);
        cout << ch << "-" << "[" << table[i] << "]";
        printed++;

        if (printed % perLine == 0) {
            cout << " |\n";
        }
        else {
            cout << "  ";
        }
    }
    if (printed % perLine != 0) {
        cout << "|\n";
    }
    waitForEnter();
}

// explicitly instantiate so linker finds them
template void hash_display<int>(const int[]);
template void hash_display<string>(const string[]);

