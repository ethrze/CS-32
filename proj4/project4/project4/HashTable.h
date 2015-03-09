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
        Node(int value)
        : m_key(string()), m_value(value)
        {}
    private:
        string m_key;
        int m_value;
        Node* m_next;
    };
    
    ValueType* m_bucketList;
    int m_capacity;
};

template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int numBuckets, int capacity)
{
    m_capacity = capacity;
    m_bucketList = new ValueType[numBuckets];
}
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable()
{
    // DESTRUCTOOOOR
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::isFull() const
{
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::set(const KeyType& key, const ValueType& value, bool permanent)
{
    // default for permanent is false
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::get(const KeyType& key, ValueType& value) const
{
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::touch(const KeyType& key)
{
    return false;
}
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::discard(KeyType& key, ValueType& value)
{
    return false;
}


// Don't touch include guards! //
#endif /* defined(__project4__HashTable__) */