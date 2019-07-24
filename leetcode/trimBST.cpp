#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    TreeNode* findChildInRange(TreeNode* root, int L, int R) {
        TreeNode* child = root;
        while (child and (child->val < L or child->val > R)) {
            //printf("Child(%d) out of range (%d, %d)\n", child->val, L, R);
            if (child->val < L) child = child->right;
            else child = child->left;
        }
        return child;
    }
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        TreeNode* newroot = findChildInRange(root, L, R);
        if (newroot) {
            vector<TreeNode*> to_visit = {newroot};
            while (to_visit.size()) {
                TreeNode* node = to_visit.back();
                to_visit.pop_back();
                node->left = findChildInRange(node->left, L, R);
                //printf("node(%d)->left is now %d\n", node->val, node->left ? node->left->val : -1);
                node->right = findChildInRange(node->right, L, R);
                //printf("node(%d)->right is now %d\n", node->val, node->right ? node->right->val : -1);
                if (node->left) to_visit.push_back(node->left);
                if (node->right) to_visit.push_back(node->right);
            }
        }

        return newroot;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["tree"];
    int L = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["L"];
    int R = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["R"];
    vector<int> vexpected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    struct TreeNode tree[vtree.size()];
    bzero(tree, vtree.size()*sizeof(struct TreeNode));
    vector2tree(vtree, tree);

    Solution s;
    TreeNode *result = s.trimBST(tree, L, R);
    vector<int> vresult = tree2vector(result);

    if (check_result(vresult, vexpected)) return 0;

    printf("trimBST(%s, %d, %d) returned %s but expected %s\n", array2str(vtree).c_str(), L, R,
        array2str(vresult).c_str(), array2str(vexpected).c_str());
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
