/*
https://leetcode.com/problems/maximum-width-of-binary-tree/

Maximum Width of Binary Tree

Given a binary tree, write a function to get the maximum width of the given tree. The width of a
tree is the maximum width among all levels. The binary tree has the same structure as a full binary
tree, but some nodes are null.

The width of one level is defined as the length between the end-nodes (the leftmost and right most
non-null nodes in the level, where the null nodes between the end-nodes are also counted into the
length calculation.

Example 1:

Input:

           1
         /   \
        3     2
       / \     \
      5   3     9

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).

Example 2:

Input:

          1
         /
        3
       / \
      5   3

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).

Example 3:

Input:

          1
         / \
        3   2
       /
      5

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).

Example 4:

Input:

          1
         / \
        3   2
       /     \
      5       9
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8
(6,null,null,null,null,null,null,7).


Note: Answer will in the range of 32-bit signed integer.
*/

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
public:
    int widthOfBinaryTree(TreeNode* root) {

        if (!root) return 0;
        vector<pair<uint64_t, TreeNode*>> *visit = new vector<pair<uint64_t, TreeNode*>>();
        vector<pair<uint64_t, TreeNode*>> *visit_next = new vector<pair<uint64_t, TreeNode*>>();

        if (root->left) visit->push_back(make_pair(0, root->left));
        if (root->right) visit->push_back(make_pair(1, root->right));

        uint64_t maxWidth = 1;

        while (visit->size()) {
            uint64_t last_index = 0, first_index = -1;
            for ( pair<uint64_t, TreeNode*> p : (*visit) ) {
                uint64_t index = p.first;
                TreeNode* n = p.second;
                if (first_index == -1) first_index = index;
                last_index = index;

                if (n->left) visit_next->push_back(make_pair(index * 2, n->left));
                if (n->right) visit_next->push_back(make_pair(index * 2 + 1, n->right));
            }
            visit->erase(visit->begin(), visit->end());
            maxWidth = max(maxWidth, last_index - first_index + 1);

            /* swap */
            vector<pair<uint64_t, TreeNode*>> *tmp = visit_next;
            visit_next = visit;
            visit = tmp;
        }
        delete visit;
        delete visit_next;
        if (maxWidth >= (uint64_t)INT_MAX) return INT_MAX;
        else return (int)maxWidth;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    struct TreeNode tree[vtree.size()] = {0};
    vector2tree(vtree, tree);

    Solution s;
    int result = s.widthOfBinaryTree(tree);

    if (result == expected) return 0;

    printf("widthOfBinaryTree(%s) returned %d but expected %d\n", array2str(vtree).c_str(),
        result, expected);
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
