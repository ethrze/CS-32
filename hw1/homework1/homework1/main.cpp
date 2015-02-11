//
//  main.cpp
//  homework1
//

#include "Multiset.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// To test a Multiset of unsigned long, leave the following line commented out;
// to test a Multiset of string, remove the "//".

// #define TEST_WITH_STRING

#ifdef TEST_WITH_STRING

const ItemType DUMMY_VALUE = "dill";
const ItemType VALUE1 = "tamarind";

#else // assume unsigned long

const ItemType DUMMY_VALUE = 999;
const ItemType VALUE1 = 42;

#endif

int main()
{
    Multiset ms;
    assert(ms.empty());
    ItemType x = DUMMY_VALUE;
    assert(ms.get(0, x) == 0   &&  x == DUMMY_VALUE); // x unchanged by get failure
    assert(!ms.contains(VALUE1));
    ms.insert(VALUE1);
    assert(ms.size() == 1);
    assert(ms.get(0, x) == 1  &&  x == VALUE1);
    cout << "Passed all tests" << endl;
}