//
//  HashTable.cpp
//  project4
//

#include <string>
#include <iostream>
using namespace std;
#include"HashTable.h"

// Write non-member hash functions
unsigned int computeHash(string s) {
    unsigned int hashValue;
    // Here you’ll write code that computes an unsigned int hash // value from a C++ string, and returns it. A HashTable whose
    // key type is string will call this function as part of determining a bucket number.
    for (int i = 0; i < s.size(); i++)
        hashValue += s[i] + i;
    
    return hashValue;
}