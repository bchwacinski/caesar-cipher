#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

using namespace std;

#define CORRECT_NUMBER_OF_ARGUMENTS 3
#define NUMBERS_SIZE 10;
#define LETTERS_SIZE 26;

// Returns true if str is made of digits only
bool isDigits(const string &str) {
	// Ignore the first character if its a plus or a minus
	if ((str[0] == '-') || (str[0] == '+')) {
		return all_of(str.begin() + 1, str.end(), ::isdigit);
	}
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

	string input_text = argv[3];
	int shift_value = stoi(argv[2]);
	if (argv[1][0] == 'd') {
		shift_value *= -1;
	}

	int number_shift = shift_value % NUMBERS_SIZE;
	int letter_shift = shift_value % LETTERS_SIZE;

	if (number_shift < 0) {
		number_shift += 10;
	}

	if (letter_shift < 0) {
		letter_shift += 26;
    }

	string output_text = "";
	unsigned int output_char_buffer = NULL;

	// Encoding/Decoding
	for (unsigned int i = 0; i < input_text.length(); i++) {
		// Encoding/Decoding numerals
		if ((input_text[i] >= '0') && (input_text[i] <= '9')) {
			// Save the would-be numeric char value
			output_char_buffer = input_text[i] + number_shift;
			// If the char moves out of bounds
			if (output_char_buffer > '9') {
				// Shift the char value back
				output_char_buffer -= NUMBERS_SIZE;
			}

		// Encoding/Decoding large letters
		} else if ((input_text[i] >= 'A') && (input_text[i] <= 'Z')) {
			// Save the would-be numeric char value
			output_char_buffer = input_text[i] + letter_shift;
			// If the char moves out of bounds
			if (output_char_buffer > 'Z') {
				// Shift the char value back
				output_char_buffer -= LETTERS_SIZE;
			}
			
		// Encoding/Decoding small letters
		} else if ((input_text[i] >= 'a') && (input_text[i] <= 'z')) {
			// Save the would-be numeric char value
			output_char_buffer = input_text[i] + letter_shift;
			// If the char moves out of bounds
			if (output_char_buffer > 'z') {
				// Shift the char value back
				output_char_buffer -= LETTERS_SIZE;
			}
		
		// If no alphanumeric characters were found, save a space character
		} else {
			output_char_buffer = ' ';
		}
		
		// Append the char value to the output string
		output_text += output_char_buffer;
	}

	//return the input and output values
	cout << "Input text:" << endl;
    cout << input_text << endl;
    cout << endl;
    cout << "Output text:" << endl;
    cout << output_text << endl;
    return 0;
}