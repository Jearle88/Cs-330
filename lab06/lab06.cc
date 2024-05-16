#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Base class for filters
class Filter
{
  virtual char FilterLetter(char ch) { return ch; }

public:
  string Exec(string input);
};

string Filter::Exec(string input)
{
  stringstream res;
  for (int i = 0; i < input.size(); i++) {
    if (isalpha(input[i])) {
      res << FilterLetter(input[i]);
    } else {
      res << input[i];
    }
  }
  return res.str();
}

// Filter to convert each alphabetic character to uppercase
class ToUpper : public Filter
{
  char FilterLetter(char ch) override { return toupper(ch); }
};

// TODO (1): Define a ToLower class which inherits from Filter and makes each character lowercase
class ToLower : public Filter
{
  char FilterLetter(char ch) override { return tolower(ch); }
};

// TODO (2): Define an Encrypt filter which uses the shift_cypher() function to encode its input letters
class Encrypt : public Filter
{
private:
  int offset;

public:
  Encrypt(int offset) : offset(offset) {}
  char FilterLetter(char ch) override { return shift_cypher(ch, offset); }

private:
  char shift_cypher(char ch, int offset)
  {
    return (toupper(ch) - 'A' + offset) % 26 + 'A';
  }
};

// Function to allocate a particular filter and return a pointer to it
Filter *getFilter()
{
  // Modify this function to test different filters
  // return new ToUpper();
  // return new ToLower();
  return new Encrypt(13); // Encrypt with a shift of 13
}

// Main function
int main()
{
  string temp;
  Filter *theFilter = getFilter();

  while (getline(cin, temp)) {
    cout << theFilter->Exec(temp) << endl;
  }

  return 0;
}
