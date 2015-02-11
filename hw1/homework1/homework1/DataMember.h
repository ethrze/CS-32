//
//  DataMember.h
//  homework1
//


#ifndef __homework1__DataMember__
#define __homework1__DataMember__

#include <iostream>
#include <string>

typedef unsigned long ItemType;

struct DataMember{
    ItemType m_element;
    int m_count;
    
    DataMember();
    DataMember(ItemType thing);
    ItemType element() const;
    void setEl(ItemType ele);
    void setCt(int cou);
    
};



#endif /* defined(__homework1__DataMember__) */
