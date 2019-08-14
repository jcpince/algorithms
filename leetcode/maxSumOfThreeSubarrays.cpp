/*
https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/

689. Maximum Sum of 3 Non-Overlapping Subarrays
Hard

In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.

Return the result as a list of indices representing the starting position of each interval
(0-indexed). If there are multiple answers, return the lexicographically smallest one.

Example:

Input: [1,2,1,2,6,7,5,1], 2
Output: [0, 3, 5]
Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

Note:

    nums.length will be between 1 and 20000.
    nums[i] will be between 1 and 65535.
    k will be between 1 and floor(nums.length / 3).
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    typedef struct {
        size_t      best_left_index;
        size_t      best_right_index;
        int32_t     sum;
        uint32_t    padding;
    } index_info_t;
    vector<index_info_t> info;

    int inline subarray_sum(vector<int>& nums, int offset, int width) {
        int sum = 0;
        for (int idx = offset ; idx < offset+width ; idx++)
            sum += nums[idx];
        //printf("Subarray(%s, %d, %d) => %d\n", array2str(nums).c_str(), offset, width, sum);
        return sum;
    }
    void build_sums(vector<int>& nums, int width) {
        int sum = 0, e0 = nums[0];
        for (int idx = 0 ; idx < width ; idx++)
            sum += nums[idx];
        nums[0] = sum;
        for (size_t idx = 1 ; idx < (nums.size() - width + 1) ; idx++) {
            sum += nums[idx + width - 1] - e0;
            e0 = nums[idx];
            nums[idx] = sum;
        }
        nums.resize(nums.size() - width + 1);
    }
    void preprocess_nums(vector<int>& nums, int width) {

        info = vector<index_info_t>(nums.size() - width + 1);

        //printf("Starts preprocessing -- info(%ld)\n", info.size());
        /* Compute the sums */
        int sum = 0;
        for (int idx = 0 ; idx < width ; idx++)
            sum += nums[idx];
        info[0].sum = sum;
        for (size_t idx = 1 ; idx < info.size() ; idx++) {
            sum += nums[idx + width - 1] - nums[idx - 1];
            info[idx].sum = sum;
        }

        /* Compute the best indices right and left */
        int best_left_idx = 0, best_right_idx = info.size() - 1;
        int best_left_sum = info[best_left_idx].sum;
        int best_right_sum = info[best_right_idx].sum;
        for (size_t off = width ; off < info.size() ; off++) {
            size_t right_off = info.size() - off - 1;

            //printf("Check best left with index %ld for off %ld\n", off - width, off);
            sum = info[off - width].sum;
            if (sum > best_left_sum) {
                best_left_sum = sum;
                best_left_idx = off - width;
            }
            info[off].best_left_index = best_left_idx;

            sum = info[right_off + width].sum;
            if (sum >= best_right_sum) {
                best_right_sum = sum;
                best_right_idx = right_off + width;
            }
            info[right_off].best_right_index = best_right_idx;
        }

        // for (size_t off = 0 ; off < info.size() ; off++)
        //     printf("info[%ld] = {%d, %ld, %ld}\n", off, info[off].sum, info[off].best_left_index,
        //         info[off].best_right_index);
    }
public:
    vector<int> maxSumOfThreeSubarrays2(vector<int>& nums, int width) {
        int maxSum = 0, isum = subarray_sum(nums, 0, width), jsum, ksum;
        size_t i, j, k;
        vector<int> result(3, 0);
        for (i = width-1 ; i < (nums.size() - (2 * width)) ; i++) {
            jsum = subarray_sum(nums, i + 1, width);
            for (j = i + width ; j < (nums.size() - width) ; j++) {
                ksum = subarray_sum(nums, j + 1, width);
                for (k = j + width ; k < nums.size() ; k++) {
                    //printf("i(%ld - %2d) -- j(%ld - %2d) -- k(%2ld - %2d) ==> %d\n",
                    //    i-width+1, isum, j-width+1, jsum, k-width+1, ksum, (isum + jsum + ksum));
                    if ((isum + jsum + ksum) > maxSum) {
                        result[0] = i-width+1;
                        result[1] = j-width+1;
                        result[2] = k-width+1;
                        maxSum = isum + jsum + ksum;
                    }
                    if ((k+1) < nums.size())
                        ksum += nums[k+1] - nums[k-width+1];
                }
                jsum += nums[j+1] - nums[j-width+1];
            }
            isum += nums[i+1] - nums[i-width+1];
        }
        return result;
    }
    vector<int> maxSumOfThreeSubarrays3(vector<int>& nums, int width) {
        printf("Array(%s)\n", array2str(nums).c_str());
        int maxSum = 0;
        size_t i, j, k, ns = nums.size();
        vector<int> result(3, 0);

        build_sums(nums, width);
        printf("SumArray(%s)\n", array2str(nums).c_str());

        for (i = 0 ; i < (ns + 1 - (3 * width)) ; i++) {
            //printf("i: %d\n", i);
            for (j = i + width ; j < (ns + 1 - (2 * width)) ; j++) {
                //printf("j: %d\n", j);
                for (k = j + width ; k < (ns + 1 - width) ; k++) {
                    //printf("k: %d\n", k);
                    if ((nums[i] + nums[j] + nums[k]) > maxSum) {
                        result[0] = i;
                        result[1] = j;
                        result[2] = k;
                        maxSum = nums[i] + nums[j] + nums[k];
                    }
                }
            }
        }
        return result;
    }
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int width) {
        //printf("Array(%s), width %d\n", array2str(nums).c_str(), width);
        int maxSum = INT_MIN;
        size_t left, middle, right, ns = nums.size() - 2 * width + 1;

        preprocess_nums(nums, width);

        for (size_t idx = width ; idx < ns ; idx++) {
            int cur_sum = info[idx].sum + info[info[idx].best_left_index].sum +
                    info[info[idx].best_right_index].sum;
            if (cur_sum > maxSum) {
                maxSum = cur_sum;
                left = info[idx].best_left_index;
                middle = idx;
                right = info[idx].best_right_index;
            }
        }
        return {(int)left, (int)middle, (int)right};
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nums"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<int> result = s.maxSumOfThreeSubarrays(nums, k);

    if (check_result(result, expected)) return 0;

    printf("maxSumOfThreeSubarrays(%s, %d) returned %s but expected %s\n", array2str(nums).c_str(),
        k, array2str(result).c_str(), array2str(expected).c_str());
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
