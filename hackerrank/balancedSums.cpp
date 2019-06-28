/*
https://www.hackerrank.com/challenges/sherlock-and-array/problem

Watson gives Sherlock an array of integers. His challenge is to find an element of the array such that the sum of all elements to the left is equal to the sum of all elements to the right. For instance, given the array , is between two subarrays that sum to . If your starting array is , that element satisfies the rule as left and right sum to

.

You will be given arrays of integers and must determine whether there is an element that meets the criterion.

Function Description

Complete the balancedSums function in the editor below. It should return a string, either YES if there is an element meeting the criterion or NO otherwise.

balancedSums has the following parameter(s):

    arr: an array of integers

Input Format

The first line contains

, the number of test cases.

The next
pairs of lines each represent a test case.
- The first line contains , the number of elements in the array .
- The second line contains space-separated integers where

.

Constraints




Output Format

For each test case print YES if there exists an element in the array, such that the sum of the elements on its left is equal to the sum of the elements on its right; otherwise print NO.

Sample Input 0

2
3
1 2 3
4
1 2 3 3

Sample Output 0

NO
YES

Explanation 0

For the first test case, no such index exists.
For the second test case,
, therefore index

satisfies the given conditions.

Sample Input 1

3
5
1 1 4 1 1
4
2 0 0 0
4
0 0 2 0

Sample Output 1

YES
YES
YES

Explanation 1

In the first test case,
is between two subarrays summing to .
In the second case, is between two subarrays summing to .
In the third case, is between two subarrays summing to .
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;


string balancedSums(const vector<int> &arr) {

    if (arr.size() == 0) return "NO";

    uint64_t sum_left = 0, sum_right = 0;
    for (int e : arr) sum_right += e;

    for (int e : arr) {
        sum_right -= e;
        if (sum_right == sum_left) return "YES";
        sum_left += e;
    }
    return "NO";
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> arr = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    string result = balancedSums(arr);
    if (result == expected) return 0;

    printf("balancedSums(%s) returned %s but expected %s\n", array2str(arr).c_str(),
        result.c_str(), expected.c_str());
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
