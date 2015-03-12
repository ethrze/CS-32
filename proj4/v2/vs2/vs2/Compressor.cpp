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
    for (int i = 0; i < 256; i++)
    {
        
    }
    
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
	return false;  // This compiles, but may not be correct
}
