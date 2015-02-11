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



int main()
{
    Multiset ms;
    ms.insert(111);
    ms.insert(111);
    
    Multiset mss;
    mss.insert(100);
    mss.insert(100);
    
    ms.swap(mss);
    
    ms.dump();
    mss.dump();
    
    
}