#include "provided.h"
#include "substituteHashTable.h"
#include <string>
#include <vector>
using namespace std;


void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
	  // This compiles, but may not be correct
    int cap;
    int len = (int)(s.length());
    if (16384 > (len/2 + 512))
        cap = (len/2 + 512);
    else
        cap = 16384;
    
    // cap / nBuckets must be <= 0.5
    int nBuckets = cap * 2;
        
    HashTable<string, unsigned short> H(nBuckets, cap);
    for (unsigned short j = 0; j < 256; j++)
    {
//        char charj = static_cast<char>(j);
        string charj;
        charj += static_cast<char>(j);
        H.set(charj, j, true);
    }
    
    int nextFreeID = 256;
    string runSoFar = "";
    vector<unsigned short> V;
    for (int i = 0; i < s.length(); i++) // step 6
    {
        char m = s[i];
        string c;
        c += m; // monkey business
        string expandedRun = runSoFar + c;
        unsigned short x;
        if (H.get(expandedRun, x) == true) // if expanded run is in the HashTable
        {
            runSoFar = expandedRun;
        } else {
            H.get(runSoFar, x);
        }
        V.push_back(x);
        H.touch(runSoFar);
        runSoFar = "";
        unsigned short cv;
        H.get(c, cv);
        V.push_back(cv);
        if (!H.isFull())
        {
            H.set(expandedRun, nextFreeID);
            nextFreeID++;
        }
        else
        {
            unsigned short disc;
            string whatever;
            H.discard(whatever, disc);
            H.set(expandedRun, disc);
        }
    }
    // step 6 complete
    if (runSoFar != "")
    {
        unsigned short x;
        H.get(runSoFar, x);
        V.push_back(x);
    }
    // final step
    V.push_back(cap);
    numbers = V; 
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
	return false;  // This compiles, but may not be correct
}
