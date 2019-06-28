/*
https://www.hackerrank.com/challenges/missing-numbers/problem

Numeros the Artist had two lists that were permutations of one another. He was very proud.
Unfortunately, while transporting them from one exhibition to another, some numbers were lost out
of the first list. Can you find the missing numbers?

As an example, the array with some numbers missing,
. The original array of numbers . The numbers missing are

.

Notes

    If a number occurs multiple times in the lists, you must ensure that the frequency of that
    number in both lists is the same. If that is not the case, then it is also a missing number.
    You have to print all the missing numbers in ascending order.
    Print each missing number once, even if it is missing multiple times.
    The difference between maximum and minimum number in the second list is less than or equal to

    .

Function Description

Complete the missingNumbers function in the editor below. It should return a sorted array of
missing numbers.

missingNumbers has the following parameter(s):

    arr: the array with missing numbers
    brr: the original array of numbers

Input Format

There will be four lines of input:

- the size of the first list,
The next line contains space-separated integers
- the size of the second list,
The next line contains space-separated integers

Constraints

Output Format

Output the missing numbers in ascending order.

Sample Input

10
203 204 205 206 207 208 203 204 205 206
13
203 204 204 205 206 207 205 208 203 206 205 206 204

Sample Output

204 205 206

Explanation

is present in both arrays. Its frequency in is , while its frequency in is . Similarly, and occur
twice in , but three times in . The rest of the numbers have the same frequencies in both lists.

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

vector<int> missingNumbers(vector<int> small, vector<int> big) {

    if (small.size() == big.size()) return {};
    sort(small.begin(), small.end());
    sort(big.begin(), big.end());

    vector<int> missing;
    size_t idx = 0, jdx = 0;
    int last_missing = big.front() - 1;
    for ( ; idx < big.size() && jdx < small.size() ; idx++) {
        if (big[idx] == small[jdx]) jdx++;
        else if (big[idx] != last_missing) {
            last_missing = big[idx];
            missing.push_back(last_missing);
        }
    }

    for ( ; idx < big.size() ; idx++) {
        if (big[idx] != last_missing) {
            last_missing = big[idx];
            missing.push_back(last_missing);
        }
    }
    return missing;
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> arr = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["arr"];
    vector<int> brr = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["brr"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<int> result = missingNumbers(arr, brr);
    if (check_result(result, expected)) return 0;

    printf("missingNumbers(%s, %s) returned %s but expected %s\n", array2str(arr).c_str(),
        array2str(brr).c_str(), array2str(result).c_str(), array2str(expected).c_str());
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
