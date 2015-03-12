// We have not yet produced the test driver main routine for you.

#include "provided.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "Test driver not yet written." << endl;
    vector<unsigned short> numbers;
    if (!BinaryConverter::decode("               \t             \t \t                ", numbers))
        cout << "Bad format dude" << endl;
    else {
        for (vector<unsigned short>::iterator q = numbers.begin(); q != numbers.end(); q++)
            cout << *q;
        cout << endl;
    }
    string fal = BinaryConverter::encode(numbers);
    for (int i = 0; i < fal.length(); i++)
    {
        if (fal[i] == ' ')
            cout << '_' ;
        else if (fal[i] == '\t')
            cout << '-';

    }
    cout << endl;
	// string text;
	// if ( ! WebSteg::hideMessageInPage("http://cs.ucla.edu", "Hello there!", text))
	//	cout << "Error hiding!" << endl;
	// string msg;
	// if ( ! WebSteg::revealMessageInPage("http://cs.ucla.edu", msg))
	// 	cout << "Error revealing!" << endl;
}
