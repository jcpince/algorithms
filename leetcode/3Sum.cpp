// 15. 3Sum
// Medium
//
// Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
//
// Note:
//
// The solution set must not contain duplicate triplets.
//
// Example:
//
// Given array nums = [-1, 0, 1, 2, -1, -4],
//
// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]

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

const bool continue_on_failure = true;

class Solution {
public:
    /* Solution n*(n-1)/2* log(n) => n^2 * log(n) */
    vector<vector<int>> threeSum_nsquare_logn(vector<int>& nums) {
        if (nums.size() < 3) return {};

        vector<vector<int>> results;
        sort(nums.begin(), nums.end());

        debug_print("Sorted array is %s\n", array2str(nums).c_str());

        int smallest = nums.front(), biggest = nums.back();
        int end_idx = nums.size() - 1;

        int first0 = smallest - 1;

        for (int idx1 = 0 ; idx1 < end_idx-1 ; idx1++)
        {
            int first = vectorat(nums, idx1), second0 = first0;
            if (first == first0) continue;
            if (first > 0) break;
            first0 = first;

            int found0 = end_idx+1, found0_below = -1;
            for (int idx2 = idx1 + 1 ; (idx2 < end_idx) && (found0 > 0) ; idx2++)
            {
                update_iterations();
                int second = vectorat(nums, idx2);
                if (second == second0) continue;
                if ((first + second) > 0) break;
                second0 = second;

                int third = 0 - first - second;
                if (third < smallest || third > biggest) continue;

                debug_print("Candidate (%d, %d, %d) - search %d between %d and %d\n",
                    first, second, third, third, idx2+1, found0-1);
                int found = find_element_or_below(nums, third, idx2+1, found0-1, found0_below);

                debug_print("Here third is %d, idx1(%d), idx2(%d), found0(%d) => %d\n", third, idx1,
                 idx2, found0, found);
                if (found != -1)
                {
                    debug_print("Found is %d, Insert %d, %d, %d\n", found, first, second, third);
                    dev_assert(found < found0);
                    results.push_back({first, second, third});
                    found0 = found;
                }
                else if (found0_below != -1) found0 = found0_below + 1;
            }
        }
        print_iterations_count();
        return results;
    }

    /* Solution n*n (discounting the duplicates skipping) */
    vector<vector<int>> threeSum(vector<int>& nums) {
        int elems_count = nums.size();
        if (elems_count < 3) return {};

        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        reset_iteration();

        for (int pivot_idx = 0 ; pivot_idx < elems_count - 2 ; pivot_idx++)
        {
            /* Skip the next pivot if identical to the previous */
            int pivot_value = vectorat(nums, pivot_idx);
            if ((pivot_idx > 0) and
                (vectorat(nums, pivot_idx - 1) == pivot_value)) continue;

            /* if the pivot is > 0, there's no sum == 0 remaining */
            if (pivot_value > 0) break;

            int small_idx = pivot_idx + 1, large_idx = elems_count - 1;
            while (small_idx < large_idx)
            {
                update_iterations();
                int small_value = vectorat(nums, small_idx);

                /* if n1 + n2 > 0, n2 is > 0 and n3 will be as well => break */
                int sum = pivot_value + small_value;
                if (sum > 0) break;

                int large_value = vectorat(nums, large_idx);
                sum += large_value;

                if (sum > 0) large_idx--;
                else if (sum < 0) small_idx++;
                else {
                    /* Found a solution, store it */
                    result.push_back({pivot_value, small_value, large_value});

                    /* move forward and skip duplicates */
                    do {
                        update_iterations();
                        small_idx++;
                        if (small_idx >= large_idx) break;
                    } while (vectorat(nums, small_idx) == vectorat(nums, small_idx - 1));

                    do
                    {
                        update_iterations();
                        large_idx--;
                        if (small_idx >= large_idx) break;
                    } while (vectorat(nums, large_idx) == vectorat(nums, large_idx + 1));
                }
            }
        }
        print_iterations_count();
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    vector<int> in = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<vector<int>> result = ((Solution *)_s)->threeSum(in);
    debug_print("Found %ld solutions\n", result.size());
    if (check_result(result, expected)) return 0;

    string sin = array2str(in), sout = array2str(result), sexp = array2str(expected);
    printf("threeSum(%s) returned %s but expected %s\n", sin.c_str(), sout.c_str(), sexp.c_str());
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
