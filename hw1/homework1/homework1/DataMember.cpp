//
//  DataMember.cpp
//  homework1
//
//  Created by Grace Phillips on 1/15/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include "DataMember.h"


// Default constructor
DataMember::DataMember() {
    m_element;
    m_count = 0;
}

// Constructor given a thing
DataMember::DataMember(ItemType thing) {
    this->m_element = thing;
    this->DataMember::m_count = 0;
}

// return element
ItemType DataMember::element() const {
    return this->m_element;
}

// set element
void DataMember::setEl(ItemType ele) {
    this->m_element = ele;
}

// set counter
void DataMember::setCt(int cou) {
    this->m_count = cou;
}