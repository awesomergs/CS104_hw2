#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    // std::set<char> punct = {"'",'"', ',', '.', ';', ':', '!'}; scrapped, its too big a list across 4 diff groups (vs 3 for alphanumeric)
    rawWords = convToLower(rawWords);
    int s = rawWords.size();
    int left = 0;
    std::set<std::string> ans = {};
    for (int right = 0; right < s; right++){
        if (!((rawWords[right] >= 'a' && rawWords[right] <= 'z') || (rawWords[right] >= 'A' && rawWords[right] <= 'Z') || (rawWords[right] >= '0' && rawWords[right] <= '9'))){
            if (right-left > 1) {ans.insert(rawWords.substr(left, right-left));}
            left = right + 1;
        }
    }

    if (s-left > 1) {ans.insert(rawWords.substr(left, s-left));}

    return ans;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
