
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
using namespace std;

// “LinkedList” is one element of our singly‐linked list “tree”
class LinkedList {
public:
    SingleNode* characterNode;  // pointer to that one‐character node
    LinkedList* next;           // next element in the list

    // ── constructor: wrap an existing SingleNode* into a list element ──
    LinkedList(SingleNode* temp)
    {
        characterNode = temp;
        next = nullptr;
    }
};

#endif // LINKEDLIST_H
