#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------
void removeSpaces(string& str) {
    // Loop through  string and erase any spaces
    for (unsigned int i = 0; i < str.length(); i++) {
    	if (str[i] == ' ')
	    str.erase(str.begin() + i);
    }
}

// Function to validate pages
bool is_valid_page(string page) {
    
    bool is_valid = true;
    
    // Check for  empty page
    if (page.length() == 0) {
	cout << "Invalid Running key: " << page << endl;
	is_valid = false;
	return is_valid;
    } 

    // Check to endusure only  lowercase letters or spaces
    for (unsigned int i = 0; i < page.length(); i++) {
    	char c = page[i];
	if (!(((c >= 'a') && (c <= 'z')) || (c == ' '))) {
	    cout << "Invalid Running key: " << page << endl;
	    is_valid = false;
	    return is_valid;
	}
    }

    return is_valid;
}

// -------------------------------------------------------
// Running Key Cipher implementation


struct Cipher::CipherCheshire {
    // Set cipher_alpha to be the in-order alphabet for encrypt/decrypt
    string cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
};


struct KCipher::ExtraCheshire {
    // Vector to store the whole book
    vector<string> book;
    
    // Default to first page
    unsigned int page = 0;
};


KCipher::KCipher() {
    //  vector for storage
    vector<string> book;

    // Initialize a page and fill it with all 'a's 
    string page;
    for (unsigned int i = 0; i < MAX_LENGTH; i++) {
    	page += 'a';
    }

    // Push  string to the vector
    book.push_back(page);

    // Create an instance of the ExtraCheshire struct
    grin = new ExtraCheshire;

    // Store that vector in the ExtraCheshire grin
    grin->book = book;
};


KCipher::KCipher(string page_one) {
    // Error check for valid page
    if (!is_valid_page(page_one)) {
    	exit(EXIT_FAILURE);
    }
	
    // Create an instance of the ExtraCheshire struct
    grin = new ExtraCheshire;
    
    // Store the first page in the ExtraCheshire grin
    grin->book.push_back(page_one);
};


void KCipher::add_key(string page) {
    // Error check for empty page
    if (!is_valid_page(page)) {
    	exit(EXIT_FAILURE);
    }
    
    // Push the desired page into the book
    grin->book.push_back(page);
};


void KCipher::set_id(unsigned int id) {
    // Error check to see if the id is greater than the number of pages in the book
    if (id > grin->book.size()) {
    	cout << "Warning: invalid id: " << id << endl;
	exit(EXIT_FAILURE);
    }

    // Set the id for the page we'll use to encrypt/decrypt
    grin->page = id;
};


string KCipher::encrypt(string raw) {
    // Initialize return variable
    string retStr;

    // Call the helper function to remove spaces from the page of the book we'll use to encrypt and decrypt
    removeSpaces(grin->book[grin->page]);

    string enc_page = grin->book[grin->page];
    
    // Initialize a vector to store the positions of the spaces in raw
    vector<int> space_pos;

    // Find the length of the raw string
    int len_raw_with_spaces = raw.length();

    // Fill the vector we just created
    for (int i = 0; i < len_raw_with_spaces; i++) {
    	if (raw[i] == ' ')
	    space_pos.push_back(i);
    }
   
    removeSpaces(raw);

    // Error check to make sure the running key is at least the same length as the text to encrypt
    if (enc_page.length() < raw.length()) {
    	cout << "Invalid Running key: " << enc_page << endl;
	exit(EXIT_FAILURE);
    }

    cout << "Encrypting...";

    
    int len_raw = raw.length();
    
  
    for (int i = 0; i < len_raw; i++) {
	// Convert the character we're looking forto lowercase
    	char lower_raw = LOWER_CASE(raw[i]);
	char lower_enc = LOWER_CASE(enc_page[i]);

	// Find the positions in the normal alphabet of the characters we just made lowercase
	int pos_raw = find_pos(smile->cipher_alpha, lower_raw);
	int pos_enc = find_pos(smile->cipher_alpha, lower_enc);

	// Rotate the alphabet however far is needed (how I handle tableau rows)
	rotate_string(smile->cipher_alpha, pos_raw);

	// Set the encrypted character to be the value of the result variable
	char result = smile->cipher_alpha[pos_enc];


	if (isupper(raw[i]))
	    result = UPPER_CASE(smile->cipher_alpha[pos_enc]);

	// Add the encrypted character to our return value
	retStr += result;

	// Reset the alphabet back to in-order
	rotate_string(smile->cipher_alpha, ALPHABET_SIZE - pos_raw);
    }

    // Get the length of the vector containing the position of spaces
    int vec_len = space_pos.size();

   
    for (int i = 0; i < vec_len; i++) {
	   retStr.insert(space_pos[i], " "); 
    }

    cout << "Done" << endl;

    return retStr;
}


string KCipher::decrypt(string enc) {
    cout << "Decrypting...";
    
   
    string retStr;

    // Determine what page of the book we'll be using to decrypt enc
    string enc_page = grin->book[grin->page];

    // Initialize a vector to store the positions of the spaces
    vector<int> space_pos;
    int len_enc_with_spaces = enc.length();
    
    // Populate the vector we just created
    for (int i = 0; i < len_enc_with_spaces; i++) {
    	if (enc[i] == ' ')
	    space_pos.push_back(i);
    }

    
    removeSpaces(enc);

    
    int len_enc = enc.length();
    
   
    for (int i = 0; i < len_enc; i++) {
        // Convert the char we're looking for in enc and enc_page to lowercase
        char lower_enc = LOWER_CASE(enc[i]);
        char lower_page = LOWER_CASE(enc_page[i]);

        // Find the position in the normal alphabet of the current char
        int pos_page = find_pos(smile->cipher_alpha, lower_page);

        // Rotate the alphabet 
        rotate_string(smile->cipher_alpha, pos_page);
        // Find position of the decoded character in the shifted alphabet
        int pos_dec = find_pos(smile->cipher_alpha, lower_enc);

        // Reset  alphabet 
        rotate_string(smile->cipher_alpha, ALPHABET_SIZE - pos_page);

        // Set decrypted character to be the value of the result variabe
        char result = smile->cipher_alpha[pos_dec];

        
        if (isupper(enc[i]))
	    result = UPPER_CASE(smile->cipher_alpha[pos_dec]);
        retStr += result;
    }

    int vect_len = space_pos.size(); 
   

    // Insert the spaces 
    for (int i = 0; i < vect_len; i++) {
	   retStr.insert(space_pos[i], " "); 
    }

    cout << "Done" << endl;

    return retStr;
}


// Destructor to delete the ExtraCheshire
KCipher::~KCipher() {
    delete grin;
};
