//
//  Coord.cpp
//  homework2
//

#include <string>
#include <stack>
#include <iostream>

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


// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    Coord end = Coord(er, ec);
    Coord start = Coord(sr, sc);

    stack<Coord> pile;
    
    pile.push(start);
    maze[sr][sc] = '+';
    
    while (!pile.empty()) {
        Coord current = pile.top();
//        cout << current.r() << ", " << current.c() << endl;
        pile.pop();
        
        int r = current.r();
        int c = current.c();
        
        // Maze Solved
        if (current.r() == end.r() && current.c() == end.c()) {
            return true;
        }
        // Check NORTH
        if (r-1 >= 0 && maze[r-1][c] == '.' && maze[r-1][c] != '+') {
            Coord north = Coord(r-1, c);
            pile.push(north);
            maze[r-1][c] = '+';
        }
        // Check EAST
        if (c+1 < nCols && maze[r][c+1] == '.' && maze[r][c+1] != '+') {
            Coord east = Coord(r, c+1);
            pile.push(east);
            maze[r][c+1] = '+';
        }
        // Check SOUTH
        if (r+1 < nRows && maze[r+1][c] == '.' && maze[r+1][c] != '+') {
            Coord south = Coord(r+1, c);
            pile.push(south);
            maze[r+1][c] = '+';
        }
        // Check WEST
        if (c-1 >= 0 && maze[r][c-1] == '.' && maze[r][c-1] != '+') {
            Coord west = Coord(r, c-1);
            pile.push(west);
            maze[r][c-1] = '+';
        }
    }
    return false;
}




// P S E U D O C O D E ! ! !

//Push the starting coordinate (sr,sc) onto the coordinate stack and
//update maze[sr][sc] to indicate that the algorithm has encountered
//it (i.e., set maze[sr][sc] to have a value other than '.').
//While the stack is not empty,
//{   Pop the top coordinate off the stack. This gives you the current
//    (r,c) location that your algorithm is exploring.
//    If the current (r,c) coordinate is equal to the ending coordinate,
//    then we've solved the maze so return true!

//    Check each place you can move from the current cell as follows:

//    If you can move NORTH and haven't encountered that cell yet,
//    then push the coordinate (r-1,c) onto the stack and update
//    maze[r-1][c] to indicate the algorithm has encountered it.

//    If you can move EAST and haven't encountered that cell yet,
//    then push the coordinate (r,c+1) onto the stack and update
//    maze[r][c+1] to indicate the algorithm has encountered it.

//    If you can move SOUTH and haven't encountered that cell yet,
//    then push the coordinate (r+1,c) onto the stack and update
//    maze[r+1][c] to indicate the algorithm has encountered it.

//    If you can move WEST and haven't encountered that cell yet,
//    then push the coordinate (r,c-1) onto the stack and update
//    maze[r][c-1] to indicate the algorithm has encountered it.
//}
//There was no solution, so return false