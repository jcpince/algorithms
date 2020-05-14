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

static const auto _=[](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);cout.tie(nullptr);
        return 0;
}();

class Solution {
        bool isMatch2(const char *s, const char *p) {

                //printf("s: '%s'; p: '%s'\n", s, p);
                /* skip the successive wildcards */
                if (*p == '*') {
                        while(p[1] == '*') p++;
                        if (!p[1]) return true;
                }

                if (!*s) return (!*p || ((*p == '*') && !p[1]));

                if (*s == *p || *p == '?')
                        return isMatch(s+1, p+1);

                if (*p != '*') /* not matching and no wildcard */
                        return false;

                /* apply the wildcard */
                /* Check all the next occurrence of p[1]*/
                while (*s) {
                        while (*s && *s != p[1]) s++;
                        if (*s) {
                                if (isMatch(s, p+1)) return true;
                                s++;
                        }
                }
                return false;
        }
        int findNeedle(const char *s, const char *p) {
                int res = -1;
                while(*s && (*s == *p || *p == '?')) {
                        s++;
                        p++;
                        res++;
                }
                return res < 0 ? res : res + 1;
        }
        bool isMatch3(const char *s, const char *p) {
                //printf("s: '%s'; p: '%s'\n", s, p);
                while(*s && (*s == *p || *p == '?')) {
                        s++;
                        p++;
                }

                if (*p == '*') while(p[1] == '*') p++;

                if (!*p) return !*s;

                if (!*s) return !*p || (*p == '*' && !p[1]);

                /* Still some characters in s and p after '*' */
                if (*p != '*') return false;
                p++;

                /* apply the wildcard */
                /* Check all the next occurrence of p[1]*/
                while (*s) {
                        int off = findNeedle(s, p);
                        if (off < 0) return false;
                        s += off;
                        if (isMatch(s++, p+off)) return true;
                }
                return false;
        }
        int substrOffset(const char *s, const char *p, int &plen) {
                int off = 0;
                plen = 0;

                do {
                        /* Find the next candidate starting point */
                        while (*s && *s != *p && *p != '?') {
                                s++;
                                off++;
                        }
                        /* backup in case of wrong candidate */
                        const char *s0 = s, *p0 = p;
                        while (*s && (*s == *p || *p == '?'))
                        {
                                s++;
                                p++;
                                plen++;
                        }
                        if (!*s || !*p || *p == '*')
                                return !*p || *p == '*' ? off : -1;

                        /* Didn't reach the end of a fragment, go to the next
                         * candidate
                         */
                        s = s0+1;
                        p = p0;
                        off += 1;
                        plen = 0;
                } while (*s);
                return -1;
        }
        bool isMatch4(const char *s, const char *p) {
                int pattern_len = 0;

                /* Look for the first fixed pattern */
                while(*s && *p && *p != '*') {
                        if (*s != *p && *p != '?') return false;
                        s++;
                        p++;
                }
                bool has_variable = *p == '*';

                while (*s && *p) {

                        /* skip * */
                        while(*p == '*') p++;
                        if (!*p) return has_variable;

                        int off = substrOffset(s, p, pattern_len);

                        printf("substrOffset('%s', '%s') returned %d (len %d)\n",
                                s, p, off, pattern_len);

                        if (off == -1) return false;

                        s = &s[off + pattern_len];
                        p = &p[pattern_len];
                }
                if (*p) {
                        /* skip last * */
                        while(*p == '*') p++;
                        return !*s && !*p;
                }
                if (!*s || !has_variable) return !*s;
                if (!pattern_len) return false;

                /* Got to the end of p, check if s ends with p */
                p = &p[-pattern_len];
                const char *s0 = s;
                while (*s) s++;
                printf("Variable, check the end with %s, %s\n", s, p);
                if (s < s0 + pattern_len) return false;
                s = &s[-pattern_len];
                printf("Variable, check the end with %s, %s\n", s, p);
                return substrOffset(s, p, pattern_len) == 0;
        }

        int lastWildCard(const char *p) {
                int lastoffset = -1, offset = 0;
                while (p[offset]) {
                        if (p[offset] == '*') lastoffset = offset;
                        offset++;
                }
                return lastoffset;
        }
        bool isMatch(const char *s, const char *p) {
                int pattern_len = 0, global_offset = 0;

                /* Look for the first fixed pattern */
                while(*s && *p && *p != '*') {
                        if (*s != *p && *p != '?') return false;
                        s++;
                        p++;
                }
                /* The last wildcard tells us when to reach out to the end and
                 * check the last pattern */
                int lastwc = lastWildCard(p);

                /* If no wild card, just check that we reached the end
                 * of p and s*/
                if (lastwc < 0) return !*s && !*p;

                /* skip first wild cards */
                while(*p == '*') {
                        global_offset++;
                        p++;
                }

                /* Loop over the fixed patterns until the last */
                while (*s && *p && global_offset < lastwc) {
                        int off = substrOffset(s, p, pattern_len);

                        // printf("substrOffset('%s', '%s') returned %d (len %d)\n",
                        //         s, p, off, pattern_len);

                        if (off == -1) return false;

                        s = &s[off + pattern_len];
                        p = &p[pattern_len];
                        global_offset += pattern_len;
                        /* skip wild cards */
                        while(*p == '*') {
                                global_offset++;
                                p++;
                        }
                }
                /* skip last wild cards */
                while(*p == '*') p++;
                if (!*s) return !*p;

                /* Move to the end of s - len(pattern) */
                int len = strlen(p);
                const char *s0 = s;
                while(*s) s++;
                if ((s - s0) < len) return false;
                s -= len;

                /* Advance until *s != *p */
                while (*s && (*s == *p || *p == '?')) {s++;p++;}
                return !*s && !*p;
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
