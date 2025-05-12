# Huffman Encoding Project

## Overview

This project implements a variation of the **Huffman Encoding Algorithm** to perform text compression.  
It provides a **menu-driven interface** that allows users to:
- Read an input text
- Calculate the frequency of each character
- Build a Huffman Tree
- Encode the input text into a compressed binary format
- Decode the binary back into the original text
- Save and load encoded/decoded files

---

## Menu Options

When the program runs, a **menu-driven interface** is presented to the user.  
The user can select from the following options:

### 1. Print Character Frequencies
- **What it does:**  
  Displays each printable character (ASCII 32–126) along with its frequency count.  
- **Logic:**  
  Read the text file and maintain a fixed array of length 95 (one slot for each printable code). For each character `c`, do  
- **Where implemented:**  
  Function in `src/huffman.cpp`, called from `src/main.cpp`.

---

### 2. Print Tree (Right-Root-Left Traversal)
- **What it does:**  
  Displays the Huffman tree structure using a right-root-left (reverse in-order) traversal.
- **Logic:**  
  Recursively traverse the tree: first right child, then root, then left child, printing nodes with their frequencies.
- **Where implemented:**  
  Tree traversal function in `src/huffman.cpp`, called from `src/main.cpp`.

---

### 3. Print Huffman Codes
- **What it does:**  
  Displays the Huffman binary codes for each character.
- **Logic:**  
  After building the Huffman tree, recursively assign codes: moving left adds `'0'`, moving right adds `'1'`, storing final codes in a map.
- **Where implemented:**  
  Huffman code assignment and printing in `src/huffman.cpp`.

---

### 4. Enter One Character and See its Huffman Code
- **What it does:**  
  Allows the user to input a single character and prints its Huffman code.
- **Logic:**  
  Search the Huffman code map for the entered character and display the corresponding binary string.
- **Where implemented:**  
  Look-up logic in `src/huffman.cpp`, handled in menu from `src/main.cpp`.

---

### 5. Enter a Word and Encode It
- **What it does:**  
  Prompts the user for a word, then return its binary representation and huffman code.
- **Logic:**  
  For each character in the input word, prints its ASCII binary representation (8 bits as a string of 0s and 1s) and find the Huffman code and concatenate the codes to form the encoded binary string.
- **Where implemented:**  
  Encoding logic in `src/huffman.cpp`.

---

### 6. Enter Encoded Text and Decode It
- **What it does:**  
  Allows the user to input a Huffman binary string and decodes it back to readable text.
- **Logic:**  
  Start from the root of the Huffman tree, follow `'0'` (left) or `'1'` (right) through the tree. When a leaf node is reached, record the character and reset back to root.
- **Where implemented:**  
  Decoding logic in `src/huffman.cpp`.

---

### 7. Enter File Name to Encode Text and Save It
- **What it does:**  
  Takes a file name, reads the text, encodes it, and saves the encoded output into a new file.
- **Logic:**  
  Read text from a given file inside the `data/` directory, encode the text using the Huffman codes, and write the binary string to a file in `output/`.
- **Where implemented:**  
  File I/O and encoding logic handled between `src/main.cpp` and `src/huffman.cpp`.

---

### 8. Enter Encoded File Name to Decode and Save It
- **What it does:**  
  Takes a file containing encoded Huffman binary and decodes it back to normal text, saving it to a new file.
- **Logic:**  
  Read encoded binary from the file in `output/`, decode it using the Huffman tree, and write the plain text back to a file.
- **Where implemented:**  
  File I/O and decoding logic between `src/main.cpp` and `src/huffman.cpp`.

---

### 9. Quit
- **What it does:**  
  Exits the program cleanly.
- **Logic:**  
  Breaks the menu loop and releases any dynamically allocated resources (if applicable).
- **Where implemented:**  
  Main loop in `src/main.cpp`.

---

## How the Menu Works

- The menu is implemented using a **`while (true)` loop**.
- Each user input is processed using a **`switch-case`** statement.
- Invalid inputs are handled gracefully by re-displaying the menu.
- The program keeps running until the user chooses **Quit**.

---

## Project Structure


```bash
HuffmanEncodingProject/
│
├── README.md          # Overview of the project (instructions below)
│
├── data/              # Folder for input text files and test data
│   ├── input.txt      # Provided sample input (like the paragraph given in Test Data)
│   └── other_test.txt # (Optional) Other text files for testing
│
├── output/            # Folder for output files
│   ├── encoded.bin    # Encoded binary files
│   └── decoded.txt    # Decoded text files
│
├── src/               # All source (.cpp) files
│   ├── main.cpp       # Main function and menu-driven logic
│   ├── huffman.cpp    # Implementation of Huffman tree, encoding/decoding
│   └── linked_list.cpp # Implementation for linked list (to store nodes)
│
├── include/           # All header (.h) files
│   ├── huffman.h      # Huffman tree class/struct declarations
│   └── linked_list.h  # Linked list class/struct declarations
│
├── docs/              # Documentation
│   ├── design_diagrams/ # UML and structural charts (optional)
│   │   ├── linked_list_uml.png
│   │   └── huffman_tree_chart.png
│   └── project_presentation.pptx # Your PowerPoint/Word/pdf presentation
│
├── tests/             # Folder for unit tests (optional but recommended)
│   └── test_huffman.cpp # Unit tests for Huffman functionality
│
└── Makefile           # (Optional) For building the project easily
```


### Folders and their Purpose

- `data/`: Input text files for testing encoding/decoding.
- `output/`: Contains the results of encoding (binary files) and decoding (text files).
- `src/`: C++ source code implementing the main logic of the project.
- `include/`: Header files containing class and function declarations.
- `docs/`: Documentation including diagrams, reports, and presentations.
- `tests/`: Optional unit tests to validate functionality.
- `Makefile`: Script for compiling the project easily.

---

## Logic

### Step 1: Build Character Frequency Table
- **Goal:** Count how often each character appears in the input text.
- **How:**  
  - Use a hash table (`std::unordered_map<char, int>`) to map each character to its frequency.
- **File:** `src/main.cpp` and helper function in `src/huffman.cpp`

---

### Step 2: Create Single Node Trees for Each Character
- **Goal:** Create a tree node for each character.
- **How:**  
  - Each node will store:
    - A character
    - Its frequency
    - Left and right child pointers (initialized to `nullptr`)
- **File:** Node struct/class is declared in `include/huffman.h` and implemented in `src/huffman.cpp`

---

### Step 3: Sort the Nodes into a Linked List (by Frequency)
- **Goal:** Maintain a sorted list of nodes in ascending order of frequency.
- **How:**  
  - Insert nodes into a linked list sorted by their frequency.
- **File:** Linked list structure declared in `include/linked_list.h` and implemented in `src/linked_list.cpp`

---

### Step 4: Build the Huffman Tree
- **Goal:** Merge nodes until a single tree remains.
- **How:**  
  - Repeatedly:
    - Take two nodes with the smallest frequency.
    - Merge them into a new node with combined frequency.
    - Insert the new node back into the linked list.
- **File:** Huffman tree building function implemented in `src/huffman.cpp`

---

### Step 5: Assign Huffman Codes
- **Goal:** Assign a unique binary string to each character.
- **How:**  
  - Traverse the Huffman tree:
    - Left branch adds `'0'`
    - Right branch adds `'1'`
  - Store character-code mappings in a map.
- **File:** Code assignment function in `src/huffman.cpp`

---

### Step 6: Encode the Text
- **Goal:** Replace each character in the text with its Huffman code.
- **How:**  
  - Use the character-to-code map to generate the encoded binary string.
- **File:** Encoding function implemented in `src/huffman.cpp`

---

### Step 7: Decode the Binary
- **Goal:** Reconstruct the original text from the encoded binary.
- **How:**  
  - Traverse the Huffman tree based on binary digits:
    - `0` goes left
    - `1` goes right
    - When reaching a leaf, retrieve the character.
- **File:** Decoding function implemented in `src/huffman.cpp`

---

### Step 8: Implement the Menu
- **Goal:** Provide user options to interact with the program.
- **How:**  
  - Use a `while` loop and a `switch` statement to process user commands:
    - Print frequency table
    - Print Huffman tree
    - Encode text
    - Decode text
    - Load/save files
    - Exit program
- **File:** Menu system implemented in `src/main.cpp`

---

## How to Build and Run

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/HuffmanEncodingProject.git
    cd HuffmanEncodingProject
    ```

2. Compile the project:

    ```bash
    g++ src/main.cpp src/huffman.cpp src/linked_list.cpp -Iinclude -o HuffmanApp
    ```

    Or use the Makefile if provided:

    ```bash
    make
    ```

3. Run the application:

    ```bash
    ./HuffmanApp
    ```

4. Follow the on-screen menu options to perform various operations.

---

## Requirements

- C++17 or later
- No external libraries (only standard C++ libraries)

---

## Documentation

The `/docs` directory includes:
- UML Diagrams for Linked List and Huffman Tree
- PowerPoint or Word report
- Sample inputs and outputs
- Team member roles and contributions

---

## Testing

The `/tests` directory contains optional unit tests to verify:
- Correct frequency counting
- Proper Huffman tree building
- Accurate encoding and decoding

---

## Final Beginner Tip

Think of the **Huffman Encoding Algorithm** in simple steps:
- **Count:** How many times each letter appears.
- **Sort:** Arrange the letters from least frequent to most frequent.
- **Merge:** Build a tree combining smallest elements first.
- **Code:** Assign 0/1 paths to each letter.
- **Compress:** Replace letters with codes for saving space.

---

