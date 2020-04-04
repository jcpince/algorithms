#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
        int find_index(const vector<int>& nums, const int &target) {

                uint32_t lower = 0, upper = (int)nums.size()-1, middle = upper / 2;

                /* Don't even look if not necessary */
                if (nums[lower] == target) return lower;
                if (nums[upper] == target) return upper;

                while (lower+1 < upper) {
                        if (nums[middle] == target) return middle;
                        else if (nums[middle] > target) {
                                upper = middle;
                        } else lower = middle;
                        middle = lower + (upper - lower) / 2;
                }
                return nums[middle] == target ? middle : -1;
        }
public:
        vector<int> searchRange(const vector<int>& nums, const int &target) {

                int start = -1, end = -1, index;
                const uint32_t size = nums.size();

                if (size && (index = find_index(nums, target)) >= 0) {
                        start = end = index;
                        while (start > 0 && nums[start-1] == target)
                                start--;
                        while (end < (int)size-1 && nums[end+1] == target)
                                end++;
                }

                return {start, end};
        }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nums"];
    int target = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["target"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<int> result = s.searchRange(nums, target);

    if (result == expected) return 0;

    printf("searchRange(%s, %d) returned %s but expected %s\n",
        array2str(nums).c_str(), target,
        array2str(result).c_str(), array2str(expected).c_str());
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
