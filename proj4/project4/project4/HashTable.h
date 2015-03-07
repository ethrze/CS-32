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
typedef string KeyType;
typedef int ValueType;

￼template<typename KeyType, typename ValueType>

￼class HashTable
{
public:
    ￼HashTable(unsigned int numBuckets, unsigned int capacity);
    ￼~HashTable();
    ￼bool isFull() const;
    ￼bool set(const KeyType& key, const ValueType& value, bool permanent = false);
    ￼bool get(const KeyType& key, ValueType& value) const;
    ￼bool touch(const KeyType& key);
    ￼bool discard(KeyType& key, ValueType& value);
    
private:
    class Node {
    public:
        ValueType getValue() { return m_value; }
        void age() { m_age++; }
    private:
        int m_value;
        int m_age;
        Node* m_root; // in this example, every bucket seems to just have one value. 
    }
    // We prevent a HashTable from being copied or assigned by declaring the
    // copy constructor and assignment operator private and not implementing them.
    ￼HashTable(const HashTable&);
    ￼HashTable& operator=(const HashTable&);
    Node* m_bucketList;
    int m_capacity;
}

// Public Member Functions
template<typename KeyType, typename ValueType>

￼typename HashTable<ItemType, ValueType>::HashTable(unsigned int numBuckets, unsigned int capacity) {
    m_bucketList = new Node[numBuckets];
    m_capacity = capacity;
}
template <typename KeyType, typename ValueType>
￼￼HashTable<ItemType, ValueType>::~HashTable() {
    
}
template <typename KeyType, typename ValueType>
￼bool ￼HashTable::isFull() const {
    
}
template <typename KeyType, typename ValueType>
￼bool ￼HashTable::set(const KeyType& key, const ValueType& value, bool permanent = false) {
    
}
template <typename KeyType, typename ValueType>
￼bool ￼HashTable::get(const KeyType& key, ValueType& value) const {
    
}
template <typename KeyType, typename ValueType>
￼bool ￼HashTable::touch(const KeyType& key) {
    
}
template <typename KeyType, typename ValueType>
￼bool ￼HashTable::discard(KeyType& key, ValueType& value) {
    
}
// Private Member Function(s)
template <typename KeyType, typename ValueType>
￼HashTable::￼HashTable(const HashTable&) {
    
}



// Don't touch include guards! //
#endif /* defined(__project4__HashTable__) */
