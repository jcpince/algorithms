
#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    vector<vector<int>> recPowerSet(vector<int>& prefix, vector<int>& nums) {

        vector<vector<int>> result = { prefix };
        if (nums.size() == 0) return result;
        vector<int>::iterator it;
        for (it = nums.begin() ; it != nums.end() ; it++) {
            prefix.emplace_back(*it);
            vector<int> newset(it+1, nums.end());
            vector<vector<int>> subresult = recPowerSet(prefix, newset);
            result.insert(result.end(), make_move_iterator(subresult.begin()), make_move_iterator(subresult.end()));
            prefix.pop_back();
        }
        return result;
    }
    vector<vector<int>> recPowerSetNoDups(vector<int>& prefix, vector<int>& nums) {

        vector<vector<int>> result = { prefix };
        if (nums.size() == 0) return result;
        vector<int>::iterator it;
        int num0 = nums[0] + 1;
        for (it = nums.begin() ; it != nums.end() ; it++) {
            if (*it == num0) continue;
            prefix.emplace_back(*it);
            vector<int> newset(it+1, nums.end());
            vector<vector<int>> subresult = recPowerSetNoDups(prefix, newset);
            result.insert(result.end(), make_move_iterator(subresult.begin()), make_move_iterator(subresult.end()));
            prefix.pop_back();
            num0 = *it;
        }
        return result;
    }
    void recPowerSetNoDups2(vector<int>& prefix, vector<int>& nums, vector<vector<int>>& result) {

        result.emplace_back(prefix);
        if (nums.size() == 0) return;
        vector<int>::iterator it;
        int num0 = nums[0] + 1;
        for (it = nums.begin() ; it != nums.end() ; it++) {
            if (*it == num0) continue;
            prefix.emplace_back(*it);
            vector<int> newset(it+1, nums.end());
            recPowerSetNoDups2(prefix, newset, result);
            prefix.pop_back();
            num0 = *it;
        }
    }
    void recPowerSetNoDups3(vector<int>& prefix, vector<int>& nums, vector<vector<int>>& result, size_t index = 0) {

        result.emplace_back(prefix);
        if (index == nums.size()) return;
        int num0 = nums[index] + 1;
        for ( ; index < nums.size() ; index++) {
            if (nums[index] == num0) continue;
            prefix.emplace_back(nums[index]);
            recPowerSetNoDups3(prefix, nums, result, index+1);
            prefix.pop_back();
            num0 = nums[index];
        }
    }
    void recPowerSetNoDups4(vector<int>& prefix, vector<int>& nums, vector<vector<int>>& result, size_t index = 0) {

        result.emplace_back(prefix);
        if (index == nums.size()) return;
        int num0 = nums[index] + 1;
        prefix.emplace_back(-1);
        for ( ; index < nums.size() ; index++) {
            if (nums[index] == num0) continue;
            prefix.back() = nums[index];
            recPowerSetNoDups4(prefix, nums, result, index+1);
            num0 = nums[index];
        }
        prefix.pop_back();
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {

        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        result.reserve(pow(2,nums.size()));
        vector<int> prefix = {};
        //recPowerSetNoDups3(prefix, nums, result);
        recPowerSetNoDups4(prefix, nums, result);
        return result;
        //return recPowerSetNoDups(prefix, nums);
    }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        vector<vector<int>> result = s.subsetsWithDup(nums);

        if (result == expected) return 0;

        printf("subsetsWithDup(%s) returned %s but expected %s\n",
                array2str(nums).c_str(), array2str(result).c_str(),
                array2str(expected).c_str());
        assert(continue_on_failure);
        return 1;
}
