/* **************************************** */
/*                                          */
/*     Project: CIS22C Huffman Encoding     */
/*     Authors: Jeriel & Chu                */
/*                                          */
/* **************************************** */

#include "../include/huffman.h"


// ─── Write all non-empty Huffman codes out to "encodedFile.txt" in the output directory ───
void outFile(ifstream& in, const string codes[]) {

	char c;
	string code;
	unsigned char uc;
	int bits_on_line = 0;
	const int max_bits_per_line = 50;
	
    // out will create the file if it doesn't exist
    ofstream out(ENCODED_FILE);
    if (!out) {
        cerr << "Error: could not open " << ENCODED_FILE << " for writing\n";
        in.close();
        return;
    }

	// rewind to beginning
    in.clear();             // clear EOF/fail bits
    in.seekg(0);  // go back to byte 0

	while (in.get(c)) {     // Going thru all char in the file

        // Getting the index for the hash table
        uc = static_cast<unsigned char>(c);

		// only printable ASCII 32..126
		if (uc < 32 || uc > 126) 
            continue;
	
		// Saving the code to the output file
		code = codes[uc - 32];

		// Switch to new line on output file
        for (char bit : code) {
            out.put(bit);
            if (++bits_on_line >= max_bits_per_line) {
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