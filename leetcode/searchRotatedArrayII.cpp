/*
https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

81. Search in Rotated Sorted Array II
Medium

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).

You are given a target value to search. If found in the array return true, otherwise return false.

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

Follow up:

    This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
    Would this affect the run-time complexity? How and why?
*/

#include <bits/stdc++.h>
#include <climits>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

template <class T>
int findSorted3(vector<T> array, T value, int start, int end)
{
    int middle;
    if (array[start] == value) return start;
    if (array[end] == value) return end;
    if(start == end) return -1;

    while(start < end)
    {
        middle = (start + end) / 2;
        if(array[middle] == value) return middle;
        else if (array[middle] > value) end = middle - 1;
        else start = middle + 1;
    }
    return -1;
}

class Solution {
    int findPivot_logn(vector<int>& nums, int start = 0, int end = -1) {
        if (end == -1) end = nums.size() - 1;
        if (end < 1) return -1;
        //if (nums[end] > nums[start]) return 0;

        int middle = -1, left = start, right = end;
        while (left < right) {
            if (left + 1 == right) return (nums[left] <= nums[right] ? -1 : right);
            middle = left + (right - left) / 2;
            debug_print("lmr(%d, %d, %d)\n", left, middle, right);
            if ((nums[left] > nums[middle])) {
                // strict monotonous right section, the pivot is on the left
                debug_print("Go left\n");
                right = middle;
            } else if ((nums[middle] < nums[right])) {
                // strict monotonous left section, the pivot is on the right
                debug_print("Go right\n");
                left = middle;
            } else {
                // We have potential duplicates on one or both sides
                debug_print("Go both sides\n");
                int res = findPivot_logn(nums, left, middle);
                if (res != -1) return res;
                res = findPivot_logn(nums, middle, right);
                return res;
            }
        }
        return middle;
    }
    int findPivot(vector<int>& nums) {
        if (nums.size() < 2) {
            //printf("findPivot(%s)_uc0 -> -1\n", array2str(nums).c_str());
            return -1;
        }
        if (nums.back() > nums.front()) {
            //printf("findPivot(%s)_uc1 -> 0\n", array2str(nums).c_str());
            return 0;
        }

        int pivot = 0;
        while ((pivot+1) < (int)nums.size() and nums[pivot] <= nums[pivot+1]) pivot++;

        if ((pivot+1) == (int)nums.size() and nums[pivot-2] <= nums[pivot-1]) pivot = -1;

        //printf("findPivot(%s) -> %d\n", array2str(nums).c_str(), pivot+1);
        return pivot+1;
    }

    bool findInRotated(vector<int>& nums, int target, int pivot) {
        if (pivot < 0) pivot = 0; // sorted array
        if (nums[pivot] == target) return true;
        if (nums[pivot] > target) return false;

        int start, end;
        int last = nums.back();
        if (last < target) {
            // target > pivot but also above the last value of the array => between 0 and pivot
            start = 0;
            if (pivot == 0) return false;
            end = pivot-1;
        } else {
            // target > pivot but below the last value of the array => between pivot and end
            start = pivot+1;
            end = nums.size()-1;
        }
        printf("findSorted3(%s. %d, %d, %d)\n", array2str(nums).c_str(), target, start, end);
        return findSorted3(nums, target, start, end) != -1;
    }
public:
    bool search(vector<int>& nums, int target) {
        if (!nums.size()) return false;
        if (nums[0] == target) return true;
        if (nums.size() == 1) return false;
        if (nums.back() == target) return true;

        int pivot = findPivot_logn(nums);
        printf("findPivot_logn(%s) -> %d\n", array2str(nums).c_str(), pivot);
        assert(pivot == findPivot(nums));
        return findInRotated(nums, target, pivot);
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nums"];
    int target = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["target"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    bool result = s.search(nums, target);

    if (result == expected) return 0;

    printf("search(%s, %d) returned %d but expected %d\n", array2str(nums).c_str(), target,
        result, expected);
    dev_assert(continue_on_failure);
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
