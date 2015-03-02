//
//  Multiset.h
//  homework4
//

// Multiset.h

#ifndef MULTISET_INCLUDED
#define MULTISET_INCLUDED

#include <string>

typedef std::string ItemType;

class Multiset
{
public:
    Multiset();          // Create an empty multiset.
    bool empty() const;  // Return true if the multiset is empty, otherwise false.
    
    int size() const;
    // Return the number of items in the multiset.  For example, the size
    // of a multiset containing "cumin", "cumin", "cumin", "turmeric" is 4.
    
    int uniqueSize() const;
    // Return the number of distinct items in the multiset.  For example,
    // the uniqueSize of a multiset containing "cumin", "cumin", "cumin",
    // "turmeric" is 2.
    
    bool insert(const ItemType& value);
    // Insert value into the multiset.  Return true if the value was
    // actually inserted.  Return false if the value was not inserted
    // (perhaps because the multiset has a fixed capacity and is full).
    
    int erase(const ItemType& value);
    // Remove one instance of value from the multiset if present.
    // Return the number of instances removed, which will be 1 or 0.
    
    int eraseAll(const ItemType& value);
    // Remove all instances of value from the multiset if present.
    // Return the number of instances removed.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the multiset, otherwise false.
    
    int count(const ItemType& value) const;
    // Return the number of instances of value in the multiset.
    
    int get(int i, ItemType& value) const;
    // If 0 <= i < uniqueSize(), copy into value an item in the multiset
    // and return the number of instances of that item in the multiset.
    // Otherwise, leave value unchanged and return 0.
    
    void swap(Multiset& other);
    // Exchange the contents of this multiset with the other one.
    
    // Housekeeping functions
    ~Multiset();
    Multiset(const Multiset& other);
    Multiset& operator=(const Multiset& rhs);
    
private:
    // Representation:
    //   a circular doubly-linked list with a dummy node.
    //   m_head points to the dummy node.
    //   m_head->m_prev->m_next == m_head and m_head->m_next->m_prev == m_head
    //   m_uniqueSize == 0 and m_size == 0  if and only if
    //                           m_head->m_next == m_head->m_prev == m_head
    //   In addition to the dummy node, the list has m_uniqueSize nodes.
    //   Nodes are in no particular order.
    
    struct Node
    {
        ItemType m_value;
        int      m_count;
        Node*    m_next;
        Node*    m_prev;
    };
    
    Node* m_head;
    int   m_uniqueSize;
    int   m_size;
    
    Node* find(const ItemType& value) const;
    // Return pointer to Node whose m_value == value if there is one,
    // else m_head
    
    int doErase(const ItemType& value, bool all);
    // Remove one or all instances of value from the multiset if present,
    // depending on the second parameter.  Return the number of instances
    // removed.
};

// Declarations of non-member functions

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);
// If a value occurs n1 times in ms1 and n2 times in ms2, then
// it will occur n1+n2 times in result upon return from this function.

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);
// If a value occurs n1 times in ms1 and n2 times in ms2, then
// it will occur n1-n2 times in result upon return from this function
// if n1 >= n2.  If n1 <= n2, it will not occur in result.

// Inline implementations

inline
int Multiset::size() const
{
    return m_size;
}

inline
int Multiset::uniqueSize() const
{
    return m_uniqueSize;
}

inline
bool Multiset::empty() const
{
    return size() == 0;
}

inline
int Multiset::erase(const ItemType& value)
{
    return doErase(value, false);
}

inline
int Multiset::eraseAll(const ItemType& value)
{
    return doErase(value, true);
}

inline
bool Multiset::contains(const ItemType& value) const
{
    return find(value) != m_head;
}

#endif // MULTISET_INCLUDED


