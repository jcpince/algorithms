/*
18. 4Sum
Medium

Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    void testSubsets4(const vector<int> &x, const int &tsum, vector<vector<int>> &solutions,
        int curr_sol0 = 0, int curr_sol1 = 0, int curr_sol2 = 0, int curr_sol3 = 0, int curr_sum = 0,
        size_t curr_size = 0, size_t curr_idx = 0)
    {
        /* stop conditions */
        if ((curr_sum > tsum) and (curr_idx < x.size()) and (x[curr_idx] > 0)) return;
        if (curr_size == 4) {
            if (curr_sum == tsum) {
                // printf("solutions.push_back([%d, %d, %d, %d])\n",
                //     curr_sol0, curr_sol1, curr_sol2, curr_sol3);
                solutions.push_back({curr_sol0, curr_sol1, curr_sol2, curr_sol3});
            }
            return;
        }
        if (curr_idx < x.size()) {
            switch (curr_size)
            {
                case 0: curr_sol0 = x[curr_idx];break;
                case 1: curr_sol1 = x[curr_idx];break;
                case 2: curr_sol2 = x[curr_idx];break;
                case 3: curr_sol3 = x[curr_idx];break;
                default: assert(false);
            }
            //printf("Set curr_sol[%ld] to %d)\n", curr_size, x[curr_idx]);
            testSubsets4(x, tsum, solutions, curr_sol0, curr_sol1, curr_sol2, curr_sol3,
                    curr_sum + x[curr_idx], curr_size + 1, curr_idx + 1);
            /* skip the current and the nexts if they are the same as the current */
            while ((curr_idx < x.size()-1) and (x[curr_idx] == x[curr_idx+1])) curr_idx++;
            testSubsets4(x, tsum, solutions, curr_sol0, curr_sol1, curr_sol2, curr_sol3,
                    curr_sum, curr_size, curr_idx + 1);
        }
    }
public:
    vector<vector<int>> fourSum2(vector<int>& nums, int target) {
        if (nums.size() < 4) return {};
        sort(nums.begin(), nums.end());
        /* Check if the sum of the 4 max elements is above the target */
        vector<int>::iterator it = nums.end() - 1;
        int s = 0;
        for (int idx = 0 ; idx < 4 ; idx++)
            s += *it;
        if (s < target) return {};
        vector<vector<int>> solutions;
        testSubsets4(nums, target, solutions);
        return solutions;
    }

    /* based on 3Sum with a pivot and left and right cursors but with 2 pivots this time */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int elems_count = nums.size();
        if (elems_count < 4) return {};
        sort(nums.begin(), nums.end());

        /* Check if the sum of the 4 max elements is above the target */
        vector<int>::iterator it = nums.end() - 1;
        int s = 0;
        for (int idx = 0 ; idx < 4 ; idx++)
            s += *it;
        if (s < target) return {};

        vector<vector<int>> result;
        for (int pivot1_idx = 0 ; pivot1_idx < elems_count - 3 ; pivot1_idx++)
        {
            /* Skip the next pivot if identical to the previous */
            int pivot1_value = vectorat(nums, pivot1_idx);
            if ((pivot1_idx > 0) and
                (vectorat(nums, pivot1_idx - 1) == pivot1_value)) continue;

            for (int pivot2_idx = pivot1_idx + 1 ; pivot2_idx < elems_count - 2 ; pivot2_idx++)
            {
                int small_idx = pivot2_idx + 1, large_idx = elems_count - 1;
                int pivot2_value = vectorat(nums, pivot2_idx);
                if ( ( (pivot1_value + pivot2_value) > target) and (pivot2_value > 0) ) break;
                if ((pivot2_idx != pivot1_idx + 1) and (pivot2_value == vectorat(nums, pivot2_idx - 1))) continue;

                while (small_idx < large_idx)
                {
                    int small_value = vectorat(nums, small_idx);

                    /* if n1 + n2 + n3 > 0, n3 is > 0 and n4 will be as well => break */
                    int sum = pivot1_value + pivot2_value + small_value;
                    if ((sum > target) and (small_value > 0)) break;

                    int large_value = vectorat(nums, large_idx);
                    sum += large_value;

                    if (sum > target) large_idx--;
                    else if (sum < target) small_idx++;
                    else {
                        /* Found a solution, store it */
                        result.push_back({pivot1_value, pivot2_value, small_value, large_value});

                        /* move forward and skip duplicates */
                        do {
                            small_idx++;
                            if (small_idx >= large_idx) break;
                        } while (vectorat(nums, small_idx) == vectorat(nums, small_idx - 1));

                        do
                        {
                            large_idx--;
                            if (small_idx >= large_idx) break;
                        } while (vectorat(nums, large_idx) == vectorat(nums, large_idx + 1));
                    }
                }
            }
        }
        return result;
    }

    vector<vector<int>> fourSum3(vector<int>& nums, int target) {
        vector<vector<int>> total;
        int n = nums.size();
        if(n<4)  return total;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n-3;i++)
        {
            if(i>0&&nums[i]==nums[i-1]) continue;
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3]>target) break;
            if(nums[i]+nums[n-3]+nums[n-2]+nums[n-1]<target) continue;
            for(int j=i+1;j<n-2;j++)
            {
                if(j>i+1&&nums[j]==nums[j-1]) continue;
                if(nums[i]+nums[j]+nums[j+1]+nums[j+2]>target) break;
                if(nums[i]+nums[j]+nums[n-2]+nums[n-1]<target) continue;
                int left=j+1,right=n-1;
                while(left<right){
                    int sum=nums[left]+nums[right]+nums[i]+nums[j];
                    if(sum<target) left++;
                    else if(sum>target) right--;
                    else{
                        total.push_back({nums[i],nums[j],nums[left],nums[right]});
                        do{left++;}while(nums[left]==nums[left-1]&&left<right);

                        do{right--;}while(nums[right]==nums[right+1]&&left<right);
                    }
                }
            }
        }
        return total;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> x = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["x"];
    int target = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["target"];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
    if ((expected.size() == 1) and (expected[0].size() == 0)) expected = {};

    Solution s;
    vector<vector<int>> result = s.fourSum(x, target);
    if (check_result(result, expected)) return 0;

    printf("fourSum(%s, %d) returned %s but expected %s\n", array2str(x).c_str(), target,
        array2str(result).c_str(), array2str(expected).c_str());
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
