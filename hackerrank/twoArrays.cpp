/*
https://www.hackerrank.com/challenges/two-arrays/problem

Consider two -element arrays of integers, and . You want to permute them into some and such that
the relation holds for all where . For example, if , , and , a valid satisfying our relation would
be and , and

.

You are given
queries consisting of , , and . For each query, print YES on a new line if some permutation ,

satisfying the relation above exists. Otherwise, print NO.

Function Description

Complete the twoArrays function in the editor below. It should return a string, either YES or NO.

twoArrays has the following parameter(s):

    k: an integer
    A: an array of integers
    B: an array of integers

Input Format

The first line contains an integer

, the number of queries.

The next
sets of

lines are as follows:

    The first line contains two space-separated integers

and , the size of both arrays and
, and the relation variable.
The second line contains
space-separated integers
.
The third line contains
space-separated integers

    .

Constraints

Output Format

For each query, print YES on a new line if valid permutations exist. Otherwise, print NO.

Sample Input

2
3 10
2 1 3
7 8 9
4 5
1 2 2 1
3 3 3 4

Sample Output

YES
NO

Explanation

We perform the following two queries:

, , and . We permute these into and

so that the following statements are true:

Thus, we print YES on a new line.
, , and . To permute and into a valid and , we would need at least three numbers in to be greater
than ; as this is not the case, we print NO on a new line.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

string twoArrays(int &k, vector<int> &A, vector<int> &B) {

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int bidx = B.size() - 1;
    for (int a : A) {
        if ((a + B[bidx--]) < k) return "NO";
    }
    return "YES";
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> A = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["A"];
    vector<int> B = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["B"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    string result = twoArrays(k, A, B);
    if (result == expected) return 0;

    printf("twoArrays(%d, %s, %s) returned %s but expected %s\n", k, array2str(A).c_str(),
        array2str(B).c_str(), result.c_str(), expected.c_str());
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
