/*
https://leetcode.com/problems/container-with-most-water/

11. Container With Most Water
Medium

Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.



The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.



Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

uint64_t inline getPartitionSum(vector<int> array, int start, int end) {
    uint64_t sum = 0;
    for (int idx = start ; idx < end ; idx ++)
        sum += array[idx];
    return sum;
}

int findSplitLowIndex(vector<int> array, int start, int end, uint64_t partition_sum)
{
    int middle, m0 = -1;
    /* Check if there is enough space to split into 2 partitions */
    if (start > (end-1)) return -1;
    /* Check if the total sum is even */
    if (partition_sum % 2) return -1;

    middle = (start + end) / 2;
    uint64_t left_sum = partition_sum - getPartitionSum(array, middle+1, end+1);
    uint64_t target_sum = partition_sum / 2;

    while ((start < end) and (middle != m0))
    {
        debug_print("findSplitLowIndex sml(%d, %d, %d) left_sum %ld\n", start, middle, end, left_sum);
        if(left_sum == target_sum) return middle;

        m0 = middle;
        if (left_sum > target_sum) {
            end = middle;
            middle = (start + end) / 2;
            left_sum -= getPartitionSum(array, middle+1, m0+1);
        }
        else {
            start = middle;
            middle = (start + end) / 2;
            left_sum += getPartitionSum(array, m0+1, middle+1);
        }
    }
    return -1;
}

int recursiveSplit(vector<int> arr, int start, int end, uint64_t partition_sum, int split_count = 0)
{
    if ( ((start * end) < 0) or (start == end) ) return split_count;
    if (partition_sum == 0) return (end - start);

    int split_low_idx = findSplitLowIndex(arr, start, end, partition_sum);
    debug_print("findSplitLowIndex(%d, %d, %ld) returned %d\n", start, end, partition_sum,
        split_low_idx);
    if (split_low_idx == -1) return split_count;

    /* Divide the sum in 2 and increase split_count to account for this new split */
    partition_sum >>= 1;
    split_count++;
    return max(recursiveSplit(arr, start, split_low_idx, partition_sum, split_count),
        recursiveSplit(arr, split_low_idx+1, end, partition_sum, split_count));
}

int arraySplitting(vector<int> arr) {
    uint64_t partition_sum = 0;

    for (int e : arr)
        partition_sum += e;

    return recursiveSplit(arr, 0, arr.size()-1, partition_sum);
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> x = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    int result = arraySplitting(x);
    if (result == expected) return 0;

    printf("arraySplitting(%s) returned %d but expected %d\n", array2str(x).c_str(), result, expected);
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
