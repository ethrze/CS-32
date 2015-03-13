#include "provided.h"
#include <string>
#include <stack>
#include <iostream>
using namespace std;

bool Steg::hide(const string& hostIn, const string& msg, string& hostOut) 
{
    if (hostIn == "")
        return false;
    
    vector<string> lines;
    int lineCount;
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
            lineCount++;
            continue;
        }
        else if (i == 0)
        {
            string line = hostIn.substr(0, tail);
            lines.push_back(line);
            lineCount++;
        }
    }
    // line scrubber
    vector<string> scrubbedLines;
    for (auto q = (lines.end()-1); q != lines.begin()-1; q--)
    {
        
        string atHand = (*q);
        string defGood = atHand;
        for (int i = (((*q).length())-1); i >= 0; i--)
        {
            if ((*q)[i] == '\t' || (*q)[i] == ' ')
                defGood = (*q).substr(0, i);
            else if ((*q)[i] != ' ' && (*q)[i] != '\t')
                break;
        }
        scrubbedLines.push_back(defGood);
    }
    // Processing secret message!
    vector<unsigned short> numbers;
    Compressor::compress(msg, numbers);
    string hideMe = BinaryConverter::encode(numbers);
//    for (int i = 0; i < hideMe.size(); i++)
//    {
//        if (hideMe[i] == ' ')
//            cout << '_';
//        if (hideMe[i] == '\t')
//            cout << '-';
//    }
//    cout << endl;
//    string hideMe = "    \t \t\t\t \t      \t\t \t \t  \t\t\t \t\t ";
    // divvy secret messagea
    int L = (int)hideMe.size();
    int N = lineCount;
    int nBits = 0;
    int chC = 0;
    string bit;
    stack<string> messageBit;
    for (int i = 0; i < hideMe.size()-1; i++)
    {

        if (nBits < (L%N))
        {
            if ((L/N)+1 != chC)
            {
                bit += hideMe[i];
                chC++;
            }
            else
            {
                messageBit.push(bit);
                chC = 0;
                nBits++;
                bit = "";
            }
        }
        else
        {
            if ((L/N) != chC)
            {
                bit+= hideMe[i];
                chC++; 
            }
            else
            {
                messageBit.push(bit);
                chC = 0;
                nBits++;
                bit = ""; 
            }
        }
    }
    // append message bits to stripped lines
    for (auto q = scrubbedLines.begin(); q != scrubbedLines.end(); q++)
    {
        string finLine = (*q) + messageBit.top();
        messageBit.pop();
        // add all of 'em to hostOut
        hostOut += finLine;
    }
        
//    for (auto q = lines.begin(); q != lines.end(); q++)
//        cout << (*q) << "//";
//    cout << endl << endl;
//    
//    for (auto q = scrubbedLines.begin(); q!= scrubbedLines.end(); q++)
//        cout << (*q) << "//";
    
	return true;
}

bool Steg::reveal(const string& hostIn, string& msg) 
{
    
	return false;  // This compiles, but may not be correct
}
