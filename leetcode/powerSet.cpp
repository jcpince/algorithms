#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    void powerSet(vector<int>& nums, vector<vector<int>>& ps, vector<int>& current, int index) {
        if (index == (int)nums.size()) return;

        /* skip the next index */
        powerSet(nums, ps, current, index + 1);
        current.push_back(nums[index]);
        ps.push_back(current);
        powerSet(nums, ps, current, index + 1);
        current.pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ps = {{}};
        vector<int> tmp;
        powerSet(nums, ps, tmp, 0);
        return ps;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.subsets(nums);

    if (check_result(result, expected)) return 0;

    printf("powerSet(%s) returned %s but expected %s\n", array2str(nums).c_str(),
        array2str(result).c_str(), array2str(expected).c_str());
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
