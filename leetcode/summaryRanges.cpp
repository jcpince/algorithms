/*
https://leetcode.com/problems/summary-ranges/

228. Summary Ranges
Medium

Given a sorted integer array without duplicates, return the summary of its ranges.

Example 1:

Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.

Example 2:

Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
*/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if (!nums.size()) return {};

        int left = 0, right = 1, current = nums[0];
        if (nums.size() == 1) return {to_string(current)};

        vector<string> ans;
        while (right < nums.size()) {
            if (nums[right] != current + 1) {
                if (left == (right - 1)) ans.push_back(to_string(current));
                else ans.push_back(to_string(nums[left]) + "->" + to_string(nums[right-1]));
                left = right;
            }
            current = nums[right];
            right++;
        }
        if (left == (right - 1)) ans.push_back(to_string(current));
        else ans.push_back(to_string(nums[left]) + "->" + to_string(nums[right-1]));
        return ans;
    }
};
