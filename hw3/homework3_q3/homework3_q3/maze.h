//
//  maze.h
//  homework3_q3
//
//  Created by Grace Phillips on 2/10/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include <string>
using namespace std;

#ifndef __homework3_q3__maze__
#define __homework3_q3__maze__

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);






#endif /* defined(__homework3_q3__maze__) */
