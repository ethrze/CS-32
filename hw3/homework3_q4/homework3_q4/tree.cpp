//
//  tree.cpp
//  homework3_q4
//

//#include <iostream>
//#include <string>
////#include "tree.h"
//using namespace std;

// NO WHILE, FOR, OR GOTO. Not that I even really know how to use 'goto'.
// Recursion seems to result in over-commenting for me. My apologies. 


// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//	10 50 40 20 50 40 30
// then for this value of a2     the function must return
//	10 20 40                            1
//	10 40 30                            2
//	20 10 40                            0
//	50 40 30                            3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    // because of recursion, returned things get added to the count.
    // array a1 of n1 elements
    // smaller array a2 of n2 elements
    // how many ways does a2 appear in sequence in a1
    
    
    if (n1 < 0)         // You've made it all the way through a1.
        return 0;
    if (n2 == 0)        // You've made it to the last element of a2, the sequence is included, +1;
        return 1;
    // IT WOULD BE REALLY NICE TO HAVE LOOPS ABOUT NOW.
    if (a1[0] == a2[0]) { // just look at the first part of the array!
        int count =  countIncludes(a1, n1, a2+1, n2-1); // move along in the sequence array
        count += countIncludes(a1+1, n1-1, a2, n2);     // move along in the comparison array?
        
        return count; // see what gets returned in the end. 1 for full sequence, zero for not.
    }
    // (if the elements we're examining aren't equal)
    return countIncludes(a1+1, n1-1, a2, n2); // they don't need to be consecutive! move along in the comparison array
    
    // SHOULD BE DONE
//    return -999;  // This is incorrect.
}






// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > separator come before all the other elements,
// and all the elements whose value is < separator come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= separator, or n if there is no such element, and firstLess is
// set to the index of the first element that is < separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > separator
//   * for firstNotGreater <= i < firstLess, a[i] == separator
//   * for firstLess <= i < n, a[i] < separator
// All the elements > separator end up in no particular order.
// All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
              int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > separator
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < separator
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    // this is like Smallberg's class example? ish?
    
    if (n >= 2)
    {
        int mid = n/2;
        // these just kind of needed to be initialized to something
        int firstNotGreater = n;    //
        int firstLess = n;          //
        
        // first division //
        separate(a, n, a[mid-1], firstNotGreater, firstLess); // changed to -1
        
        if (n != firstLess) // we want to keep dividing until we should order
        {
            order(a, firstLess);
//            order(a, firstNotGreater); // CLOSE?
//            separate(a, n, a[mid-1], firstNotGreater, firstLess); // changed to -1
        }
        // otherwise, more order!
//        order(a, firstNotGreater);
        order((a+firstLess), (n-firstLess)); // offset using previous orders
//        order(a, firstNotGreater); // changed from n to firstNotGreater
        
    }
    // SHOULD BE DONE.
//    return;  // This is not always correct.
}


//int main() {
//    
//    double a1[8] = {10, 50, 40, 20, 2, 40, 30, 80 };
//    int n1 = 8;
////    double a2[3] = {50, 40, 30 };
////    int n2 = 3;
//    
//    // count includes
////    cout << countIncludes(a1, n1, a2, n2) << endl;
//    order(a1, n1);
//    for (int i = 0; i < n1; i++)
//        cout << a1[i] << " ";
//    cout << endl;
//}