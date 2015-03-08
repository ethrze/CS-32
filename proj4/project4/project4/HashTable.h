//
//  HashTable.h
//  project4
//

#include <string>
#include <iostream>
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
    ￼bool set(const KeyType& key, const ValueType& value, bool permanent = false);
    
    
private:
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
￼bool HashTable<KeyType, ValueType>::isFull() const
{
    return false;
}

template<typename KeyType, typename ValueType>
￼bool HashTable<KeyType, ValueType>::set(const KeyType& key, const ValueType& value, bool permanent = false)
{
    return false;
}



// Don't touch include guards! //
#endif /* defined(__project4__HashTable__) */
