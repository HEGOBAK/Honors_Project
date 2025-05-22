/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// ─── 1) “SingleNode” holds one character + its frequency (and child pointers) ───
class SingleNode {
public:
    char          ch;     // the character (only valid in a leaf)
    int           freq;   // how many times it appeared
    SingleNode*   left;   // left child in the Huffman tree
    SingleNode*   right;  // right child

    // leaf constructor
    SingleNode(char c, int f)
      : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // internal‐node constructor (merging two children)
    SingleNode(SingleNode* l, SingleNode* r)
      : ch('\0'), freq(l->freq + r->freq),
        left(l), right(r) {}
};

// ─── 2) “TreeNode” is one element of our singly-linked list (the “tree”) ───
class TreeNode {
public:
    SingleNode* singleNode;  // pointer to that one‐character node
    TreeNode*   next;        // next element in the list
    TreeNode(SingleNode* sn) : singleNode(sn), next(nullptr) {}
};

// ─── 3) Insert a new singleNode into our list-tree in ascending freq order ───
void insertSorted(TreeNode*& treeHead, SingleNode* sn) {
    TreeNode* nn = new TreeNode(sn);

    // empty list or sn is smallest → becomes new head
    if (!treeHead || sn->freq < treeHead->singleNode->freq) {
        nn->next    = treeHead;
        treeHead    = nn;
        return;
    }

    // otherwise, walk until the next node’s freq is bigger
    TreeNode* cur = treeHead;
    while (cur->next && cur->next->singleNode->freq <= sn->freq) {
        cur = cur->next;
    }

    // splice in
    nn->next   = cur->next;
    cur->next  = nn;
}

// ─── 4) Count printable‐ASCII freqs into freq[0..127] ───
void countFrequencies(const string& filename, int freq[]) {
    for (int i = 0; i < 128; ++i) freq[i] = 0;

    ifstream in(filename.c_str(), ios::binary);
    if (!in) {
        cerr << "Error: cannot open " << filename << "\n";
        exit(1);
    }

    char c;
    while (in.get(c)) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (uc < 128 && isprint(uc))
            ++freq[uc];
    }
    in.close();
}

// ─── 5) Build the initial list (“tree”) of single-character nodes ───
TreeNode* makeTree(int freq[]) {
    TreeNode* treeHead = nullptr;
    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            // create one‐node leaf and insert sorted
            insertSorted(treeHead, new SingleNode(char(i), freq[i]));
        }
    }
    return treeHead;
}

// ─── 6) Merge until only one singleNode remains (the full Huffman tree) ───
SingleNode* buildTree(TreeNode*& treeHead) {
    while (treeHead && treeHead->next) {
        // pop the first two singleNodes
        SingleNode* left  = treeHead->singleNode;
        TreeNode*   t1    = treeHead;
        treeHead = treeHead->next;
        delete t1;

        SingleNode* right = treeHead->singleNode;
        TreeNode*   t2    = treeHead;
        treeHead = treeHead->next;
        delete t2;

        // merge into a new parent singleNode and re-insert
        insertSorted(treeHead, new SingleNode(left, right));
    }
    // now treeHead->singleNode is the root of the Huffman tree
    return treeHead ? treeHead->singleNode : nullptr;
}

// ─── 7) Walk the final tree to generate bit-strings ───
void generateCodes(SingleNode* node,
                   const string& path,
                   string codes[]) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[static_cast<unsigned char>(node->ch)] = path;
    } else {
        generateCodes(node->left,  path + '0', codes);
        generateCodes(node->right, path + '1', codes);
    }
}

// ─── 8) Free memory ───
void deleteTree(SingleNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    // ask for file
    cout << "Enter name of text file to encode: ";
    string filename;
    getline(cin, filename);

    // count freqs
    int freq[128];
    countFrequencies(filename, freq);

    // build list (“tree”) of single nodes
    TreeNode* treeHead = makeTree(freq);

    // merge into one Huffman tree (root is a SingleNode)
    SingleNode* root = buildTree(treeHead);

    // generate codes
    string codes[128];
    generateCodes(root, "", codes);

    // print
    cout << "\nChar  ASCII  Freq   Code\n";
    cout << "----  -----  ----   ----\n";
    for (int i = 0; i < 128; ++i) {
        if (freq[i] > 0) {
            string disp = (i==' ') ? "␣" : string(1, char(i));
            cout << disp
                 << "      " << i
                 << "     "  << freq[i]
                 << "     "  << codes[i] << "\n";
        }
    }

    deleteTree(root);
    return 0;
}
