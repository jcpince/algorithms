#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {

public:
        TreeNode* bstFromPreorder(vector<int>& preorder) {

                TreeNode *root = NULL, *node, *ancestor = NULL;
                queue<TreeNode*> q;
                for ( int val : preorder) {
                        node = new TreeNode(val);
                        if (!root) {
                                root = node;
                                q.push(root);
                                ancestor = root;
                                continue;
                        }
                        if (ancestor->val > val) {
                                printf("Set node(%d)->left with %d\n", ancestor->val, node->val);
                                ancestor->left = node;
                        }
                        else {
                                ancestor = NULL;
                                while (!q.empty()) {
                                        TreeNode *current = q.front();
                                        q.pop();
                                        if (current->val > val) break;
                                        ancestor = current;
                                }
                                assert(ancestor || !root->right);
                                printf("Set node(%d)->right with %d\n", ancestor->val, node->val);
                                ancestor->right = node;
                        }
                        ancestor = node;
                        q.push(ancestor);
                }

                return root;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        TreeNode *result = s.bstFromPreorder(nums);
        vector<int> vresult = tree2vector(result);
        deleteDynTree(result);

        if (check_result(vresult, expected)) return 0;

        printf("bstFromPreorder(%s) returned %s but expected %s\n",
                array2str(nums).c_str(), array2str(vresult).c_str(),
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
