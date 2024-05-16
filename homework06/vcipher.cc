#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"



// -------------------------------------------------------
// Vigenere Cipher implementation
// -------------------------------------------------------

// Create a reference to the Cipher Cheshire
struct Cipher::CipherCheshire {
    // Set cipher_alpha 
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
};

// Create a reference to the KCipher ExtraCheshire
struct KCipher::ExtraCheshire {
    vector<string> book;
    unsigned int page = 0;
};

// Default constructor is the same as KCipher 
VCipher::VCipher() : KCipher() {
};

VCipher::VCipher(string key) {
    // Error check to make sure key is valid
    // NOTE: don't use is_valid_page function from KCipher since we can't have spaces here
    for (unsigned int i = 0; i < key.size(); i++) {
    	char c = key[i];
	if (!(c >= 'a') && (c <= 'z')) {
	    cout << "Error: not a valid Vigenere key word" << endl;
	    exit(EXIT_FAILURE);
	}
    }

    // Initialize a variable to store the page that will be  added to  ExtraCheshire grin
    string page;

    // fill  page by repeating the key until it hits MAX_LENGTH
    while (page.size() < MAX_LENGTH) {
    	page += key;
    }

    // Clear  book because KCipher default constructor was automatically called
    grin->book.clear();

    // Push the page into  book
    grin->book.push_back(page);
};

// Destructor handled in KCipher and Cipher
VCipher::~VCipher() {
};

