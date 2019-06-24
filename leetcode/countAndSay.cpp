/*
38. Count and Say
Easy

794

6114

Favorite

Share
The count-and-say sequence is the sequence of integers with the first five terms as following:

1.     1
2.     11
3.     21
4.     1211
5.     111221
1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.

Given an integer n where 1 ≤ n ≤ 30, generate the nth term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.



Example 1:

Input: 1
Output: "1"
Example 2:

Input: 4
Output: "1211"
*/


#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#define MAX_CACHE_SIZE 30

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

class Solution {
private:
    vector<string> cache = {"1\0"};
public:
    string countAndSay(int n) {
        if (n <= 0 or n >= MAX_CACHE_SIZE) return "";

        if (n <= (int)cache.size()) return vectorat(cache, n-1);

        /* not in the cache, build it */
        const char *prev = cache.back().c_str();
        n -= cache.size();
        for (int idx = 0 ; idx < n ; idx++) {
            string newstr;
            do {
                const char c = prev[0];
                int count = 0;
                while (*prev == c) { prev++; count++; }
                newstr += to_string(count) + c;
            } while (*prev);
            cache.push_back(newstr);
            prev = cache.back().c_str();
        }
        return cache.back();
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    string result = ((Solution *)_s)->countAndSay(n);
    if (result == expected) return 0;

    printf("countAndSay(%d) returned %s but expected %s\n", n, result.c_str(), expected.c_str());
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    Solution s;
    int tests_ran = 0;
    const char *tc_id = NULL;

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
        cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
            endl;
        return -1;
    }

    UnitTests uts((void*)&s, &run_test_case, argv[1]);

    if (argc == 3) tc_id = argv[2];

    int errors_count = uts.run_test_cases(tc_id, tests_ran);
    if (errors_count == 0)
        cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
    else
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;
    return errors_count;
}
