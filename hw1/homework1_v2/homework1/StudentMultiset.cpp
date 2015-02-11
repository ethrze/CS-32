//
//  StudentMultiset.cpp
//  homework1
//


#include "StudentMultiset.h"
#include <iostream>
using namespace std;

// NO for, while (except in print), *, or []
// must not call Multiset::dump()

StudentMultiset::StudentMultiset()
// Create an empty student multiset.
: StuSet()
{}

bool StudentMultiset::add(ItemType id)
// Add a student id to the StudentMultiset.  Return true if and only
// if the id was actually added.
{
    return StuSet.Multiset::insert(id);
}

int StudentMultiset::size() const
// Return the number of items in the StudentMultiset.  If an id was
// added n times, it contributes n to the size.
{
    return StuSet.Multiset::size();
}

void StudentMultiset::print() const
// Print to cout every student id in the StudentMultiset one per line;
// print as many lines for each id as it occurs in the StudentMultiset.
{
    int uniqSize = StuSet.Multiset::uniqueSize();
    for (int i = 0; i < uniqSize; i++)                              // goes once for every uniq element
    {
        ItemType value;
        int numInst = StuSet.Multiset::get(i, value);
        StuSet.Multiset::get(i, value);
        for (int j = 0; j < numInst; j++)                           // repeats for num of instances of unique element
        {
            cout << value << endl;
        }
    }
}
//Private shit down here


// Some of your code goes here.