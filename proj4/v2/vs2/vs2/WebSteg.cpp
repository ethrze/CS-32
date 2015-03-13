#include "provided.h"
#include "http.h"
#include <string>
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
    string pageContents;
    // retrieve web page
    HTTP().get(url, pageContents);
    // compress / encode / hide message
    vector<unsigned short> numbers;
    Compressor::compress(msg, numbers);
    string hideMe = BinaryConverter::encode(numbers);
    string hostOut;
    Steg::hide(pageContents, hideMe, hostOut);
    // put that text in host
    host = hostOut;
    return true;
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
    string pageContents;
    string mssg;
    // retrieve web page
    HTTP().get(url, pageContents);
    // extract / decode / decompress
    vector<unsigned short> numbers;
    Steg::reveal(pageContents, mssg);
    BinaryConverter::decode(mssg, numbers);
    string done;
    Compressor::decompress(numbers, done);
    // put that text in msg
    msg = done;
    
    return true;
}
