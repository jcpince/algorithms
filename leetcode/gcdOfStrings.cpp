#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    bool isValidPattern(int len, const char *c_str1, const char *c_str2) {
        // Quick check
        if (c_str1[len-1] != c_str2[len-1]) return false;

        const char *pattern = c_str1;
        int idx = 0;
        while (*c_str1 or *c_str2) {
            if (*c_str1 and (*c_str1 != pattern[idx])) return false;
            if (*c_str2 and (*c_str2 != pattern[idx])) return false;
            if (*c_str1) c_str1++;
            if (*c_str2) c_str2++;
            if (++idx == len) idx = 0;
        }
        return (!*c_str1 and !*c_str2 and !idx);
    }
public:
    string gcdOfStrings(string &str1, string &str2) {
        int len1 = str1.length(), len2 = str2.length();
        if ((str1[0] != str2[0]) or (str1[len1-1] != str2[len2-1])) return "";

        if (len1 == len2) {
            if (str1 == str2) return str1;
            return "";
        }
        int gcd_len = min(len1, len2);

        // Find the first multiple of both
        while (gcd_len and ((len1 % gcd_len) or (len2 % gcd_len))) gcd_len--;
        if (!gcd_len) return "";

        const char *c_str1 = str1.c_str(), *c_str2 = str2.c_str();

        while (gcd_len) {
            if (isValidPattern(gcd_len, c_str1, c_str2)) return str1.substr(0, gcd_len);
            else while (gcd_len and ((len1 % gcd_len) or (len2 % gcd_len))) gcd_len--;
        }
        return "";
    }
};

/*class Solution {
    bool compare(string &shortest, string &longest, int len) {
        const char *s1 = shortest.c_str(), *s2 = longest.c_str(), *limit = &s1[len];
        while ((s1 < limit) && (*s1++ == *s2++));
        return s1 == limit;
    }
public:
    string gcdOfStrings(const string &str1, const string &str2) {
        string shortest = str2.length() > str1.length() ? str1 : str2;
        string longest = str2.length() > str1.length() ? str2 : str1;

        if (longest.compare(0, shortest.length(), shortest)) return "";

        int length = shortest.length(), multiple = 1, pidx = 0;
        const char *slong, *sshort, *pattern = shortest.c_str();
        while (length) {
            pidx = 0;
            //printf("Check the pattern with %d chars -- %d -- compare(%s, %s)= %d\n", length,
            //      longest.length() % length, longest.c_str(), shortest.c_str(), compare(shortest, longest, length));
            if (!(longest.length() % length) and compare(shortest, longest, length)) {
                // candidate, check the pattern
                //printf("Check the pattern %s\n", str1.substr(0, length).c_str());
                sshort = &shortest.c_str()[length];
                while (*sshort && *sshort == pattern[pidx]) {
                    sshort++;
                    pidx++;
                    if (pidx == length) pidx = 0;
                }
                if (!pidx) {
                    slong = &longest.c_str()[length];
                    while (*slong && *slong == pattern[pidx]) {
                        slong++;
                        pidx++;
                        if (pidx == length) pidx = 0;
                    }
                    if (!pidx) return str1.substr(0, length);
                }
            }
            while ((shortest.length() % ++multiple) and (multiple <= shortest.length()));
            length = shortest.length() / multiple;
        }
        return "";
    }
};*/

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    string str1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["str1"];
    string str2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["str2"];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    string result = s.gcdOfStrings(str1, str2);

    if (result == expected) return 0;

    printf("gcdOfStrings(%s, %s) returned %s but expected %s\n", str1.c_str(), str2.c_str(),
        result.c_str(), expected.c_str());
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
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;
    return errors_count;
}
