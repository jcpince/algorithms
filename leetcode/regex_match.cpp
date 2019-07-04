/*
10. Regular Expression Matching
Hard

Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Note:

    s could be empty and contains only lowercase letters a-z.
    p could be empty and contains only lowercase letters a-z, and characters like . or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:

Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:

Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".

Example 5:

Input:
s = "mississippi"
p = "mis*is*p*."
Output: false

*/

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

#define DEBUG 1
#undef DEBUG
#ifdef DEBUG
#define debug_print printf
#define dev_assert assert
#else
#define debug_print(...)
#define dev_assert(...)
#endif

const bool continue_on_failure = false;

/* -------------- INCOMPLETE -------------- */

class Solution {
    bool isMatch(const char *str, const char *regex)
    {
        if (!*regex && !*str) return true;

        current = *c_regex++;
        assert(current != '*');

        zeromore = (*c_regex == '*');
        if (zeromore)
        {
            /* find the next non zeromore sequence */
            next = *++c_regex;
            assert(next != '*');
            while (*(c_regex+1) && *(c_regex+1) == '*')
        }

        str = advance_str(current, zeromore, str, regex);
        return false;
    }
public:
    bool isMatch(string &str, string &pattern) {
        char current, next;
        bool zeromore = false;

        if (str.length() == 0) return (pattern.length() == 0);
        if (pattern.length() == 0) return false;

        const char *c_str = , c_regex = pattern.c_str();
        return isMatch(str.c_str(), pattern.c_str());
    }
};

int check_solution(Solution &s, string &str, string &pattern, bool expected)
{
    bool result = s.isMatch(str);
    if (result == expected) return 0;

    printf("isMatch(%s, %s) returned %d\n", str.c_str(), pattern.c_str(), result);
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    Solution s;
    int errors = 0, tests_count = 0;
    string str, pattern;

    str = "aa"; pattern = "a"; errors += check_solution(s, str, pattern, false); tests_count++;
    str = "aa"; pattern = "a*"; errors += check_solution(s, str, pattern, true); tests_count++;
    str = "ab"; pattern = ".*"; errors += check_solution(s, str, pattern, true); tests_count++;
    str = "aab"; pattern = "c*a*b"; errors += check_solution(s, str, pattern, true); tests_count++;
    str = "mississippi"; pattern = "mis*is*p*."; errors += check_solution(s, str, pattern, true); tests_count++;

    if (errors == 0)
        cout << "All tests succeeded!!!" << endl;
    else
        cout << errors << " tests failed over a total of " << tests_count << endl;
    return 0;
}
