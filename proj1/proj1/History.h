//
//  History.h
//  proj1
//


#pragma once

#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    
    
    private:
        // pointer to 2d arrays?
        int** m_grid;
        int nR;
        int nC;
};




