//
//  HashTable.h
//  project4
//

#include <string>
using namespace std;

#ifndef __project4__HashTable__
#define __project4__HashTable__
// Don't touch include guards! //

// probably need to define KeyType/ValueType better?

template<typename KeyType, typename ValueType>
class HashTable
{
public:
    HashTable(int numBuckets, int capacity);
    ~HashTable();
    
    bool isFull() const;
    bool set(const KeyType& key, const ValueType& value, bool permanent = false);
    bool get(const KeyType& key, ValueType& value) const;
    bool touch(const KeyType& key);
    bool discard(KeyType& key, ValueType& value);
    
    
private:
    // We prevent a HashTable from being copied or assigned by declaring the
    // copy constructor and assignment operator private and not implementing them.
    HashTable(const HashTable&);
    HashTable& operator=(const HashTable&);
    
    class Node {
    public:
        Node(KeyType key, ValueType val, bool permanent)
        : m_key(key), m_value(val), m_age(0), m_next(nullptr), m_permanent(permanent)
        {
            if (permanent)
                m_age = -1;
        }
    private:
        ValueType m_value;
        KeyType m_key;
        bool m_permanent;
        Node* m_next;
        int m_age;
    };
    
    class Bucket {
    public:
        Bucket(int goodHash)
        : m_hash(goodHash)
        { }
        void initContent(Node* first)
        { m_contents = first; }
        int getHash() { return m_hash; }
    private:
        int m_hash;
        int m_nWithin;
        Node* m_contents;
    };
    
    void growOld();
    
    
    Bucket* m_buckList;
//    Node* m_bucketRoot;
    int m_nBuckets;
    int m_curBuckets;
    int m_capacity;
    int m_fill;
};

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int numBuckets, int capacity)
{
    m_capacity = capacity;
    m_buckList = new Bucket[numBuckets];
    m_nBuckets = numBuckets;
}
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
    // DESTRUCTOOOOR
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::isFull() const
{
    if (m_fill == m_capacity)
        return true;
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::set(const KeyType& key, const ValueType& value, bool permanent)
{
    bool allIn = false;
    if (!permanent)
        growOld();
    // default for permanent is false
    for (int i = 0; i < this->m_nBuckets; i++)
    {
        if (computeHash(key) == m_buckList[i].m_hash) // if it already has a bucket
        {
            if (!isFull())
            {
                auto m = m_buckList[i].m_contents;
                bool update = false;
                while (m->m_next != nullptr)
                {
                    m = m->m_next;
                    if (m->m_key == key)
                        update = true;
                }
                if (!update)
                {
                    Node* nodey = new Node(key, value, permanent);
                    m->m_next = nodey;
                    m_buckList[i]->m_nWithin++; // bucket size tracker
                    m_fill++; // capacity counter
                    allIn = true;
                }
                if (update)
                {
                    auto t = m_buckList[i].m_contents;
                    while(t->m_key != key)
                        t = t->m_next;
                    t->value = value;
                    // successful update
                    allIn = true;
                }
            }
        }
    }
    if (!isFull() && allIn == false) // if it just doesn't have a bucket yet.
    {
        if (m_curBuckets != m_nBuckets)
        {
            m_buckList[m_curBuckets] = new Bucket(computeHash(key)); // we made a bucket!
            Node* shorthand = m_buckList[m_curBuckets]->m_contents;
            Node* nodey = new Node (key, value, permanent);
            shorthand = nodey;
            m_curBuckets++; // bucket size tracker
            m_fill++; // capacity tracker
            allIn = true;
        }
    }

    if (allIn == true)
        return true;
    return false;
    // alteration
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::get(const KeyType& key, ValueType& value) const
{
    unsigned int newHash = computeHash(key);
    for (int i = 0; i < m_curBuckets; i++)
    {
        if (newHash == m_buckList[i]->m_hash)
        {
            for (Node* q = m_buckList[i]->m_contents; q != nullptr; q = q->m_next)
            {
                if (q->m_key == key && q->m_value == value)
                    return true;
            }
        }
    }
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::touch(const KeyType& key)
{
    unsigned int newHash = computeHash(key);
    for (int i = 0; i < m_curBuckets; i++)
    {
        if (newHash == m_buckList[i]->m_hash)
        {
            for (Node* q = m_buckList[i]->m_contents; q != nullptr; q = q->m_next)
            {
                if (q->m_key == key)
                {
                    growOld();
                    q->m_age = 0;
                    return true;
                }
            }
        }
    }
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::discard(KeyType& key, ValueType& value)
{
    Node* oldest;
    Node* oldNext;
    Node* trailer;
    Node* maxTrailer;
    Node* index;
    int maxAge = 0;
    bool action = false;
    
    for (int i = 0; i < m_curBuckets; i++)
    {
        trailer = m_buckList[i]->m_contents;
        for (Node* q = m_buckList[i]->m_contents; q != nullptr; q = q->m_next)
        {
            if (!(m_buckList[i]->m_permanent))
            {
                if (m_buckList[i]->m_age > maxAge)
                {
                    maxAge = m_buckList;
                    maxTrailer = trailer;
                    oldNext = q->m_next;
                    oldest = m_buckList[i];
                    index = i;
                    action = true;
                }
            } // end permanent if
            trailer = q;
        }
    }
    if (action == true)
    {
        if (maxTrailer == m_buckList[index]->m_contents)
        {
            m_buckList[index]->m_contents = oldNext;
        }
        else
        {
            maxTrailer->m_next = oldNext;
        }
        delete oldest;
        return true;
    }
    return false;
}
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::growOld()
{
    // HOUSEKEEPING
    for (int i = 0; i < this->m_curBuckets; i++) // age all the buckets
    {
        if (m_buckList->m_contents != nullptr)
        {
            for (Node* q = m_buckList->m_contents; q != nullptr; q = q->m_next)
            {
                if (!(q->m_permanent))
                    q->age();
            }
        }
    }
}


// Don't touch include guards! //
#endif /* defined(__project4__HashTable__) */