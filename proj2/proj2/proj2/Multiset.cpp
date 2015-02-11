//
//  Multiset.cpp
//
#include "Multiset.h"
#include <cassert>
#include <iostream>
#include <cstdlib>



Multiset::Multiset()
:head(nullptr), uniqSize(0), maxSize(0)
{
}

Multiset::Multiset(const Multiset& other)  // copy constructor
: uniqSize(other.uniqSize), maxSize(other.maxSize)
{
    // this is rather silly but it puts everything in identically
    head = nullptr;
    // loop through to the end
    for (Node* p = other.head; p != nullptr; p = p->m_next)
    {
        // when you get to the end
        if (p->m_next == nullptr) {
            // loop from end to start and insert those items into the new MS
            for (Node* l = p; l != nullptr; l = l->m_prev)
            {
                for (int i = 0; i < l->m_occ; i++)
                {
                    this->insert(l->m_item);
                }
            }
        }
    }
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
    // if they're not already identical
    if (this != &rhs)
    {
        Multiset temp(rhs);
        swap(temp);
    }
    return *this;
}


Multiset::~Multiset()
{
    // loop through all the nodes, deleting them
    for (Node* p = head; p != nullptr; p = p->m_next) {
        delete p;
    }
}


bool Multiset::empty() const
{
    if (head == nullptr) // only empty if the head's not pointing anywhere
    {
        return true;
    }
    return false;
}

int Multiset::size() const
{
    int tally;
    tally = 0;
    for (Node* p = head; p != nullptr; p = p->m_next) {
        tally += p->m_occ;
    }
    return tally;
}

int Multiset::uniqueSize() const
{
    return uniqSize;
}

bool Multiset::insert(const ItemType& value)
{
    // Case 1: this value is not unique.
    for (Node* p = head; p != nullptr; p = p->m_next) {
        if (value == p->m_item) {
            p->m_occ++;
            return true;
        }
    }
    
    // Case 2: this value is unique.
    Node* lol = new Node(value);
    if (head != nullptr)
    {
        // set following item's prev
        head->m_prev = lol;
        // set lol's prev and next
        lol->m_next = head;
        lol->m_prev = nullptr;
        // set head's next to lol
        head = lol;
        
        // item set
        
        uniqSize++;
        delete lol;
        return true;
    } else {
        lol->m_next = nullptr;
        lol->m_prev = nullptr;
        head = lol;
        uniqSize++;
        delete lol;
        return true;
    }
    
}
int Multiset::erase(const ItemType& value)
{
    for (Node* p = head; p != nullptr; p = p->m_next) {
        if (value == p->m_item)
        {
            // there's more than one occurence
            if (p->m_occ > 1)
            {
                
                p->m_occ--;
                return 1;
            }
            else
            {
                eraseAll(value);
                return 1; 
            }
        }
    }
    return 0;
}
int Multiset::eraseAll(const ItemType& value)
{
    for (Node* p = head; p != nullptr; p = p->m_next) {
        if (value == p->m_item)
        {
            int occ = p->m_occ;
            Node* prev = p->m_prev;
            Node* next = p->m_next;
            
            // take care of next
            if (prev == nullptr && next == nullptr) // if it's the only node
            {
                head = nullptr;
            }
            
            if (prev == nullptr) // if it's the first node
            {
                head = next;
                next->m_prev = nullptr;
            }
            else
            {
                //cout << "here_nextElse" << endl;
                prev->m_next = next;
            }
            
            // take care of prev
            if (next == nullptr) // if it's the last node
            {
                prev->m_next = nullptr;
                
            }
            else {
                next->m_prev = prev;
            }
            // housekeeping
            uniqSize--;
            delete p;
            return occ;
        }
    }
    
    return 0;
}
bool Multiset::contains(const ItemType& value) const
{
    for (Node* p = head; p != nullptr; p = p->m_next)
    {
        if (p->m_item == value)
            return true;
    }
    return false;
}
int Multiset::count(const ItemType& value) const
{
    for (Node* p = head; p != nullptr; p = p->m_next)
    {
        if (p->m_item == value)
            return p->m_occ;
    }
    return 0;
}
int Multiset::get(int i, ItemType& value) const
{
    int k = 0;
    Node* p;
    if (i >= 0 && i < uniqSize) {
        for (p = head; p != nullptr; p = p->m_next)
        {
            if (k == i) {
                value = p->m_item;
                return p->m_occ;
            } else {
                k++;
            }
        }
    }
    return 0;
}
void Multiset::swap(Multiset& other)
{
    // swaps heads
    Node* tempData = head;
    head = other.head;
    other.head = tempData;
    
    // swap tails
    
    
    // Swap uniqueSize, size, and capacity.
    int temp = other.uniqSize;
    other.uniqSize = uniqSize;
    uniqSize = temp;
    
    temp = other.maxSize;
    other.maxSize = maxSize;
    maxSize = temp;
}




void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    
    Multiset* lol = new Multiset();
    for (int i = 0; i < ms1.uniqueSize(); i++)
    {
        ItemType value;
        ms1.get(i, value);
        for (int j = 0; j < ms1.count(value); j++)
            lol->insert(value);
    }
    for (int i = 0; i < ms2.uniqueSize(); i++)
    {
        ItemType val;
        ms2.get(i, val);
        for (int j = 0; j < ms2.count(val); j++)
            lol->insert(val);
    }
    result = *lol;
    delete lol;
    
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    Multiset* lol = new Multiset();
    for (int k = 0; k < ms1.uniqueSize(); k++)
    {
        ItemType rawr;
        ms1.get(k, rawr);
        
        if (ms2.contains(rawr))
        {
            if (ms1.count(rawr) > ms2.count(rawr))
            {
                for (int i = 0; i < (ms1.count(rawr) - ms2.count(rawr)); i++)
                    lol->insert(rawr);
            }
        }
        else {
            for (int j = 0; j < ms1.count(rawr); j++)
                lol->insert(rawr);
        }
    }
    result = *lol;
    delete lol;
}






