//
//  Multiset.cpp
//  homework1
//


#include "Multiset.h"
#include <iostream>


Multiset::Multiset() // Create an empty multiset.
: set(), setSize(0)
{
    // don't think I need anything in here...
}

//   ----------------------------------------
//  |                empty                   |
//   ----------------------------------------
bool Multiset::empty()  // Return true if the multiset is empty, otherwise false.
{
    if (setSize == 0)
{
        return true;
    }
    else {
        return false;
    }
}

//   ----------------------------------------
//  |                 size                   |
//   ----------------------------------------
int Multiset::size() const
// Return the number of items in the multiset.  For example, the size
// of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.
{
    return setSize;
}


//   ----------------------------------------
//  |              uniqueSize                |
//   ----------------------------------------
int Multiset::uniqueSize() const
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.
{
    int theCount = 0;
    ItemType uniqArr[setSize];                                  // changed from DEFAULT_ITEM_SIZE
    for (int i = 0; i < setSize; i++)                           // set[] loop
    {                               
        int track = 0;
        for (int j = 0; j < theCount; j++)
        {
            if (set[i] == uniqArr[j])
            {
                track++;                                        // counts matches to unique list
                break;
            }
        }
        if (track == 0)
        {
            uniqArr[theCount] = set[i];
            theCount++;                                         // if there aren't any matches, it's unique
        }
    }
    return theCount;
}


//   ----------------------------------------
//  |                insert                  |
//   ----------------------------------------
bool Multiset::insert(const ItemType& value)
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).
{
    if (setSize != DEFAULT_MAX_ITEMS)
    {
        set[setSize] = value;
        setSize++;
        return true;
    } else {
        return false;
    }
}


//   ----------------------------------------
//  |                 erase                  |
//   ----------------------------------------
int Multiset::erase(const ItemType& value)
// Remove one instance of value from the multiset if present.
// Return the number of instances removed, which will be 1 or 0.
{
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if (set[i] == value)
        {
            for (int j = i; j < DEFAULT_MAX_ITEMS; j++)
            {
                set[j] = (set[j+1]);
            }
            setSize--;
            return 1;
        }
    }
    return 0;
}


//   ----------------------------------------
//  |                eraseAll                |
//   ----------------------------------------
int Multiset::eraseAll(const ItemType& value)
// Remove all instances of value from the multiset if present.
// Return the number of instances removed.
{
    int numRem = 0;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if (set[i] == value)
        {
            for (int j = i; j < DEFAULT_MAX_ITEMS; j++)  // move everything left
            {
                set[j] = (set[j+1]);
            }
            numRem++;
        }
    }
    return numRem;
}


//   ----------------------------------------
//  |                contains                |
//   ----------------------------------------
bool Multiset::contains(const ItemType& value) const
// Return true if the value is in the multiset, otherwise false.
{
    for (int i = 0; i < setSize; i++)
    {
        if (set[i] == value)
            return true;
    }
    return false;
}


//   ----------------------------------------
//  |                 count                  |
//   ----------------------------------------
int Multiset::count(const ItemType& value) const
// Return the number of instances of value in the multiset.
{
    int inst = 0;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        if (set[i] == value)
            inst++;
    }
    return inst;
}


//   ----------------------------------------
//  |                  get                   |
//   ----------------------------------------
int Multiset::get(int i, ItemType& value) const
// If 0 <= i < uniqueSize(), copy into value an item in the
// multiset and return the number of instances of that item in
// the multiset.  Otherwise, leave value unchanged and return 0.
// (See below for details about this function.)
{
    int occurence = 0;
    // Create array of uniques
    if (i >= 0 && i < this->uniqueSize()) {
        int theCount = 0;
        ItemType uniqArr[DEFAULT_MAX_ITEMS];
        for (int k = 0; k < DEFAULT_MAX_ITEMS; k++)                 // set[] loop
        {
            int track = 0;
            for (int j = 0; j < theCount; j++)
            {
                if (set[k] == uniqArr[j])
                {
                    track++;    // counts matches to unique list
                    break;
                }
            }
            if (track == 0)
            {
                uniqArr[theCount] = set[k];
                theCount++;     // if there aren't any matches, it's unique
            }
        }
        
        // Count instances with the aid of that array
        for (int l = 0; l < DEFAULT_MAX_ITEMS; l++)
        {
            if (set[l] == uniqArr[i])
            {
                occurence++;
            }
        }
        value = uniqArr[i];
        return occurence;
        
    }
    return 0;
}


//   ----------------------------------------
//  |                  swap                  |
//   ----------------------------------------
void Multiset::swap(Multiset& other)
// Exchange the contents of this multiset with the other one.
{
    Multiset temp;      // the ol' reddit switcharoo
    temp = *this;
    *this = other;
    other = temp;
    
}


void Multiset::dump() const
{
    for (int i = 0; i < setSize; i++){
        std::cerr << set[i] << " ";
    }
    std::cerr << std::endl;
}