/*
https://leetcode.com/problems/degree-of-an-array/

697. Degree of an Array
Easy

Given a non-empty array of non-negative integers nums, the degree of this array is defined as the
maximum frequency of any one of its elements.

Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the
same degree as nums.

Example 1:

Input: [1, 2, 2, 3, 1]
Output: 2
Explanation:
The input array has a degree of 2 because both elements 1 and 2 appear twice.
Of the subarrays that have the same degree:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
The shortest length is 2. So return 2.

Example 2:

Input: [1,2,2,3,1,4,2]
Output: 6

Note:
nums.length will be between 1 and 50,000.
nums[i] will be an integer between 0 and 49,999.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

typedef struct {
    uint16_t occurrences;
    uint16_t first_index;
    uint16_t last_index;
} freqency_t;

class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        freqency_t occurrences[50000] = {{0,0,0}};
        int index = 0;
        for ( int num: nums) {
            if (!occurrences[num].occurrences) occurrences[num].first_index = index;
            occurrences[num].occurrences++;
            occurrences[num].last_index = index;
            index++;
        }

        /* Now, find the max */
        int max_occurrences = 0, min_range = INT_MAX;
        for ( index = 0 ; index < 50000 ; index++) {
            if (occurrences[index].occurrences > max_occurrences) {
                min_range = occurrences[index].last_index - occurrences[index].first_index + 1;
                max_occurrences = occurrences[index].occurrences;
            } else if (occurrences[index].occurrences == max_occurrences) {
                int range = occurrences[index].last_index - occurrences[index].first_index + 1;
                if (range < min_range) min_range = range;
            }
        }
        return min_range;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.findShortestSubArray(nums);

    if (result == expected) return 0;

    printf("findShortestSubArray(%s) returned %d but expected %d\n", array2str(nums).c_str(),
        result, expected);
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
