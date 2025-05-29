/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// ─── Print out a character's Huffman code ───
template<typename T>
void showChar(const T table[], const string output) {
    string line;
    char ch;
    unsigned char uc;

    // keep prompting until we get a printable ASCII character
    while (true) {
        cout << "Enter a single character: ";
        if (!getline(cin, line)) {
            // I/O error: clear state and retry
            cin.clear();
            continue;
        }
        if (line.empty()) {
			// input empty just continue
            continue;
        }

        ch = line[0];
        uc = static_cast<unsigned char>(ch);

        // check printable ASCII range
        if (uc < 32 || uc > 126) {
            cout << "Character out of printable ASCII range (32-126). Please try again.\n";
            continue;
        }
        break;
    }

    // locate the char using idx
    int idx = uc - 32;
    if (table[idx] == T()) {
        cout << "Character '" << ch << "' not found.\n";
        waitForEnter();
    } else {
        cout << output << " for '" << ch << "' is: " << table[idx] << "\n";
        waitForEnter();
    }
}

template void showChar<int>(const int[], const string);
template void showChar<string>(const string[], const string);
