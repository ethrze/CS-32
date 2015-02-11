//
//  Multiset.h
//

#ifndef __proj2__Multiset__
#define __proj2__Multiset__

#include <iostream>
#include <cstring>

using namespace std;

typedef string ItemType;

struct Node
{
    ItemType m_item;
    int m_occ;
    Node* m_next;
    Node* m_prev;
    Node(ItemType item)
    : m_next(), m_prev(), m_occ(1)
    {
        m_item = item;
    }
};


class Multiset
{
public:
    //Constructors
    Multiset();
    
    //Copy constructor
    Multiset(const Multiset& other);
    
    //Assignment operator
    Multiset& operator=(const Multiset& rhs);
    
    //Destructor
    ~Multiset();
    
    //Multiset utilities
    bool empty() const;
    int size() const;
    int uniqueSize() const;
    bool insert(const ItemType& value);
    int erase(const ItemType& value);
    int eraseAll(const ItemType& value);
    bool contains(const ItemType& value) const;
    int count(const ItemType& value) const;
    int get(int i, ItemType& value) const;
    void swap(Multiset& other);
    
private:
    Node* head;
    int uniqSize;
    int maxSize;
};

//Added linked list utilites
void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);



#endif /* defined(__proj2__Multiset__) */
