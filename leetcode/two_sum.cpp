/*
1. Two Sum
Easy

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

Example:

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

*/

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        vector<int> result = {0, 1};
        for (vector<int>::iterator it = nums.begin() ; it != nums.end() ; it++)
        {
            int diff = target - *it;
            vector<int>::iterator it2 = find(it+1, nums.end(), diff);
            if (it2 != nums.end())
            {
                result[1] = distance(nums.begin(), it2);
                break;
            }
            result[0]++;
        }
        cout << "returns [" << result[0] << ", " << result[1] << "]" << endl;
        return result;
    }
};

int main(int argc, char **argv)
{
    Solution s;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = s.twoSum(nums, target);
    assert((result.size() == 2) && (nums[result[0]] + nums[result[1]]) == target);

    nums = {3, 2, 4};
    target = 6;
    result = s.twoSum(nums, target);
    assert((result.size() == 2) && (nums[result[0]] + nums[result[1]]) == target);

    cout << "All tests succeeded" << endl;
    return 0;
}
