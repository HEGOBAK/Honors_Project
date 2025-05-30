/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"

// <================= START => OPEN FILE  =================> //

// ─── Ask for user input repeatedly until the user provides a valid filename ───
ifstream openFile(const string usage) {
    string filename;
    while (true) {
        cout << "Enter name of text file to " << usage << ": ";
        if (!getline(cin, filename)) {
            // clear error state and retry
            cin.clear();
            continue;
        }

        // try in current directory
        ifstream in(filename);
        if (in) {
            cout << "Opened \"" << filename << "\" successfully.\n";
            waitForEnter();
            return in;
        }

        // try in ../tests/ if they gave just a fileName
        string alt = "tests/" + filename;
        ifstream in2(alt);
        if (in2) {
            cout << "Opened \"" << alt << "\" successfully.\n";
            return in2;
        }
        
        // neither worked
        cerr << "Error: cannot open '" << filename 
             << "' or '" << alt << "'. Please try again.\n\n";
    }
}

// <====================== Open File Is DONE ======================> //



//  <======== Below Is From Open File -> Unordered Hash Table ========> //

// ─── Extract data from file and count printable‐ASCII freqs into freq[0..127] ───
void countFrequencies(ifstream& in, int freq[]) {
    // Initialize the hash table
    for (int i = 0; i < NUM_PRINTABLE; ++i) freq[i] = 0;

    char c;
    while (in.get(c)) {     // Going thru all char in the file

        // Getting the index for the hash table
        unsigned char uc = static_cast<unsigned char>(c) - 32;
        if (uc >= 0 && uc < NUM_PRINTABLE)
            // Increase the freq of that char
            ++freq[uc];
    }
}

// <====================== Hash Table Is DONE ======================> //



// <======== Below Is From Hash Table -> Ordered Linked List ========> //

// ─── Build the initial list (“tree”) of single-character nodes ───
LinkedList* makeLinkedList(int hash_table[]) {
    LinkedList* treeHead = nullptr;
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        if (hash_table[i] > 0) {
            // create one‐node leaf and insert sorted
            insertSorted(treeHead, new SingleNode(char(i + 32), hash_table[i]));
        }
    }
    return treeHead;
}

// ─── Insert a new SingleNode into our list-tree in ascending freq order ───
void insertSorted(LinkedList*& treeHead, SingleNode* node_toInsert) {
    LinkedList* newChar = new LinkedList(node_toInsert);

    // empty list or node is smallest → becomes new head
    if (!treeHead || node_toInsert->freq < treeHead->characterNode->freq) {
        newChar->next = treeHead;
        treeHead = newChar;
        return;
    }

    // otherwise, walk until the next node’s freq is bigger
    LinkedList* cur = treeHead;
    while (cur->next && cur->next->characterNode->freq <= newChar->characterNode->freq) {
        cur = cur->next;
    }

    // splice in
    newChar->next   = cur->next;
    cur->next  = newChar;
}

// <================= Ordered Linked List Is DONE =================> //



// <============== Below Is From Linked List -> Tree ==============> //

// ─── Merge until only one SingleNode remains (the full Huffman tree) ───
SingleNode* buildTree(LinkedList*& treeHead) {
    while (treeHead && treeHead->next) {

        // pop the first two SingleNodes
        SingleNode* left = treeHead->characterNode;

        // Temporary holder to free memory while we traverse to the next node
        LinkedList* t1   = treeHead;
        treeHead = treeHead->next;
        delete t1;

        SingleNode* right = treeHead->characterNode;
        LinkedList*   t2    = treeHead;
        treeHead = treeHead->next;
        delete t2;

        // merge into a new parent SingleNode (Internal-Node) and re-insert
        insertSorted(treeHead, new SingleNode(left, right));
    }
    // now treeHead->SingleNode is the root of the Huffman tree
    return treeHead ? treeHead->characterNode : nullptr;
}

// <================= Huffman Tree Is DONE =================> //



// <======= Below Is From Huffman Tree -> Huffman Codes =======> //

// ─── Walk the tree to generate Huffman Codes using recursive ───
void generateCodes(SingleNode* node, const string& path, string codes[]) {
    if (!node) return;  // Base case
    if (!node->leftChild && !node->rightChild) {

        // Storing the final huffman code to the character
        codes[static_cast<unsigned char>(node->ch) - 32] = path;

    } else {
        // If it goes left, the path add '0'
        generateCodes(node->leftChild,  path + '0', codes);

        // If it goes right, the path add '1'
        generateCodes(node->rightChild, path + '1', codes);
    }
}

// <================= Huffman Codes Is DONE =================> //



// <================= Below Is Clear Tree =================> //

// ─── Free memory using recursive ───
void deleteTree(SingleNode* node) {
    if (!node) return;   // Base case
    deleteTree(node->leftChild);
    deleteTree(node->rightChild);
    delete node;  // Delete the root
}

// <================= Clear Tree Is DONE =================> //