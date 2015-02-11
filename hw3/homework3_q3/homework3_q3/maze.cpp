//
//  maze.cpp
//  homework3_q3
//
//  Created by Grace Phillips on 2/10/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

//#include "maze.h"
#include <string>
using namespace std;

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    Coord start = Coord(sr, sc);
    Coord end = Coord(er, ec);
    if (start.r() == end.r() && start.c() == end.c()) {
        return true;
    }
    
    maze[sr][sc] = '+';
    
    if (maze[sr+1][sc] != 'X' && maze[sr+1][sc] != '+' && sr+1 < nRows) { // I remember the maze going 0->nRows-1/nCols-1
        //pathExists(maze, nRows, nCols, sr+1, sc, er, ec);
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    
    if (maze[sr-1][sc] != 'X' && maze[sr-1][sc] != '+' && sr-1 >= 0) {
        //pathExists(maze, nRows, nCols, sr-1, sc, er, ec);
        if (pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    
    if (maze[sr][sc+1] != 'X' && maze[sr][sc+1] != '+' && sc+1 < nCols) {
        //pathExists(maze, nRows, nCols, sr, sc+1, er, ec);
        if (pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    
    if (maze[sr][sc-1] != 'X' && maze[sr][sc-1] != '+' && sc-1 >= 0) {
        //pathExists(maze, nRows, nCols, sr, sc-1, er, ec);
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    return false;
}




//If the start location is equal to the ending location, then we've
//solved the maze, so return true.
//Mark the start location as visted.
//For each of the four directions,
//If the location one step in that direction (from the start location) is unvisited,
//        then call pathExists starting from that location (and
//                                                  ending at the same ending location as in the
//                                                  current call).
//                          If that returned true,
//                              then return true.
//Return false.