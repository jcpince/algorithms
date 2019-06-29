/*
https://leetcode.com/problems/integer-to-roman/

12. Integer to Roman
Medium

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as II in Roman numeral, just two one's added together. Twelve is written as, XII, which is simply X + II. The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:

    I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: 3
Output: "III"

Example 2:

Input: 4
Output: "IV"

Example 3:

Input: 9
Output: "IX"

Example 4:

Input: 58
Output: "LVIII"
Explanation: L = 50, V = 5, III = 3.

Example 5:

Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

const string units[] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
const string decimals[] = {"X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const string centains[] = {"C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const string mills[] = {"M", "MM", "MMM"};

class Solution {
public:
    string intToRoman(int num) {
        int u = num % 10, d = (num / 10) % 10, c = (num / 100) % 10, m = (num / 1000) % 4;
        string result = "";
        if (m) result += mills[m-1];
        if (c) result += centains[c-1];
        if (d) result += decimals[d-1];
        if (u) result += units[u-1];
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    int num = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    string result = s.intToRoman(num);
    if (result == expected) return 0;

    printf("intToRoman(%d) returned %s but expected %s\n", num, result.c_str(), expected.c_str());
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
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
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;
    return errors_count;
}
