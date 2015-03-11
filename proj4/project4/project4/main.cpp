// We have not yet produced the test driver main routine for you.

#include "provided.h"
#include "HashTable.h"
#include <iostream>
using namespace std;

void argh() {
    HashTable<string, int> nameToAge(100, 200);
    nameToAge.set("Carey", 43);
    nameToAge.set("David", 97);
    nameToAge.set("Timothy", 43, true);
    nameToAge.set("Ivan", 28);
    nameToAge.set("Sally", 22);
    nameToAge.set("David", 55);
    nameToAge.touch("Carey");
    // let’s discard the two least recently written items
    for (int k = 0; k < 2; k++) {
        string discardedName;
        int discardedAge;
        if (nameToAge.discard(discardedName,discardedAge))
            cout << "Discarded " << discardedName << " who was " << discardedAge << " years old.\n";
        else
            cout << "There are no items to discard!\n";
    }
}

int main()
{
    //	cout << "Test driver not yet written." << endl;
    
//    argh();
    
    
    
    
    // string text;
    // if ( ! WebSteg::hideMessageInPage("http://cs.ucla.edu", "Hello there!", text))
    //	cout << "Error hiding!" << endl;
    // string msg;
    // if ( ! WebSteg::revealMessageInPage("http://cs.ucla.edu", msg))
    // 	cout << "Error revealing!" << endl;
}


