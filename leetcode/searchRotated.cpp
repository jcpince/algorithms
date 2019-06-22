/*
33. Search in Rotated Sorted Array
Medium

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>
#include <climits>
#include <vector>

using namespace std;

class Solution {
    int recursive(vector<int>& nums, int target, int start, int end)
    {
        if (nums[start] == target) return start;
        if (nums[end] == target) return end;
        if (start >= (end - 1)) return -1;

        int median = start + (end - start) / 2;
        if (nums[median] == target) return median;

        if (nums[median] < nums[end])
        {
            /* 2nd half is contiguous */
            //printf("2nd half contiguous: Looking at indices %d(%d), %d(%d), %d(%d)\n", start, nums[start], median, nums[median], end, nums[end]);
            if ((nums[median] < target) && (nums[end] > target))
            {
                start = median;
                end--;
            }
            else
            {
                end = median;
                start++;
            }
        }
        else
        {
            /* 2nd half is split, first half is contiguous */
            //assert(nums[start] < nums[median]);
            //printf("1st half contiguous: Looking at indices %d(%d), %d(%d), %d(%d)\n", start, nums[start], median, nums[median], end, nums[end]);
            if ((nums[median] > target) && (nums[start] < target))
            {
                end = median;
                start++;
            } else
            {
                start = median;
                end--;
            }
        }
        //printf("Calling recursive(%d, %d)\n", start, end);
        return recursive(nums, target, start, end);
    }
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 0) return -1;
        if (nums.size() == 1) return nums[0] == target ? 0 : -1;
        //cout << "Searching for " << target << " in nums" << endl;
        int res = recursive(nums, target, 0, nums.size()-1);
        //printf("returns %d\n", res);
        return res;
    }
};

int main(int argc, char **argv)
{
    Solution s;

    vector<int> nums;

    nums = {4,5,6,7,0,1,2};
    assert(s.search(nums, 1) == 5);

    nums = {4,5,6,7,8,9,0,1,2};
    assert(s.search(nums, 0) == 6);

    nums = {4,5,6,7,8,9,0,1,2};
    assert(s.search(nums, 9) == 5);

    nums = {4,5,6,7,0,1,2};
    assert(s.search(nums, 3) == -1);

    nums = {0,1,2,4,5,6,7};
    assert(s.search(nums, 0) == 0);

    nums = {1,2,4,5,6,7,0};
    assert(s.search(nums, 0) == 6);

    nums = {};
    assert(s.search(nums, 0) == -1);

    nums = {1};
    assert(s.search(nums, 1) == 0);

    nums = {1};
    assert(s.search(nums, 2) == -1);

    cout << "All tests succeeded" << endl;
    return 0;
}
