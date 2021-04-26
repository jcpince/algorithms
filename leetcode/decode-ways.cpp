/*

91. Decode Ways
Medium

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

Example 1:
Input: s = "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).

Example 2:
Input: s = "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:
Input: s = "0"
Output: 0
Explanation: There is no character that is mapped to a number starting with '0'. We cannot ignore a zero when we face it while decoding. So, each '0' should be part of "10" --> 'J' or "20" --> 'T'.

Example 4:
Input: s = "1"
Output: 1
 

Constraints:
1 <= s.length <= 100
s contains only digits and may contain leading zero(s).
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
public:
    int numDecodings0(const string &_s) {
        const char *s = _s.c_str();
        while(*s && *s == '0') s++;
        if (!s[0] || !s[1]) return s[0] ? 1 : 0;
        
        int r[3] = {1, 1, 1}, digit0 = *s++ - '0';
        printf("num %d: r[%d, %d, %d]\n", digit0, r[0], r[1], r[2]);
        while(*s) {
            int digit = *s++ - '0';
            if (digit0 + digit == 0) return 0;
            if (digit == 0 and digit0 > 2) return 0;
            int num = digit0 * 10 + digit;
            if (digit == 0) { r[2] = r[0]; r[1] = 0; }
            else if (num > 10 and num < 27) r[2] = r[0] + r[1];
            digit0 = digit;
            r[0] = r[1];
            r[1] = r[2];
            printf("num %d: r[%d, %d, %d]\n", num, r[0], r[1], r[2]);
        }
        printf("%s(%s) returns %d\n", __func__, _s.c_str(), r[2]);
        return r[2];
    }
    int numDecodings(const string &_s) {
        const char *s = _s.c_str();
        if (s[0] == '0') return 0;
        
        int r[3] = {1, 1, 1}, digit0 = *s++ - '0';
        while(*s) {
            int digit = *s++ - '0';
            if (digit0 + digit == 0) return 0;
            if (digit == 0 and digit0 > 2) return 0;
            int num = digit0 * 10 + digit;
            if (digit == 0) { r[2] = r[0]; r[1] = 0; }
            else if (num > 10 and num < 27) r[2] = r[0] + r[1];
            digit0 = digit;
            r[0] = r[1];
            r[1] = r[2];
        }
        return r[2];
    }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        string in = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        int result = s.numDecodings(in);

        if (result == expected) return 0;

        printf("numDecodings(%s) returned %d but expected %d\n",
                in.c_str(), result, expected);
        assert(continue_on_failure);
        return 1;
}
