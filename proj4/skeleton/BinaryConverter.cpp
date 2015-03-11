//     _
//    u            .--~*teu.
//   88Nu.   u.   dF     988Nx
//  '88888.o888c d888b   `8888>
//   ^8888  8888 ?8888>  98888F
//    8888  8888  "**"  x88888~
//    8888  8888       d8888*`
//    8888  8888     z8**"`   :
//   .8888b.888P   :?.....  ..F
//    ^Y8888*""   <""888888888~
//      `Y"       8:  "888888*
//                ""    "**"`

#include "provided.h"
#include <string>
#include <vector>
using namespace std;

const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
	return "";  // This compiles, but may not be correct
}

bool BinaryConverter::decode(const string& bitString,
							 vector<unsigned short>& numbers)
{
	return false;  // This compiles, but may not be correct
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
