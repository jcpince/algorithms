/*
3. Longest Substring Without Repeating Characters
Medium

Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

#include "listNode.h"

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() == 1) return 1;
        int len = 0, maxlen = 0;
        bool used[256] = {0};
        const char *str = s.c_str(), *start = str;
        while (*str)
        {
            const char c = *str;
            if (!used[c])
            {
                len++;
                used[c] = true;
                str++;
            }
            else
            {
                if (len > maxlen) maxlen = len;
                if (len = 1)
                {
                    len = 0;
                    bzero(used, sizeof(used));
                    str = start++;
                } else
                {
                    int skip = 1;
                    while (*start != c)
                        skip++;
                    len -= skip;
                    start += skip;
                    str = start++;
                }
            }
        }
        printf("lengthOfLongestSubstring(%s) returns %d\n", s.c_str(), maxlen > len ? maxlen : len);
        return maxlen > len ? maxlen : len;
    }
};

int main(int argc, char **argv)
{
    Solution s;
    assert(s.lengthOfLongestSubstring("abcabcbb") == 3);
    assert(s.lengthOfLongestSubstring("bbbbb") == 1);
    assert(s.lengthOfLongestSubstring("pwwkew") == 3);
    assert(s.lengthOfLongestSubstring("") == 0);
    assert(s.lengthOfLongestSubstring("au") == 2);
    assert(s.lengthOfLongestSubstring("aab") == 2);
    assert(s.lengthOfLongestSubstring("dvdf") == 3);

    cout << "All tests succeeded" << endl;
    return 0;
}
