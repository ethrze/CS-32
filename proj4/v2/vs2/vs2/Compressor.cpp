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
    unsigned short cap = *(numbers.end()-1);
    cout << cap << endl;
    int capacity = (int)(cap);
    int nBuckets = capacity * 2;
    
    // 1.
    HashTable<unsigned short, string> H(nBuckets, capacity);
    // 2.
    for (unsigned short j = 0; j < 256; j++)
    {
        string charj = string();
        charj += static_cast<char>(j);
        H.set(j, charj, true);
    }
    // 3.
    int nextFreeID = 256;
    // 4.
    string runSoFar = string();
    // 5. empty string for decompressed result
    string output = string();
    
    
    // <unsigned short, string>
    // 6.
    for (auto q = numbers.begin(); q != (numbers.end()-1); q++)
    {
        unsigned short us = *q;
        // a.
        if (us <= 255) // represents normal 1-byte character
        {
            string expandedRun = "";
            // i.
            string str;
            H.get(us, str);
            output += str;
            // ii.
            if (runSoFar == "")
            {
                runSoFar += str;
                continue;
            }
            // iii.
            else
            {
                expandedRun += runSoFar;
                expandedRun += us;
            }
            // iv.
            if (!H.isFull())
            {
                H.set(nextFreeID, expandedRun);
                nextFreeID++;
            }
            // v.
            else
            {
                // 1.
                unsigned short key;
                string value;
                H.discard(key, value);
                // 2.
                H.set(key, expandedRun);
            }
            // vi.
            runSoFar = "";
            // v.
            continue;
        }
        // b.
        else
        {
            // i.
            string S;
            if (H.get(us, S) == false)
            {
                cout << "Failure in formatting?" << endl;
                return false;
            }
            // ii.
            H.touch(us);
            // iii.
            H.get(us, S);
            output += S;
            // iv.
            runSoFar = S;
            // v.
            continue;
        }
    }
    // 7.
    s = output;
	return true;
}








