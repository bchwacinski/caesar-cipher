#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>

constexpr int correct_number_of_arguments = 3;
constexpr int numbers_size = 10;
constexpr int letters_size = 26;

// Returns true if str is made of digits only
bool
isDigits(const std::string_view str)
{
  auto str_begin = str.begin();
  // ignoring the first character if it's a plus or a minus
  if ((str[0] == '-') || (str[0] == '+')) {
    str_begin += 1;
  }
  return all_of(str_begin, str.end(), ::isdigit);
}

// Returns true if str is made of digits and letters only
// Ignores spaces
bool
isDigitsOrLetters(const std::string_view str)
{
  return all_of(
    str.begin(), str.end(), [](char c) { return isalnum(c) || isspace(c); });
}

// Verifies the input arguments
void
verifyArgs(int* argc, char** argv)
{
  // verifying the number of arguments
  if (*argc != (correct_number_of_arguments + 1)) {
    throw std::invalid_argument(
      "Invalid number of arguments.\nPlease provide " +
      std::to_string(correct_number_of_arguments) + " arguments!");
  }

  // verifying the encode/decode argument
  if ((argv[1][0] != 'd') && (argv[1][0] != 'e')) {
    throw std::invalid_argument(
      "Invalid argument: <[e]ncode/[d]ecode>.\nUsage: "
      "ccipher <[e]ncode/[d]ecode> <shift value> <text>");
  }

  // verifying the shift value
  if (!isDigits(argv[2])) {
    throw std::invalid_argument(
      "Invalid argument: <shift value>.\nPlease use only numbers.");
  }

  // verifying the text
  if (!isDigitsOrLetters(argv[3])) {
    throw std::invalid_argument(
      "Invalid argument: <text>.\nPlease use only numbers and letters.");
  }
}

// Shifts the input string by the shift value
// Numbers get shifted separately from letters
std::string
shiftString(const std::string_view str_to_shift, int shift_value)
{
  // preparing number- and letter-specific shift values with overhead removed
  int number_shift = shift_value % numbers_size;
  int letter_shift = shift_value % letters_size;

  // adjusting the shift value if its negative
  if (number_shift < 0) {
    number_shift += 10;
  }
  if (letter_shift < 0) {
    letter_shift += 26;
  }

  // creating output text and char buffers
  std::string output_str = "";
  unsigned int output_char_buffer = NULL;

  // shifting individual string chars
  for (const char c_to_shift : str_to_shift) {
    // shifting numerals
    if ((c_to_shift >= '0') && (c_to_shift <= '9')) {
      // saving the would-be numeric char value
      output_char_buffer = c_to_shift + number_shift;
      // shifting the char value back if it moves out of bounds
      if (output_char_buffer > '9') {
        output_char_buffer -= numbers_size;
      }

      // shifting large letters
    } else if ((c_to_shift >= 'A') && (c_to_shift <= 'Z')) {
      // saving the would-be numeric char value
      output_char_buffer = c_to_shift + letter_shift;
      // shifting the char value back if it moves out of bounds
      if (output_char_buffer > 'Z') {
        output_char_buffer -= letters_size;
      }

      // shifting small letters
    } else if ((c_to_shift >= 'a') && (c_to_shift <= 'z')) {
      // saving the would-be numeric char value
      output_char_buffer = c_to_shift + letter_shift;
      // shifting the char value back if it moves out of bounds
      if (output_char_buffer > 'z') {
        output_char_buffer -= letters_size;
      }

      // saving a space char if no alphanumeric characters were found
    } else {
      output_char_buffer = ' ';
    }

    // adding the current char to the output string
    output_str += output_char_buffer;
  }

  // returning the output string
  return output_str;
}

// Usage: ccipher <[e]ncode/[d]ecode> <shift value> <text>
int
main(int argc, char* argv[])
{
  // verifying execution arguments
  try {
    verifyArgs(&argc, argv);
    // outputing error message if invalid arguments found
  } catch (std::invalid_argument& err) {
    std::cerr << err.what() << std::endl;
    return -1;
  }

  // storing the input text
  std::string input_text = argv[3];

  // storing the shift value
  int shift_value = std::stoi(argv[2]);
  // negating the shift value if decoding mode was chosen
  if (argv[1][0] == 'd') {
    shift_value *= -1;
  }

  // creating the output text by encoding/decoding the input text
  std::string output_text = shiftString(input_text, shift_value);

  // returning the input and output values
  std::cout << "Input text:" << std::endl;
  std::cout << input_text << std::endl;
  std::cout << std::endl;
  std::cout << "Output text:" << std::endl;
  std::cout << output_text << std::endl;
  return 0;
}