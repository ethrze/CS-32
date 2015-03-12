#include "provided.h"
#include "substituteHashTable.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
    // calculate capacity
    int cap;
    int len = (int)(s.length());
    if (16384 > (len/2 + 512))
        cap = (len/2 + 512);
    else
        cap = 16384;
    
    // cap / nBuckets must be <= 0.5
    int nBuckets = cap * 2;
    // create Hashtable
    HashTable<string, unsigned short> H(nBuckets, cap);
    // 2. populate hash table
    for (unsigned short j = 0; j < 256; j++)
    {
//        char charj = static_cast<char>(j);
        string charj = string();
        charj += static_cast<char>(j);
        H.set(charj, j, true);
    }
    
    // 3. set nextFreeID
    int nextFreeID = 256;
    // 4. create empty string runSoFar
    string runSoFar = string();
    // 5. create empty vecotr V to contain compressed result
    vector<unsigned short> V;
    // 6. for each character 'c' in input string,
    for (int i = 0; i < s.length(); i++) // step 6
    {
        // weird casting
        char m = s[i];
        string c = "";
        c += m; // monkey business
        // a. create string named expandedRun equal to runSoFar + c
        string expandedRun = runSoFar + c;
        // b. if expandedRun is already contained in H
        unsigned short x;
        if (H.get(expandedRun, x) == true) // if expanded run is in the HashTable
        {
            // i. set runSoFar equal to expandedRun, inc current run length by one char
            runSoFar = expandedRun;
            // ii. go to next iteration of step 6 above.
            continue;
        }
        else
        {
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
    // step 7
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
