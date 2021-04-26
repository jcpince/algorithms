/* 94. Binary Tree Inorder Traversal
Medium

Given the root of a binary tree, return the inorder traversal of its nodes' values.

Example 1:
Input: root = [1,null,2,3]
Output: [1,3,2]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Example 4:
Input: root = [1,2]
Output: [2,1]

Example 5:
Input: root = [1,null,2]
Output: [1,2]
 

Constraints:
The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
 

Follow up:
Recursive solution is trivial, could you do it iteratively?
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

 #include <bits/stdc++.h>

 //#define DEBUG 1
 #undef DEBUG

 #include <TreeNode.h>
 #include <UnitTests.h>
 #include <TestsHelper.h>

 using namespace std;

 const bool continue_on_failure = false;

class Solution {
    bool inline isvisited(TreeNode* root, set<struct TreeNode *> &visited) {
        return (visited.find(root) != visited.end());
    }
    void df(TreeNode* root, stack<struct TreeNode *> &stk,
                set<struct TreeNode *> &visited, vector<int> &result) {

        if ((root->left or root->right) and !isvisited(root, visited))
            stk.push(root);

        if (root->left and !isvisited(root->left, visited))
            df(root->left, stk, visited, result);

        if (root and !isvisited(root, visited)) {
            visited.insert(root);
            result.push_back(root->val);
        }

        if (root->right and !isvisited(root->right, visited))
            df(root->right, stk, visited, result);

        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            df(node, stk, visited, result);
        }
    }
    vector<int> df_it(TreeNode* node) {
        vector<int> result;
        stack<struct TreeNode *> stk;
        set<struct TreeNode *> visited;
        while (node) {
            if (node->left and !isvisited(node->left, visited)) {
                stk.push(node);
                node = node->left;
                continue;
            }
            if (node and !isvisited(node, visited)) {
                visited.insert(node);
                result.push_back(node->val);
            }
            if (node->right and !isvisited(node->right, visited)) {
                stk.push(node);
                node = node->right;
                continue;
            }
            if (!stk.empty()) {
                node = stk.top();
                stk.pop();
                continue;
            }
            node = NULL;
        }
        return result;
    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        return df_it(root);
    }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        struct TreeNode tree[vtree.size()];
        bzero(tree, vtree.size()*sizeof(struct TreeNode));
        vector2tree(vtree, tree);

        Solution s;
        vector<int> result = s.inorderTraversal(tree);
        if (result == expected) return 0;

        printf("inorderTraversal(%s) returned %s but expected %s\n",
                array2str(vtree).c_str(), array2str(result).c_str(),
                array2str(expected).c_str());
        assert(continue_on_failure);
        return 1;
}
