/*
35. Search Insert Position
Easy

1347

181

Favorite

Share
Given a sorted array and a target value, return the index if the target is found. If not,
return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Example 1:

Input: [1,3,5,6], 5
Output: 2
Example 2:

Input: [1,3,5,6], 2
Output: 1
Example 3:

Input: [1,3,5,6], 7
Output: 4
Example 4:

Input: [1,3,5,6], 0
Output: 0
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int below_idx = 0;
        int found_idx = find_element_or_below(nums, target, 0, nums.size()-1, below_idx);

        if (found_idx != -1) return found_idx;
        if (below_idx != -1) return below_idx+1;
        else return 0;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nums"];
    int target = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["target"];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    int result = ((Solution *)_s)->searchInsert(nums, target);
    if (result == expected) return 0;

    string sin = array2str(nums);
    printf("searchInsert(%s, %d) returned %d but expected %d\n", sin.c_str(), target, result,
        expected);
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
