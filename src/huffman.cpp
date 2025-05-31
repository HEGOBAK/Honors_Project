
#include "Huffman.h"
#include <cstdio>   // for remove()
using namespace std;

// ──────────────────────────────────────────────────────────────────────────
// clearState: frees any existing tree, deletes linked‐list wrappers,
//             zeroes freq_[] and codes_[], removes on‐disk files,
//             sets fileEncoded_ to false.
// ──────────────────────────────────────────────────────────────────────────
void Huffman::clearState() {
    // free any existing Huffman tree
    if (root_) {
        deleteTree(root_);
        root_ = nullptr;
    }

    // delete the linked‐list wrappers (and the SingleNode inside each)
    while (treeHead_) {
        LinkedList* tmp = treeHead_;
        treeHead_ = treeHead_->next;
        delete tmp;
    }
    treeHead_ = nullptr;

    // zero out frequency table and codes
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        freq_[i] = 0;
        codes_[i].clear();
    }

    // remove any on‐disk files
    remove(ENCODED_FILE);
    remove(DECODED_FILE);

    fileEncoded_ = false;
}


// ──────────────────────────────────────────────────────────────────────────
// openFile: prompt user until they provide a valid filename for “encode”
//           or “decode,” try both current directory and “tests/”.
// ──────────────────────────────────────────────────────────────────────────
ifstream Huffman::openFile(const string usage) const
{
    string filename;
    while (true) {
        cout << "Enter name of text file to " << usage << ": ";
        if (!getline(cin, filename)) {
            cin.clear();
            continue;
        }
        // try current directory
        ifstream in(filename);
        if (in) {
            cout << "Opened \"" << filename << "\" successfully.\n";
            waitForEnter();
            return in;
        }
        // try “tests/” subfolder
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


// ──────────────────────────────────────────────────────────────────────────
// outFile: write result into ENCODED_FILE, 50 bits per line. 
// ──────────────────────────────────────────────────────────────────────────
void Huffman::outFile(ifstream& in, const string codes[]) const
{
    char c;
    unsigned char uc;
    int bits_on_line = 0;
    const int max_bits_per_line = 50;

    ofstream out(ENCODED_FILE);
    if (!out) {
        cerr << "Error: could not open " << ENCODED_FILE << " for writing\n";
        in.close();
        return;
    }

    // rewind to start
    in.clear();
    in.seekg(0);

    while (in.get(c)) {
        uc = static_cast<unsigned char>(c);
        // only printable ASCII (32..126)
        if (uc < 32 || uc > 126) {
            continue;
        }
        string code = codes[uc - 32];
        for (char bit : code) {
            out.put(bit);
            bits_on_line++;
            if (bits_on_line >= max_bits_per_line) {
                out.put('\n');
                bits_on_line = 0;
            }
        }
    }

    cout << "Huffman codes saved to " << ENCODED_FILE << "\n";
    in.close();
    out.close();
    waitForEnter();
}


// ──────────────────────────────────────────────────────────────────────────
// countFrequencies: given an open input stream, fill freq_[0..94]
// ──────────────────────────────────────────────────────────────────────────
void Huffman::countFrequencies(ifstream& in)
{
    // zero it out first
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        freq_[i] = 0;
    }

    char c;
    while (in.get(c)) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (uc >= 32 && uc <= 126) {
            freq_[uc - 32]++;
        }
    }
}


// ──────────────────────────────────────────────────────────────────────────
// makeLinkedList: scan freq_[i], for each freq_[i] > 0, create one
//                 SingleNode(char(i+32), freq_[i]), then insertSorted
//                 into a LinkedList* in ascending order.
// ──────────────────────────────────────────────────────────────────────────
LinkedList* Huffman::makeLinkedList()
{
    LinkedList* head = nullptr;
    for (int i = 0; i < NUM_PRINTABLE; ++i) {
        if (freq_[i] > 0) {
            // create a leaf‐node
            SingleNode* leaf = new SingleNode(static_cast<char>(i + 32), freq_[i]);
            insertSorted(head, leaf);
        }
    }
    return head;
}

void Huffman::insertSorted(LinkedList*& head, SingleNode* nodeToInsert)
{
    LinkedList* newNode = new LinkedList(nodeToInsert);

    // empty list or smaller than head?
    if (!head || nodeToInsert->freq < head->characterNode->freq) {
        newNode->next = head;
        head = newNode;
        return;
    }

    LinkedList* cur = head;
    while (cur->next && cur->next->characterNode->freq <= nodeToInsert->freq) {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
}


// ──────────────────────────────────────────────────────────────────────────
// buildTree: while more than one node in treeHead_, pop off the first
//            two SingleNode*, merge them (new SingleNode(left,right)),
//            then insertSorted back into treeHead_. At end, the only
//            SingleNode* left is the root of full Huffman tree.
// ──────────────────────────────────────────────────────────────────────────
SingleNode* Huffman::buildTree()
{
    while (treeHead_ && treeHead_->next) {
        // pop left
        SingleNode* leftNode = treeHead_->characterNode;
        LinkedList* t1 = treeHead_;
        treeHead_ = treeHead_->next;
        delete t1;

        // pop right
        SingleNode* rightNode = treeHead_->characterNode;
        LinkedList* t2 = treeHead_;
        treeHead_ = treeHead_->next;
        delete t2;

        // merge into internal node, re‐insert
        SingleNode* parent = new SingleNode(leftNode, rightNode);
        insertSorted(treeHead_, parent);
    }
    // now the only node left is the root
    return (treeHead_ ? treeHead_->characterNode : nullptr);
}


// ──────────────────────────────────────────────────────────────────────────
// generateCodes: recursive walk of Huffman tree:
//   if leaf, store path in codes_[ch−32]; else recurse left with path+"0",
//   right with path+"1".
// ──────────────────────────────────────────────────────────────────────────
void Huffman::generateCodes(SingleNode* node, const string& path)
{
    if (!node) return;

    if (!node->leftChild && !node->rightChild) {
        // leaf: store its code
        unsigned char uc = static_cast<unsigned char>(node->ch);
        codes_[uc - 32] = path;
    }
    else {
        generateCodes(node->leftChild,  path + '0');
        generateCodes(node->rightChild, path + '1');
    }
}


// ──────────────────────────────────────────────────────────────────────────
// deleteTree: recursively free all nodes under ‘node’
// ──────────────────────────────────────────────────────────────────────────
void Huffman::deleteTree(SingleNode* node)
{
    if (!node) return;
    deleteTree(node->leftChild);
    deleteTree(node->rightChild);
    delete node;
}


// ──────────────────────────────────────────────────────────────────────────
// encodeFile (option 7): if fileEncoded_ is already true, clearState()
//                       first so we can re‐encode. Then:
//    1) prompt & open input file (openFile("encode")),
//    2) countFrequencies(in),
//    3) buildLinkedList() → treeHead_,
//    4) buildTree() → root_,
//    5) generateCodes(root_, ""), 
//    6) outFile(in, codes_),
//    7) set fileEncoded_ = true.
// ──────────────────────────────────────────────────────────────────────────
void Huffman::encodeFile()
{
    if (fileEncoded_) {
        clearState();
    }

    ifstream in = openFile("encode");
    if (!in) return;

    // count frequencies
    countFrequencies(in);

    // build sorted list (treeHead_)
    treeHead_ = makeLinkedList();

    // merge into one Huffman tree (root_)
    root_ = buildTree();

    // generate codes
    generateCodes(root_, "");

    // write to encoded file
    outFile(in, codes_);

    in.close();
    fileEncoded_ = true;
}


// ──────────────────────────────────────────────────────────────────────────
// decodeFile (option 8): prompt & open encoded file, traverse bits using
//                      root_ (already built during encodeFile), write
//                      decoded text to DECODED_FILE 50 chars/line,  
// ──────────────────────────────────────────────────────────────────────────
void Huffman::decodeFile() const
{
    if (!root_) {
        cerr << "Error: no Huffman tree to decode from. Please encode a file first.\n";
        waitForEnter();
        return;
    }

    ifstream in = openFile("decode");
    if (!in) return;

    ofstream out(DECODED_FILE);
    if (!out) {
        cerr << "Error: could not open " << DECODED_FILE << " for writing\n";
        in.close();
        return;
    }

    SingleNode* curr = root_;
    char bit;
    int chars_on_line = 0;
    const int max_chars_per_line = 50;

    while (in.get(bit)) {
        // skip anything but '0' or '1'
        if (bit != '0' && bit != '1') continue;

        if (bit == '0') {
            curr = curr->leftChild;
        }
        else {
            curr = curr->rightChild;
        }
        if (!curr) {
            cerr << "Error: invalid encoding encountered in file.\n";
            break;
        }

        // if leaf, output and reset
        if (!curr->leftChild && !curr->rightChild) {
            out.put(curr->ch);
            chars_on_line++;
            if (chars_on_line >= max_chars_per_line) {
                out.put('\n');
                chars_on_line = 0;
            }
            curr = root_;
        }
    }

    cout << "Decoded text saved to " << DECODED_FILE << "\n";
    in.close();
    out.close();
    waitForEnter();
}


// ──────────────────────────────────────────────────────────────────────────
// printTree (option 2): prompt for traversal order I/E/S, then call
//   inorder_display, preorder_display, or postorder_display. Matches
//   your printTree from printTree.cpp (:contentReference[oaicite:28]{index=28}).
// ──────────────────────────────────────────────────────────────────────────

void Huffman::printTree() const
{
    if (!root_) {
        cout << "Error: no tree to display. Please encode a file first.\n";
        waitForEnter();
        return;
    }

    string line;
    while (true) {
        cout << "\nSelect traversal - (I)norder, pr(E)order, po(S)torder (or Q to quit): ";
        if (!getline(cin, line)) {
            cout << "Input error; aborting tree print.\n";
            continue;
        }
        if (line.empty()) continue;
        if (line == "Q" || line == "q") break;

        char choice = toupper(line[0]);
        if (choice == 'I') {
            cout << "\n--- Inorder (Left-Root-Right) ---\n";
            inorder_display(root_, 0);
        }
        else if (choice == 'E') {
            cout << "\n--- Preorder (Root-Left-Right) ---\n";
            preorder_display(root_, 0);
        }
        else if (choice == 'S') {
            cout << "\n--- Postorder (Left-Right-Root) ---\n";
            postorder_display(root_, 0);
        }
        else {
            cout << "Invalid choice; please enter I, E, or S.\n";
        }
    }
}


// ──────────────────────────────────────────────────────────────────────────
// encodeWord (option 5): prompt for a word, then for each character
//   show its ASCII bits and Huffman code. Matches your encodeWord
//   logic in encode.cpp (:contentReference[oaicite:30]{index=30}).
// ──────────────────────────────────────────────────────────────────────────
void Huffman::encodeWord() const
{
    if (!fileEncoded_) {
        cout << "Error: Please encode a file first before encoding a word.\n";
        waitForEnter();
        return;
    }

    bool valid;
    string word;
    while (true) {
        cout << "\nEnter a word to encode : ";
        if (!getline(cin, word)) {
            cin.clear();
            continue;
        }
        valid = true;
        string result;
        string ascii;
        for (unsigned char c : word) {
            int idx = c - 32;
            if (idx < 0 || idx >= NUM_PRINTABLE || codes_[idx].empty()) {
                cout << "Error: no Huffman code for character '" << static_cast<char>(c)
                     << "'. Please try again.\n";
                valid = false;
                break;
            }
            // merge Huffman bits
            result += codes_[idx];
            // build ASCII‐binary
            for (int bit = 7; bit >= 0; --bit) {
                ascii += ((c >> bit) & 1) ? '1' : '0';
            }
        }
        if (valid) {
            cout << "Huffman encoding: " << result << "\n";
            cout << "ASCII Binary representation : " << ascii << "\n";
        }

		cout << "\n(Press Q to return to the menu, or any other key to look up again) : ";
		if (!getline(cin, word)) {
            // I/O error: retry
            cin.clear();
            continue;
        }
        if (word.empty()) {
            continue;
        }
		if (word[0] == 'Q' || word[0] == 'q')
			break;
    }
}


// ──────────────────────────────────────────────────────────────────────────
// decodeText (option 6): prompt user for a bit‐string, then traverse the
//   					  Huffman tree to decode.
// ──────────────────────────────────────────────────────────────────────────
void Huffman::decodeText() const
{
    if (!fileEncoded_) {
        cout << "Error: Please encode a file first before decoding text.\n";
        waitForEnter();
        return;
    }

    string bits;
    while (true) {
        cout << "\nEnter Huffman bit-string to decode (or Q to quit): ";
        if (!getline(cin, bits)) {
            cin.clear();
            continue;
        }
        if (bits == "Q" || bits == "q") {
            break;
        }

        string decoded;
        SingleNode* curr = root_;
        bool valid = true;
        for (char bit : bits) {
            if (bit == '0') {
                curr = curr->leftChild;
            }
            else if (bit == '1') {
                curr = curr->rightChild;
            }
            else {
                cout << "Error: invalid character '" << bit << "'. Only '0' or '1' allowed.\n";
                valid = false;
                break;
            }
            if (!curr) {
                cout << "Error: path led to null—this bit-string is not valid.\n";
                valid = false;
                break;
            }
            if (!curr->leftChild && !curr->rightChild) {
                decoded.push_back(curr->ch);
                curr = root_;
            }
        }
        if (valid) {
            cout << "Decoded text: " << decoded << "\n";
        }
    }
}


// ──────────────────────────────────────────────────────────────────────────
// Below: static helper functions for tree traversal.
// ──────────────────────────────────────────────────────────────────────────

// preorder (Root-Left-Right)
void Huffman::preorder_display(SingleNode* node, int level) const
{
    if (!node) return;

    for (int i = 0; i < level; ++i) cout << '-';
    if (!node->leftChild && !node->rightChild)
        cout << '[' << node->ch;
    else
        cout << "[*";
    cout << "(" << node->freq << ")]\n";

    preorder_display(node->leftChild,  level + 1);
    preorder_display(node->rightChild, level + 1);
}

// inorder (Left-Root-Right)
void Huffman::inorder_display(SingleNode* node, int level) const
{
    if (!node) return;

    inorder_display(node->leftChild, level + 1);
    for (int i = 0; i < level; ++i) cout << '-';
    if (!node->leftChild && !node->rightChild)
        cout << '[' << node->ch;
    else
        cout << "[*";
    cout << "(" << node->freq << ")]\n";
    inorder_display(node->rightChild, level + 1);
}

// postorder (Left-Right-Root)
void Huffman::postorder_display(SingleNode* node, int level) const
{
    if (!node) return;

    postorder_display(node->leftChild,  level + 1);
    postorder_display(node->rightChild, level + 1);
    for (int i = 0; i < level; ++i) cout << '-';
    if (!node->leftChild && !node->rightChild)
        cout << '[' << node->ch;
    else
        cout << "[*";
    cout << "(" << node->freq << ")]\n";
}
