//
//  main.cpp
//  homework2_q3
//
//  Created by Grace Phillips on 2/1/15.
//  Copyright (c) 2015 UCLA. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <string>
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
