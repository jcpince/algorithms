#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    void maxBT(vector<int>& nums, TreeNode* root, bool isleft, size_t i0, size_t i1) {
        //printf("maxBT(%p, %d, %ld, %ld)\n", (void*)root, isleft, i0, i1);
        if (i0 > i1) return;

        if (i0 == i1) {
            if (isleft) root->left = new TreeNode(nums[i0]);
            else root->right = new TreeNode(nums[i0]);
            return;
        }

        size_t maxidx = maxIndex(nums, i0, i1);
        TreeNode* node = new TreeNode(nums[maxidx]);
        if (isleft) root->left = node;
        else root->right = node;
        if (maxidx) maxBT(nums, node, true, i0, maxidx-1);
        maxBT(nums, node, false, maxidx+1, i1);
    }
    static inline size_t maxIndex(vector<int>& nums, size_t i0, size_t i1) {
        //printf("maxIndex(%s, %ld, %ld)", array2str(nums).c_str(), i0, i1);
        size_t maxidx = i0;
        int max = nums[i0++];
        for ( ; i0 <= i1 ; i0++)
            if (nums[i0] > max) {
                max = nums[i0];
                maxidx = i0;
            }
        //printf(" returns %ld\n", maxidx);
        return maxidx;
    }
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.size() == 0) return NULL;

        size_t maxidx = maxIndex(nums, 0, nums.size()-1);
        TreeNode* root = new TreeNode(nums[maxidx]);
        if (maxidx) maxBT(nums, root, true, 0, maxidx-1);
        maxBT(nums, root, false, maxidx+1, nums.size()-1);
        return root;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    TreeNode *result = s.constructMaximumBinaryTree(nums);
    vector<int> vresult = tree2vector(result);
    deleteDynTree(result);

    if (check_result(vresult, expected)) return 0;

    printf("constructMaximumBinaryTree(%s) returned %s but expected %s\n", array2str(nums).c_str(),
        array2str(vresult).c_str(), array2str(expected).c_str());
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
