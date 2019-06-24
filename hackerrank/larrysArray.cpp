/*
https://www.hackerrank.com/challenges/larrys-array/problem

Larry has been given a permutation of a sequence of natural numbers incrementing from

as an array. He must determine whether the array can be sorted using the following operation any number of times:

    Choose any

consecutive indices and rotate their elements in such a way that

    .

For example, if

:

A		rotate
[1,6,5,2,4,3]	[6,5,2]
[1,5,2,6,4,3]	[5,2,6]
[1,2,6,5,4,3]	[5,4,3]
[1,2,6,3,5,4]	[6,3,5]
[1,2,3,5,6,4]	[5,6,4]
[1,2,3,4,5,6]

YES

On a new line for each test case, print YES if

can be fully sorted. Otherwise, print NO.

Function Description

Complete the larrysArray function in the editor below. It must return a string, either YES or NO.

larrysArray has the following parameter(s):

    A: an array of integers

Input Format

The first line contains an integer

, the number of test cases.

The next

pairs of lines are as follows:

    The first line contains an integer

, the length of
.
The next line contains
space-separated integers

    .

Constraints

integers that increment by from to

Output Format

For each test case, print YES if

can be fully sorted. Otherwise, print NO.

Sample Input

3
3
3 1 2
4
1 3 4 2
5
1 2 3 5 4

Sample Output

YES
YES
NO

Explanation

In the explanation below, the subscript of

denotes the number of operations performed.

Test Case 0:

is now sorted, so we print

on a new line.

Test Case 1:
.
.
is now sorted, so we print

on a new line.

Test Case 2:
No sequence of rotations will result in a sorted
. Thus, we print on a new line.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

void rotate(vector<int> &A, int index0, int last_index)
{
    debug_print("rotate1(%s, %d, %d)\n", array2str(A).c_str(), index0, last_index);
    UNUSED(last_index);
    dev_assert(last_index >= (index0 + 2));
    int a0 = A[index0];
    A[index0] = A[index0+1];
    A[index0+1] = A[index0+2];
    A[index0+2] = a0;
    debug_print("      => %s\n", array2str(A).c_str());
}

void rotate2(vector<int> &A, int index0, int last_index)
{
    debug_print("rotate2(%s, %d, %d)\n", array2str(A).c_str(), index0, last_index);
    UNUSED(last_index);
    dev_assert(last_index >= (index0 + 2));
    int a0 = A[index0];
    A[index0] = A[index0+2];
    A[index0+2] =  A[index0+1];
    A[index0+1] = a0;
    debug_print("       => %s\n", array2str(A).c_str());
}

string larrysArray(vector<int> A) {

    int Asize = A.size(), last_index = Asize - 1;

    /* skip last well placed elements */
    while (last_index and (A[last_index] == (last_index+1))) last_index--;

    /* last_index = 0, all are well placed, nothing to do */
    if (last_index == 0) return "YES";

    int pivot_value = last_index + 1;
    while (last_index >= 2) {
        int pivot_idx = 0;
        /* find the pivot value index */
        for ( ; pivot_idx < last_index ; pivot_idx++)
            if (A[pivot_idx] == pivot_value) break;
        /* Check for invalid array */
        if (pivot_idx > last_index) return "NO";

        /* Rotate A until pivot_value is well placed */
        debug_print("A(%s): rotate %d\n", array2str(A).c_str(), pivot_value);
        while ((pivot_value - pivot_idx - 1) > 0)
            if ((pivot_value - pivot_idx) == 2) {
                if (pivot_idx < 1) return "NO";
                rotate2(A, pivot_idx-1, last_index);
                pivot_idx += 1;
            } else {
                rotate(A, pivot_idx, last_index);
                pivot_idx += 2;
            }

        /* next pivot */
        pivot_value--;
        last_index--;

        /* skip last well placed elements that could have been permuted during the operations */
        while (last_index && (A[last_index] == (last_index+1))) {pivot_value--;last_index--;}
    }
    debug_print("last_index %d\n", last_index);
    return last_index == 0 ? "YES" : "NO";
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> input = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    string result = larrysArray(input);
    if (result == expected) return 0;

    string sinput = array2str(input);
    printf("larrysArray(%s) returned %s but expected %s\n", sinput.c_str(), result.c_str(),
        expected.c_str());
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
