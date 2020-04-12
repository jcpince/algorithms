#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
        int treeDepth(TreeNode* root, int &diameter) {
                int left = root->left ? 1 + treeDepth(root->left, diameter) : 0;
                int right = root->right ? 1 + treeDepth(root->right, diameter) : 0;
                if (left+right > diameter) diameter = left+right;
                return left > right ? left : right;
        }
public:
        int diameterOfBinaryTree(TreeNode* root) {
                if (!root) return 0;
                int diameter = 0;
                treeDepth(root, diameter);
                return diameter;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        struct TreeNode tree[vtree.size()], *ptree = NULL;
        if (vtree.size()) {
                bzero(tree, vtree.size()*sizeof(struct TreeNode));
                vector2tree(vtree, tree);
                ptree = tree;
        }

        Solution s;
        int result = s.diameterOfBinaryTree(ptree);

        if (result == expected) return 0;

        printf("diameterOfBinaryTree(%s) returned %d but expected %d\n",
                array2str(vtree).c_str(), result, expected);
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
