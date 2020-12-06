/*87. Scramble String
Hard

Share
We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.
If the length of the string is > 1, do the following:
Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
Apply step 1 recursively on each of the two substrings x and y.
Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.

 
Example 1:
Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at ranom index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.
As there is one possible scenario that led s1 to be scrambled to s2, we return true.


Example 2:
Input: s1 = "abcde", s2 = "caebd"
Output: false


Example 3:
Input: s1 = "a", s2 = "a"
Output: true
 

Constraints:

s1.length == s2.length
1 <= s1.length <= 30
s1 and s2 consist of lower-case English letters.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    int strsum(const string &s) {
        const char* ptr = s.c_str();
        int sum = 0;
        while (*ptr) sum += *ptr++;
        return sum;
    }
    int strsum(const string &s, int start, int len) {
        const char* ptr = &(s.c_str())[start];
        int sum = 0;
        while (len--) sum += *ptr++;
        return sum;
    }
    bool _scramble(const string &s1, const string &s2) {
        bool result = false;
        assert(s1.length() == s2.length());
        if (s1 == s2) return true;
        if (s1.length() < 2) return false;
        //string message = "_sramble(" + s1 + "," + s2 + ")";
        for (unsigned lx = 1 ; lx < s1.length() ; lx++) {
            int ly = s1.length() - lx;
            string s1x = s1.substr(0, lx), s1y = s1.substr(lx, ly);
            string s2x = s2.substr(0, lx), s2y = s2.substr(lx, ly);
            if (strsum(s1x) == strsum(s2x) and strsum(s1y) == strsum(s2y)) {
                //message += " calls1 scramble(" + s1x + "," + s2x + " and " + s1y + "," + s2y + ")";
                if (_scramble(s1x, s2x) and _scramble(s1y, s2y)) {
                    result = true;
                    break;
                }
            }
            
            // inv x and y
            string s2xinv = s2.substr(ly, lx);
            string s2yinv = s2.substr(0, ly);
            if (strsum(s1x) == strsum(s2xinv) and strsum(s1y) == strsum(s2yinv)) {
                //message += " calls2 (" + s1x + "," + s2xinv + " and " + s1y + "," + s2yinv + ")";
                if (_scramble(s1x, s2xinv) and _scramble(s1y, s2yinv))  {
                    result = true;
                    break;
                }
            }
        }
        //cout << message << " returns " << result << endl;
        return result;
    }
    bool scramble(const string &s1, string before, string after, const string &s2) {
        if (s1.length() < 2) return false;
        if (before.length() && strsum(before, 0, before.length()) != strsum(s2, 0, before.length()))
        // {
        //     string sorted1 = before; sort(sorted1.begin(), sorted1.end());
        //     string sorted2 = s2.substr(0, sorted1.length()); sort(sorted2.begin(), sorted2.end());
        //     assert(sorted1 != sorted2);
        //     printf("%s doesn't start with the letters of %s\n", s2.c_str(), before.c_str());
            return false;
        // } else {
        //     string sorted1 = before; sort(sorted1.begin(), sorted1.end());
        //     string sorted2 = s2.substr(0, sorted1.length()); sort(sorted2.begin(), sorted2.end());
        //     printf("%s starts with the letters of %s\n", s2.c_str(), before.c_str());
        //     assert(sorted1 == sorted2);
        // }
        if (after.length() && strsum(after, 0, after.length()) != strsum(s2, s2.length() - after.length(), after.length()))
        // {
        //     string sorted1 = after; sort(sorted1.begin(), sorted1.end());
        //     string sorted2 = s2.substr(s2.length()-sorted1.length(), s2.length()); sort(sorted2.begin(), sorted2.end());
        //     assert(sorted1 != sorted2);
        //     printf("%s doesn't end with the letters of %s\n", s2.c_str(), after.c_str());
            return false;
        // } else {
        //     string sorted1 = after; sort(sorted1.begin(), sorted1.end());
        //     string sorted2 = s2.substr(s2.length()-sorted1.length(), s2.length()); sort(sorted2.begin(), sorted2.end());
        //     printf("%s ends with the letters of %s -- %s vs %s\n", s2.c_str(), after.c_str(), sorted1.c_str(), sorted2.c_str());
        //     assert(sorted1 == sorted2);
        // }
        // printf("scramble(\"%s\", \"%s\", \"%s\")\n", s1.c_str(), before.c_str(), after.c_str());
        for (unsigned split = 1 ; split < s1.length() ; split++) {
            string x = s1.substr(0, split), y = s1.substr(split, s1.length() - split);
            // printf("++ scramble %s -- \"%s\" \"%s\" \"%s\" \"%s\"\n", s1.c_str(),
            //         before.c_str(), x.c_str(), y.c_str(), after.c_str());
            if (before + x + y + after == s2) return true;
            if (before + y + x + after == s2) return true;
            if (scramble(x, before, y+after, s2) or
                scramble(x, before+y, after, s2)) return true;
            if (scramble(y, before, x+after, s2) or
                scramble(y, before+x, after, s2)) return true;
        }
        return false;
    }
public:
    bool isScramble(const string &s1, const string &s2) {
        if (s1 == s2) return true;
        string sorted1 = s1; sort(sorted1.begin(), sorted1.end());
        string sorted2 = s2; sort(sorted2.begin(), sorted2.end());
        if (sorted1 != sorted2) return false;
        //return scramble(s1, "", "", s2);
        return _scramble(s1, s2);
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    string s1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s1"];
    string s2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s2"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.isScramble(s1, s2);

    if (result == expected) return 0;

    printf("isScramble(%s, %s) returned %d but expected %d\n", s1.c_str(), s2.c_str(),
        result, expected);
    dev_assert(continue_on_failure);
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