#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

/* check cipher alphabet for validity
 */
bool is_valid_alpha(string alpha);


// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
    // TODO: Implement this default constructor 
      // Create the struct appropriately
    smile = new CipherCheshire;
    smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
}

    


/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
    // TODO: Implement this constructor
     // Ifvalid cipher_alpha, create the struct appropriately
    if (is_valid_alpha(cipher_alpha)) {
    	smile = new CipherCheshire;
    	smile->cipher_alpha = cipher_alpha;
    }
    // else display an error
    else {
	cout << "Invalid cipher alphabet/key: " << cipher_alpha << endl;
    	exit(EXIT_FAILURE);
    }
    
}

/* Destructor
 */ 
Cipher::~Cipher()
{
    // TODO: Implement this constructor
    delete smile;
}

/* This member function encrypts the input text 
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;
    // TODO: Finish this function
      int len = raw.size();

    
    string real_alpha = "abcdefghijklmnopqrstuvwxyz";

      /* Loop through the input text, find the position of each char in
    the actual alphabet, use the corresponding position in the cipher
    alphabet to encrypt */
    for (int i = 0; i < len; i++) {
	// If the character is a space, just add a space to the encryption
	if (raw[i] == ' ')
	    retStr += ' ';

	else {
	    // Convert the character we're looking for to lowercase
	    char lower = LOWER_CASE(raw[i]);

	    // Find the position of the char in the actual alphabet
    	    int pos = find_pos(real_alpha, lower);

	    // Find the corresponding char in cipher_alpha
	    char result = smile->cipher_alpha[pos];

	    // If it was uppercase, encrypt it as uppercase
	    if (isupper(raw[i]))
	        result = UPPER_CASE(smile->cipher_alpha[pos]);
	    
	    // Add the character to our return variable
	    retStr += result;
    	}
    }
   
    cout << "Done" << endl;

    return retStr;
}


/* This member function decrypts the input text 
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrypting...";
    // TODO: Finish this function
    // Find the length of the ecrypted text
    int len = enc.length();

    // Initialize a variable to store the in-order alphabet
    string real_alpha = "abcdefghijklmnopqrstuvwxyz";
    
    /* Loop through the enencrypted text, find the position of each char in
    the cipher alphabet, use the corresponding position in the real
    alphabet to decrypt */
    for (int i = 0; i <enc.size() ; i++) // If the character is a space, just ad
    {
	    int pos=-2;
	    bool upper=false;
	    if( enc[i]==' '){
		    pos=-1;
		    
	    }
	    else if(enc[i]=='a'){
		    pos= find_pos(smile-> cipher_alpha,enc[i]);
	    }
	    else {
		    pos=find_pos(smile->cipher_alpha,LOWER_CASE(enc[i]));
				    }
	    if( pos == -1){
		retStr=' ';
		}
		else if (upper){
			    retStr+= UPPER_CASE(pos+'a');
		    }
		else{
			retStr+=(pos+'a');
		
		    }
    cout << "Done" << endl;

    return retStr;
    }
}




// -------------------------------------------------------


//  Helper functions 
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int find_pos(string alpha, char c)
{
    unsigned int pos = 0;

    // TODO: You will likely need this function. Finish it.
   

    // Loop through the entire cipher_alpha if necessary to find c's position
    for (unsigned int i = 0; i < ALPHABET_SIZE; i++) {
    	if (c == alpha[i]) {
	    pos = i;
	    break;
	}
    }

    return pos;

    
}

/* Make sure the cipher alphabet is valid - 
   a) it must contain every letter in the alphabet 
   b) it must contain only one of each letter 
   c) it must be all lower case letters 
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if(alpha.size() != ALPHABET_SIZE) {
        is_valid = false; 
    } else {
        unsigned int letter_exists[ALPHABET_SIZE];
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            letter_exists[i] = 0;
        }
        for(unsigned int i = 0; i < alpha.size(); i++) {
            char c = alpha[i];
            if(!((c >= 'a') && (c <= 'z'))) {
                is_valid = false;
            } else {
                letter_exists[(c - 'a')]++;
            }
        }
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            if(letter_exists[i] != 1) {
                is_valid = false;
            }
        }
    }

    return is_valid;
}
