//
//  main.cpp
//  homework3_q3
//

#include <iostream>
#include <string>
using namespace std;
#include "maze.h"

int main()
{
    string maze[10] = {
//        "..........",
//        "..........",
//        "..........",
//        "..........",
//        "..........",
//        "..........",
//        "..........",
//        "..........",
//        "..........",
//        ".........."
        
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}