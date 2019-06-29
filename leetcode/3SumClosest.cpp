/*
https://leetcode.com/problems/3sum-closest/

16. 3Sum Closest
Medium

Given an array nums of n integers and an integer target, find three integers in nums such that the
sum is closest to target. Return the sum of the three integers. You may assume that each input
would have exactly one solution.

Example:

Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

void testSubsets3(const vector<int> &x, const int &tsum, int &best_sum, int curr_sum = 0,
    size_t curr_size = 0, size_t curr_idx = 0)
{
    /* stop conditions */
    int cur_delta = abs(tsum - curr_sum), best_delta = abs(tsum - best_sum);
    printf("best_sum(%d), cur_delta(%d), best_delta(%d), curr_size(%d)\n", best_sum, cur_delta,
        best_delta, curr_size);
    if (curr_size == 3) {
        if (cur_delta < best_delta) {
            printf("Set best sum to %d\n", curr_sum);
            best_sum = curr_sum;
        }
        return;
    }
    if (curr_idx < x.size()) {
        testSubsets3(x, tsum, best_sum, curr_sum + x[curr_idx], curr_size + 1, curr_idx + 1);
        testSubsets3(x, tsum, best_sum, curr_sum, curr_size, curr_idx + 1);
    }
}

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            int res = 0;
            for (size_t idx = 0 ; idx < nums.size() ; idx++)
                res += nums[idx];
            return res;
        }
        sort(nums.begin(), nums.end());
        int best_sum = nums[0] + nums[1] + nums[2];
        testSubsets3(nums, target, best_sum);
        return best_sum;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nums"];
    int target = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["target"];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.threeSumClosest(nums, target);
    if (result == expected) return 0;

    printf("threeSumClosest(%s, %d) returned %d but expected %d\n", array2str(nums).c_str(), target,
        result, expected);
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
