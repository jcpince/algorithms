/*
46. Permutations
Medium

Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
[1,2,3],
[1,3,2],
[2,1,3],
[2,3,1],
[3,1,2],
[3,2,1]
]
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
        void inline swap(vector<int>& nums, int i0, int i1) {
                int tmp = nums[i0];
                nums[i0] = nums[i1];
                nums[i1] = tmp;
        }
        void permute(vector<vector<int>> &result, vector<int>& nums, int pivot,
                        const int nb_nums) {
                if (pivot == 1) {
                        result.push_back(nums);
                        return;
                }
                for (int i = 0 ; i < pivot ; i++) {
                        permute(result, nums, pivot - 1, nb_nums);
                        if (pivot&1) //odd
                                swap(nums, i, pivot-1);
                        else // even
                                swap(nums, 0, pivot-1);
                }
        }
public:
        vector<vector<int>> permute(vector<int>& nums) {
                int nb_nums = nums.size();

                if (nb_nums < 2) return {nums};

                vector<vector<int>> result;
                permute(result, nums, nb_nums, nb_nums);

                return result;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        vector<vector<int>> result = s.permute(nums);

        if (result == expected) return 0;

        printf("permute(%s) returned %s but expected %s\n",
                array2str(nums).c_str(), array2str(result).c_str(),
                array2str(expected).c_str());
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
