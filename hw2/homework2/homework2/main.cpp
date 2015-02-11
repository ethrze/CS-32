//
//  main.cpp
//  homework2
//
//  Created by Grace Phillips on 1/29/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include <iostream>
#include <String>

using namespace std;

class Coord;
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

int main()
{
    string maze[10] = {
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