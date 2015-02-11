//
//  History.cpp
//  proj1
//

#include <iostream>
using namespace std;

#include "History.h"
#include "globals.h"

// This provides the character that corresponds to the jump count. 
const char disp[27] = {'.', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                       'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

History::History(int nRows, int nCols)
{
    nR = nRows;
    nC = nCols;
    
    /* Setting up appropriately sized 2D array */
    m_grid = new int*[nRows];
    
    for(int i = 0; i < nRows; ++i)
        m_grid[i] = new int[nCols];
    
    
    /* Filling array with '0' to begin */
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            m_grid[i][j] = 0;
        }
    }
    
}


// parameters same as pit
// 1,1 is upper left-most position
bool History::record(int r, int c)
{
    if (r < MAXROWS && r > 0 && c < MAXCOLS && c > 0)
    {
        // do recording here
        if (m_grid[r-1][c-1] != 26) // check these for off by one badness
            m_grid[r-1][c-1] += 1;
        // all's well
        return true;
    } else {
        return false;
    }
}

void History::display() const
{
    // clear screen
    // display history
    // empty line after history grid
    // NO "press enter to continue."
    clearScreen();
    for (int r = 0; r < nR; r++)
    {
        for (int c = 0; c < nC; c++)
            cout << disp[m_grid[r][c]]; // pulls corresponding letter from display array
        cout << endl;
    }
    clearScreen();
    cout << endl;
    
}