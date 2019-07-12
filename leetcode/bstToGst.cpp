/*
https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/

1038. Binary Search Tree to Greater Sum Tree
Medium

Given the root of a binary search tree with distinct values, modify it so that every node has a
new value equal to the sum of the values of the original tree that are greater than or equal to
node.val.

As a reminder, a binary search tree is a tree that satisfies these constraints:

    The left subtree of a node contains only nodes with keys less than the node's key.
    The right subtree of a node contains only nodes with keys greater than the node's key.
    Both the left and right subtrees must also be binary search trees.



Example 1:

Input: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]



Note:

    The number of nodes in the tree is between 1 and 100.
    Each node will have value between 0 and 100.
    The given tree is a binary search tree.
*/

#include <bits/stdc++.h>
#include <climits>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

class Solution {
    void append_right_branch(vector<struct TreeNode *> &vnodes, TreeNode* root) {
        vnodes.push_back(root);
        while ( root->right ) {
            vnodes.push_back(root->right);
            root = root->right;
        }
    }
public:
    TreeNode* bstToGst(TreeNode* root) {

        vector<struct TreeNode *> vnodes;

        // find and append the path to the right outer node
        append_right_branch(vnodes, root);

        //printf("Now, visit starting from node %d\n", vnodes.back()->val);
        int last_node_val = 0;
        while ( vnodes.size() ) {
            TreeNode *node = vnodes.back();
            vnodes.pop_back();
            //printf("Visit node %d\n", node->val);
            node->val += last_node_val;
            last_node_val = node->val;

            if (node->left) append_right_branch(vnodes, node->left);
        }

        return root;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    struct TreeNode tree[vtree.size()];
    memset(tree, 0, vtree.size()*sizeof(struct TreeNode));
    vector2tree(vtree, tree);

    Solution s;
    struct TreeNode *result = s.bstToGst(tree);

    vector<int> vresult = tree2vector(result);
    if (check_result(vresult, expected)) return 0;

    printf("bstToGst(%s) returned %s but expected %s\n", array2str(vtree).c_str(),
        array2str(vresult).c_str(), array2str(expected).c_str());
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
