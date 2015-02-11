//
//  linear.cpp
//  homework3_q2
//

#include "linear.h"

//bool somePredicate(double x)
//{
//    if (x > 0)
//        return true;
//    else
//        return false;
//}

// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.
// IT'S DONE!
bool anyTrue(const double a[], int n)
{
    n--;
    if (somePredicate(a[n]))
    {
        return true;
    }
    if (n == 0)
    {
        return false;
    }
    anyTrue(a, n);
    if (anyTrue(a, n)) {
        return 1;
    } else {
        return 0;
    }
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if (n==-1)
        return 0; 
    if (somePredicate(a[n-1])) {
        return countTrue(a, n-1)+1;
    } else {
        return countTrue(a, n-1);
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if (somePredicate(a[0]))                // if it's zero, you want to return zero
            return 0;
    else if (n==0)                               // if you make it to n==0 w/out returning, there's no true element
        return -1;
    else 
        return firstTrue(a+1, n-1) + 1;     // move starting point in array forward, decrement # of elements, +1 to account
                                            // for index numbering.
    
    
//    int b = n;
//    if (somePredicate(a[b-n])) {
//        b--;
//        return n-1;
//    }
//    else {
//        return n;
//    }
//    
//    if (b == 0) {
//        return -1;
//    }
    
}

// Return the subscript of the smallest element in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    // Doesn't look at predicates?
    // I basically got this one when I figured out the last one. I DID NOT THINK TO ITERATE THE ARRAY AT FIRST.
    if (n==0)
        return -1; // if there aren't any elements, return -1
    if (n==1)
        return 0;
    if (a[0] <= a[n-1])
        return indexOfMin(a, n-1);
    return indexOfMin(a+1, n-1);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20

// LIKE Q4
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    
    if (n1 == 0 && n2 != 0) // if you're out of elements in a1 and not out of n2 elements, n1 doesn't include n2
        return false;  // This is not always correct.
    if (n1 == 0 && n2 == 0) // they've both zeroed out, you're done/you can back out a step
        return true;
    // recursive check
    if (a1[0] == a2[0])
        return includes(a1+1, n1-1, a2+1, n2-1); // changed all n's to -1
        // push arrays forward, decrement element counters (ignoring previously checked elements of both arrays after match)
    return includes(a1+1, n1-1, a2, n2); // if no match, just push comparison array
}

