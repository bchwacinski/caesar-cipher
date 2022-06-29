#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

using namespace std;

#define CORRECT_NUMBER_OF_ARGUMENTS 3

const char alnum_chars[62] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

const uint alnum_size = sizeof(alnum_chars)/sizeof(*alnum_chars);

// Returns true if str is made of digits only
bool isDigits(const string &str) {
	return all_of(str.begin(), str.end(), ::isdigit);
}

// Returns true if str is made of digits and letters only
// Ignores spaces
bool isDigitsOrLetters(const string &str) {
	return all_of(str.begin(), str.end(), [](char c) {
		return isalnum(c) || isspace(c);
	});
}

// Verifies the input arguments
void verifyArgs(int *argc, char **argv) {
	// Verify the number of arguments
    if (*argc != (CORRECT_NUMBER_OF_ARGUMENTS + 1)) {
        throw invalid_argument("Invalid number of arguments.\nPlease provide " + to_string(CORRECT_NUMBER_OF_ARGUMENTS) + " arguments!");
    }

	// Verify the encode/decode argument
	if ((argv[1][0] != 'd') && (argv[1][0] != 'e')){
		throw invalid_argument("Invalid argument: <[e]ncode/[d]ecode>.\nUsage: ccipher <[e]ncode/[d]ecode> <shift value> <text>");
	}

	// Verify the shift value
	if (!isDigits(argv[2])){
		throw invalid_argument("Invalid argument: <shift value>.\nPlease use only numbers.");
	}

	// Verify the text
	if (!isDigitsOrLetters(argv[3])){
		throw invalid_argument("Invalid argument: <text>.\nPlease use only numbers and letters.");
	}
}

// Usage: ccipher <[e]ncode/[d]ecode> <shift value> <text>
int main(int argc, char *argv[]) {
	// verifying execution arguments
    try {
        verifyArgs (&argc, argv);
    }
    catch(invalid_argument& err) {
        cerr << err.what() << endl;
        return -1;
    }

	string text = argv[3];
	int number_shift = stoi(argv[2]) % 10;
	int letter_shift = stoi(argv[2]) % 26;

	if (number_shift < 0) {
		number_shift += 10;
	}

	if (letter_shift < 0) {
		letter_shift += 26;
    }

	// Encoding/Decoding
	for (uint i = 0; i < text.length(); i++) {
	// translation
		if ((text[i] >= '0') && (text[i] <= '9')) {

		}

		if ((text[i] >= 'A') && (text[i] <= 'Z')) {
			
		}

		if ((text[i] >= 'a') && (text[i] <= 'z')) {
			
		}

	 	text[i] = 97 + (text[i] + shift - 97) % alnum_size;
	}

	// //returning the translation
    cout << endl << "Well done!" << endl;
    return 0;
}