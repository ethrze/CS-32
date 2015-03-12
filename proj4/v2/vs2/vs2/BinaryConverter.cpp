#include "provided.h"
#include <string>
#include <vector>
using namespace std;

const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

// go from unsigned shorts to tabs and spaces
// every 16 chars in the string is a number basically
string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
    string binString = "";
    for (auto q = numbers.begin(); q != numbers.end(); q++)
    {
        binString += convertNumberToBitString(*q);
    }
    string tabspace = "";
    for (int i = 0; i < binString.length(); i++)
    {
        if (binString[i] != '0' && binString[i] != '1')
            return "Your vector isn't properly formatted.";
        if (binString[i] == '0')
            tabspace += ' ';
        if (binString[i] == '1')
            tabspace += '\t';
    }
    return tabspace;  // This compiles, but may not be correct
}

// take block of 16 \t and " " and go to binary
// take the binary to unsigned shorts
// BINGO, BABE
bool BinaryConverter::decode(const string& bitString,
							 vector<unsigned short>& numbers)
{
    if (bitString.length() % BITS_PER_UNSIGNED_SHORT != 0) // if it doesn't break down into units of 16, bad
        return false;
    string binary = "";
    unsigned short num;
    for (unsigned short i = 0; i < bitString.length(); i++)
    {
        if (bitString[i] != ' ' && bitString[i] != '\t') // nothin' but tabs n' spaces
            return false;
        if (bitString[i] == ' ')
            binary += '0';
        if (bitString[i] == '\t')
            binary += '1';
        int innum = i+1;
        if (innum % 16 == 0)
        {
            convertBitStringToNumber(binary.substr(((innum/BITS_PER_UNSIGNED_SHORT)-1)*BITS_PER_UNSIGNED_SHORT, innum), num);
            numbers.push_back(num);
        }
    }
    return true;
}

string convertNumberToBitString(unsigned short number)
{
	string result(BITS_PER_UNSIGNED_SHORT, '0');
	for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
	{
		k--;
		if (number % 2 == 1)
			result[k] = '1';
	}
	return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
	if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
		return false;
	number = 0;
	for (size_t k = 0; k < bitString.size(); k++)
	{
		number *= 2;
		if (bitString[k] == '1')
			number++;
		else if (bitString[k] != '0')
			return false;
	}
	return true;
}
