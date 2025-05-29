/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// ========== Display Hash Table ========== //

template<typename T>
void hash_display(const T table[]) {
   // how many entries per line
    int printed;
    char ch;
    const int perLine = 10;

    // header
    cout << "\n <========= Hash Table =========> \n";

    // data
	printed = 0;   // how many non-zero entries we’ve shown so far
    for (int i = 0; i < NUM_PRINTABLE; ++i) {

		// If the character doesn't exist then skip
        if (table[i] == T()) continue;

		// at the start of each row, print the leading '| '
        if (printed % perLine == 0) {
            cout << "|  ";
        }
        ch = char(i + 32);   // Get the character
		cout << ch << "-" << '[' << table[i] << ']';
		printed++;
    
        // New line after each full row of entries, space otherwise
        if (printed % perLine == 0)
            cout << " |\n";
        else
            cout << "  ";
    }

    // Ensure the last line ends with a newline if it wasn’t exactly full
    if (printed % perLine != 0)
        cout << "|\n";

    waitForEnter();
}

template void hash_display<int>(const int[]);
template void hash_display<string>(const string[]);

// ========== END OF Display Hash Table ========== //

// ------------------------------------------------------------

// ========== Display Linked Listed ========== //

void linkedList_display(LinkedList* treeHead) {
	int printed;
	LinkedList* cur;
	const int perLine = 10;

	cur = treeHead;
	printed = 0;
	cout << "head";
	while (cur && cur->characterNode->freq > 0) {
		cout << "->[" << cur->characterNode->ch   // the character stored in this node
             << ", " << cur->characterNode->freq  // its frequency/count
             << "]";
		printed++;
		cur = cur->next;
		if (printed % perLine == 0)
			cout << '\n';
    }
    cout << "\n";
}

// ========== END OF Display Linked Listed ========== //

// ------------------------------------------------------------

// ========== Display Indented Huffman Tree ========== //

// ─── Preorder (root, left, right) ───
void preorder_display(SingleNode* node, int level) {
    if (!node) return;   // Base case

    // level by 'level' spaces
    for (int i = 0; i < level; ++i) 
        cout << '-';

    // leaf? show its character, otherwise a '*' for internal nodes
    if (!node->leftChild && !node->rightChild)
        cout << '[' << node->ch;
    else
        cout << "[*";
    cout << "(" << node->freq << ")]\n";

    preorder_display(node->leftChild,  level + 1);
    preorder_display(node->rightChild, level + 1);
}

// ─── Inorder (left, root, right) ───
void inorder_display(SingleNode* node, int level) {
    if (!node) return;   // Base case

    inorder_display(node->leftChild, level + 1);

    for (int i = 0; i < level; ++i) 
        cout << '-';
    if (!node->leftChild && !node->rightChild)
        cout << '[' << node->ch;
    else
        cout << "[*";
    cout << "(" << node->freq << ")]\n";

    inorder_display(node->rightChild, level + 1);
}

// ─── Postorder (left, right, root) ───

void postorder_display(SingleNode* node, int level) {
    if (!node) return;   // Base case

    postorder_display(node->leftChild,  level + 1);
    postorder_display(node->rightChild, level + 1);

    for (int i = 0; i < level; ++i) 
        cout << '-';
    if (!node->leftChild && !node->rightChild)
        cout << '[' << node->ch;
    else
        cout << "[*";
    cout << "(" << node->freq << ")]\n";
}

// ========== END OF Display Indented Huffman Tree ========== //
