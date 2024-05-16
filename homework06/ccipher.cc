#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation
struct Cipher::CipherCheshire {
   string cipher_alpha; 
};
CCipher::CCipher() {
    // Start with the alphabet in order
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    
    // Rotate by 0 for the default
    rotate_string(cipher_alpha, 0);
    
    // Assign the cipher alphabet to cipher_alpha in the Cheshire
    smile->cipher_alpha = cipher_alpha;
}

CCipher::CCipher(int shift) {
    // Check to see if shift is positive
    if (shift < 0) {
    	cout << "Error: Caesar cipher is less than 0" << endl;
	exit(EXIT_FAILURE);
    }
    
    // Start with the alphabet in order
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    
    // Rotate by  shift
    rotate_string(cipher_alpha, shift);
    
    // Assign the cipher alphabet to cipher_alpha in the Cheshire
    smile->cipher_alpha = cipher_alpha;
}

// Destructor handled in cipher.cc
CCipher::~CCipher() {
}


// -------------------------------------------------------


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{
	 
    // Shift rot times
    while (rot) {
	// Move head of in_str to  end
    	in_str[ALPHABET_SIZE] = in_str[0];
	
	// Loop through and shift  one
	for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
	    in_str[i] = in_str[i + 1];
	}
	

	rot--;
    }
}

