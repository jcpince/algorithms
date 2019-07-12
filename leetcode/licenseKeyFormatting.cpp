/*
https://leetcode.com/problems/license-key-formatting/

482. License Key Formatting
Easy

You are given a license key represented as a string S which consists only alphanumeric character and dashes. The string is separated into N+1 groups by N dashes.

Given a number K, we would want to reformat the strings such that each group contains exactly K characters, except for the first group which could be shorter than K, but still must contain at least one character. Furthermore, there must be a dash inserted between two groups and all lowercase letters should be converted to uppercase.

Given a non-empty string S and a number K, format the string according to the rules described above.

Example 1:

Input: S = "5F3Z-2e-9-w", K = 4

Output: "5F3Z-2E9W"

Explanation: The string S has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.

Example 2:

Input: S = "2-5g-3-J", K = 2

Output: "2-5G-3J"

Explanation: The string S has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.

Note:

    The length of string S will not exceed 12,000, and K is a positive integer.
    String S consists only of alphanumerical characters (a-z and/or A-Z and/or 0-9) and dashes(-).
    String S is non-empty.

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

class Solution {
public:
    string licenseKeyFormatting(string S, int K) {

        const char *orig = S.c_str();

        // First, count the dashes
        int dash_count = 0, letters_count = 0;
        // Don't count the leading dashes
        while (*orig) {
            if (*orig++ == '-') {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
                while (*orig and (*orig == '-')) *orig++;
#pragma GCC diagnostic pop
                dash_count++;
            } else letters_count++;
        }

        if (!letters_count) return "";

        // Remove the trailing dash
        --orig;
        if (*orig == '-') dash_count--;

        int first_letters_count = K != 1 ? letters_count % K : 0;
        int new_dash_count = (letters_count - first_letters_count + 1) / K - 1;
        if (first_letters_count) new_dash_count++;

        char result[letters_count + new_dash_count + 1], *ret = result;
        result[letters_count + new_dash_count] = 0;

        /* Now, copy the chunks */
        int seg_size = first_letters_count ? first_letters_count : K;
        orig = S.c_str();
        while (*orig) {
            for (int jdx = 0 ; jdx < seg_size ; orig++) {
                if (*orig != '-') {
                    int offset = 0;
                    if (*orig >= 'a' and *orig <= 'z') offset = 'A' - 'a';
                    *ret++ = (*orig) + offset;
                    jdx++;
                }
            }
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
            if (*orig == '-') while (*orig and (*orig == '-')) *orig++;
#pragma GCC diagnostic pop
            if (*orig) *ret++ = '-';
            seg_size = K;
        }
        *ret = 0;
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    string key = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["key"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    string result = s.licenseKeyFormatting(key, k);

    if (result == expected) return 0;

    printf("licenseKeyFormatting(%s, %d) returned \"%s\" but expected \"%s\"\n", key.c_str(), k,
        result.c_str(), expected.c_str());
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
