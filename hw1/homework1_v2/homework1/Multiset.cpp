//
//  Multiset.cpp
//  homework1
//


#include "Multiset.h"
#include <iostream>


Multiset::Multiset() // Create an empty multiset.
: set(), setSize(0), maxSize(DEFAULT_MAX_ITEMS)
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
    int tally;
    tally = 0;
    for (int i = 0; i < setSize; i++)
    {
        tally += set[i].occ;
    }
    return tally;
}


//   ----------------------------------------
//  |              uniqueSize                |
//   ----------------------------------------
int Multiset::uniqueSize() const
// Return the number of distinct items in the multiset.  For example,
// the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
// "turmeric" is 2.
{
    return setSize;
}


//   ----------------------------------------
//  |                insert                  |
//   ----------------------------------------
bool Multiset::insert(const ItemType& value)
// Insert value into the multiset.  Return true if the value was
// actually inserted.  Return false if the value was not inserted
// (perhaps because the multiset has a fixed capacity and is full).
{
    for (int i = 0; i < setSize; i++)
    {
        if (set[i].item == value)
        {
            set[i].occ++;
            return true;
        }
    }
    if (setSize != maxSize)
    {
        set[setSize].item = value;
        set[setSize].occ = 1;
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
    for (int i = 0; i < setSize; i++)
    {
        if (set[i].item == value)
        {
            for (int j = i; j < setSize; j++)
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
    for (int i = 0; i < setSize; i++)
    {
        if (set[i].item == value)
        {
            for (int j = i; j < setSize; j++)  // move everything left
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
        if (set[i].item == value)
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
    for (int i = 0; i < maxSize; i++)
    {
        if (set[i].item == value)
            return set[i].occ;
    }
    return 0;
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
    if (i >= 0 && i < this->uniqueSize())
    {
        value = set[i].item;
        return set[i].occ;
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
    for (int i = 0; i < maxSize; i++) {
        for (int j = 0; j < set[i].occ; j++) {
            std::cerr << set[i].item << " ";
        }
    }
    std::cerr << std::endl;
}