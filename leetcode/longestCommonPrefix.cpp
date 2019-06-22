/*
14. Longest Common Prefix
Easy

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: ["flower","flow","flight"]
Output: "fl"

Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

Note:

All given inputs are in lowercase letters a-z.
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

/*class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        if (strs.size() == 1) return strs[0];

        string prefix = "";
        int idx = 0;
        char c = strs[0].c_str()[idx];

        while (idx < strs[0].size())
        {
            for (vector<string>::iterator it = strs.begin() ; it < strs.end() ; it++)
                if ((*it).c_str()[idx] != c) return prefix;

            prefix += c;
            c = strs[0].c_str()[++idx];
        }
        //cout << "longestCommonPrefix returns " << prefix << endl;
        return prefix;
    }
};*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& _strs) {

        if (_strs.size() == 0) return "";
        if (_strs.size() == 1) return _strs[0];

        int idx = 0, jdx = 0, prefix_size = _strs[0].size(), nb_strs = _strs.size();
        const char *strs[nb_strs];
        for (vector<string>::iterator it = _strs.begin() ; it < _strs.end() ; it++, idx++)
        {
            strs[idx] = _strs[idx].c_str();
            prefix_size = _strs[idx].size() < prefix_size ? _strs[idx].size() : prefix_size;
        }
        if (!prefix_size) return "";
        char prefix[prefix_size+1];

        while (jdx < prefix_size)
        {
            char c = strs[0][jdx];
            for (idx = 0 ; idx < nb_strs ; idx++)
                if (c != strs[idx][jdx]) goto end;

            prefix[jdx++] = c;
        }
end:
        prefix[jdx] = 0;
        cout << "longestCommonPrefix returns " << prefix << endl;
        return string(prefix);
    }
};

/*class Solution {
public:
    string longestCommonPrefix(vector<string>& _strs) {

        if (_strs.size() == 0) return "";
        if (_strs.size() == 1) return _strs[0];

        string prefix = "";
        int idx = 0, size = _strs[0].size(), nb_strs = _strs.size();
        const char **strs = (const char **)malloc(nb_strs*sizeof(const char *));
        if (!strs) return "";
        for (vector<string>::iterator it = _strs.begin() ; it < _strs.end() ; it++, idx++)
            strs[idx] = _strs[idx].c_str();

        char c = *strs[0];
        while (idx < size)
        {
            for (idx = 0 ; idx < nb_strs ; idx++)
                if (c != *strs[idx]) goto end;
                else strs[idx]++;

            prefix += c;
            c = *strs[0];
        }
end:
        //cout << "longestCommonPrefix returns " << prefix << endl;
        free(strs);
        return prefix;
    }
};*/

int main(int argc, char **argv)
{
    Solution s;
    vector<string> strs = {"dog","racecar","car"};
    assert(strlen(s.longestCommonPrefix(strs).c_str()) == 0);

    strs = {"flower","flow","flight"};
    assert(strlen(s.longestCommonPrefix(strs).c_str()) == 2);

    strs = {};
    assert(strlen(s.longestCommonPrefix(strs).c_str()) == 0);

    strs = {"abc","abc"};
    assert(strlen(s.longestCommonPrefix(strs).c_str()) == 3);

    cout << "All tests succeeded" << endl;
    return 0;
}
