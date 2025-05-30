/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// ─── print Huffman Code tree ───
void printTree(SingleNode* root) {
	string line;
    while (true) {
        // prompt for traversal order
        cout << "Select traversal - (I)norder, pr(E)order, po(S)torder (or Q to quit): ";
        if (!getline(cin, line)) {
            // I/O error (e.g., EOF), bail out
            cout << "Input error; aborting tree print.\n";
            continue;
        }
        if (line.empty()) {
            // empty input just continue
            continue;
        }

        if (line == "Q" || line == "q") 
            break;                  // user chose to quit

        char choice = toupper(line[0]);  
        if (choice == 'I') {
            cout << "\n--- Inorder (Left-Root-Right) ---\n";
            inorder_display(root, 0);   // print with indentation
        }
        else if (choice == 'E') {
            cout << "\n--- Preorder (Root-Left-Right) ---\n";
            preorder_display(root, 0);
        }
        else if (choice == 'S') {
            cout << "\n--- Postorder (Left-Right-Root) ---\n";
            postorder_display(root, 0);
        }
        else {
            // unrecognized letter
            cout << "Invalid choice; please enter I, E, or S.\n";
        }
    }
}