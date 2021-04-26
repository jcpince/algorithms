/* 98. Validate Binary Search Tree
Medium

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
 

Example 1:
Input: root = [2,1,3]
Output: true

Example 2:
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
 

Constraints:
The number of nodes in the tree is in the range [1, 104].
-231 <= Node.val <= 231 - 1
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <TestsHelper.h>
#include <cstdint>

//#define DEBUG 1
#undef DEBUG

using namespace std;

const bool continue_on_failure = false;

class Solution {
    bool isValidBST(const TreeNode* node, int64_t &__min, int64_t &__max) {
        bool result = true;

        if (node->left) {
            int64_t _min = (int64_t)node->val, _max = (int64_t)node->val;
            result &= node->left->val < node->val and
                        isValidBST(node->left, _min, _max) and
                            node->val > _max;
            __min = _min;
        }
        else __min = (int64_t)node->val;

        if (result and node->right) {
            int64_t _min = (int64_t)node->val, _max = (int64_t)node->val;
            result &= node->right->val > node->val and
                        isValidBST(node->right, _min, _max) and
                            node->val < _min;
            __max = _max;
        }
        else __max = (int64_t)node->val;

        return result;
    }
public:
    bool isValidBST(const TreeNode* root) {
        int64_t _min = (int64_t)root->val, _max = (int64_t)root->val;
        return isValidBST(root, _min, _max);
    }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        struct TreeNode tree[vtree.size()];
        bzero(tree, vtree.size()*sizeof(struct TreeNode));
        vector2tree(vtree, tree);

        Solution s;
        bool result = s.isValidBST(tree);
        if (result == expected) return 0;

        printf("isValidBST(%s) returned %d but expected %d\n",
                array2str(vtree).c_str(), result, expected);
        assert(continue_on_failure);
        return 1;
}
