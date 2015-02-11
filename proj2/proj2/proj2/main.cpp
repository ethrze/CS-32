#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
    
    Multiset ms; 					// default constructor
    assert(ms.empty()); 				// test empty
    assert(!ms.erase("thing")); 			// nothing to erase
    assert(ms.size() == 0); 			// test size
    assert(ms.insert("bob") == 1); 			// test insert
    ms.insert("bob");
    assert(ms.count("bob") == 2);			// test count
    assert(ms.uniqueSize() == 1);			// test uniqueSize
    assert(ms.size() == 2); 			// test size
    assert(ms.insert("alice") == 1); 		// test insert
    assert(ms.insert("eunice") == 1);
    ItemType value;
    int i = 0;
    ms.get(i, value); 				// test get
    assert(value == "eunice"); i++; ms.get(i, value);
    assert(value == "alice"); i++; ms.get(i, value);
    assert(value == "bob"); i++;
    assert(ms.get(i, value) == 0);
    assert(value == "bob"); 			// finished testing get
    assert(ms.eraseAll("bob") == 2); 		// test eraseAll
    assert(ms.erase("eunice") == 1); 		// test erase
    assert(ms.size() == 1);
    assert(ms.contains("eunice") == 0);		// test contains
    
    Multiset sm;
    sm.insert("horatio");
    ms.swap(sm);					// test swap
    assert(sm.contains("alice"));
    assert(ms.contains("horatio"));
    sm.insert("alice");
    sm.insert("alice");
    sm.insert("horatio");
    sm.insert("spalding");
    sm.insert("firenze");
    sm.insert("alan");
    
    ms.insert("alice");
    ms.insert("horatio");
    ms.insert("gendry");
    ms.insert("eru iluvatar");
    
    Multiset mnm;
    combine(sm, ms, mnm); 			// test combine
    assert(mnm.count("alice") == 4);
    
    subtract(sm, ms, mnm); 			// works with non-empty result
    assert(mnm.count("alice") == 2); 	// test subtract
    assert(!mnm.contains("eru iluvatar")); 	// doesn't include m2


}

////
////  main.cpp
////  proj2
////
//
//
//#include <iostream>
//#include "Multiset.h"
//
//int main(int argc, const char * argv[]) {
//    Multiset ms;
//    Multiset sm;
//
//    ms.insert(3);
//    ms.insert(3);
//    ms.insert(3);
//    ms.insert(5);
//    ms.insert(7);
//    ms.insert(7);
//
//    sm.insert(3);
//    sm.insert(14);
//    sm.insert(11);
//    sm.insert(7);
//
//    Multiset thing;
//    subtract(ms, sm, thing);
//
//    cout << thing.count(3) << endl;
//    cout << endl;
//
//    thing.dump();
////    ms.dump();
////    cout << endl;
////    sm.dump();
////    cout << endl;
////    cout << endl;
////    cout << "Size: " <<  ms.size() << endl;
////    cout << "UniqSize: " << ms.uniqueSize() << endl;
//
//
//
//}
