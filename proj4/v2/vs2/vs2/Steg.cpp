#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

bool Steg::hide(const string& hostIn, const string& msg, string& hostOut) 
{
    if (hostIn == "")
        return false;
    
    vector<string> lines;
    int tail = hostIn.length()-1;
    for (int i = (hostIn.length()-1); i >= 0; i--)
    {
        char c = hostIn[i];
        if (c == '\n')
        {
            string line;
//            if (hostIn[tail] != '\n')
                line = hostIn.substr(i+1, (tail-(i)));
            tail = i-1;
            lines.push_back(line);
            continue;
        }
        else if (i == 0)
        {
            string line = hostIn.substr(0, tail);
            lines.push_back(line);
        }
    }
    // line scrubber
//    for (auto q = lines.begin(); q != lines.end(); q++)
//    {
//        for (int i = (*q).length(); (*q)[i] != '\n'; i--)
//        {
//            (*q) = (*q).substr(0, i-1);
//        }
//    }
    
    for (auto q = lines.begin(); q!= lines.end(); q++)
        cout << (*q) << ", ";
    
	return false;  // This compiles, but may not be correct
}

bool Steg::reveal(const string& hostIn, string& msg) 
{
	return false;  // This compiles, but may not be correct
}
