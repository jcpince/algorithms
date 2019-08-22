/*
https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/

1161. Maximum Level Sum of a Binary Tree
Medium

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at level X is maximal.



Example 1:

Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.



Note:

    The number of nodes in the given tree is between 1 and 10^4.
    -10^5 <= node.val <= 10^5
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        int maxsum = INT_MIN, maxlevel = 0, idxlevel = 1;
        vector<TreeNode*> current_level({root}), next_level;

        while(!current_level.empty()) {
            int sum = 0;
            // build next
            for (TreeNode* n : current_level) {
                sum += n->val;
                if (n->right)
                    next_level.emplace_back(n->right);
                if (n->left)
                    next_level.emplace_back(n->left);
            }
            if (sum > maxsum) {
                maxsum = sum;
                maxlevel = idxlevel;
            }
            current_level = next_level;
            next_level.clear();
            idxlevel++;
        }
        return maxlevel;
    }
};

/* Or a solution based on a single queue 

    1 - get the queue size at each level
    2 - for size, pop from the queue and add the value
    3 - compare to max and update max and level if necessary
    4 - Increase the level counter by one and loop over until the queue is empty
*/
