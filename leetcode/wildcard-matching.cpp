/*
44. Wildcard Matching
Hard

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

Note:

    s could be empty and contains only lowercase letters a-z.
    p could be empty and contains only lowercase letters a-z, and characters like ? or *.

Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false


*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

class Solution {
        bool isMatch(const char *s, const char *p) {

                //printf("s: '%s'; p: '%s'\n", s, p);

                if (!*s && !*p) return true;
                if (!*p) return false;

                if (*s && (*s == *p || *p == '?') && isMatch(s+1, p+1))
                        return true;

                if (((*s == *p || *p == '?') && p[1] == '*') || *p == '*') {
                        if (*s) return isMatch(s, p+1) || isMatch(s+1, p);
                        else return isMatch(s, p+1);
                }

                return false;
        }
public:
        bool isMatch(const string &_s, const string &_p) {
                return isMatch(_s.c_str(), _p.c_str());
        }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        string s = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s"];
        string p = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["p"];
        bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        bool result = _s.isMatch(s, p);

        if (result == expected) return 0;

        printf("isMatch(%s, %s) returned %d but expected %d\n", s.c_str(),
                p.c_str(), result, expected);
        assert(continue_on_failure);
        return 1;
}

int main(int argc, char **argv) {
        int tests_ran = 0;
        const char *tc_id = NULL;

        if (argc < 2 || argc > 3)
        {
                cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
                cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
                endl;
                return -1;
        }

        UnitTests uts(NULL, &run_test_case, argv[1]);

        if (argc == 3) tc_id = argv[2];

        int errors_count = uts.run_test_cases(tc_id, tests_ran);
        if (errors_count == 0)
                cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
        else
                cout << errors_count << " test(s) failed over a total of "
                        << tests_ran << endl;

        return errors_count;
}
