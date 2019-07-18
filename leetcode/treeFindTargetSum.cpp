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
     struct TreeNode *find_target(TreeNode* node, int target) {
         if (node->val == target) return node;
         if (node->val < target) {
             if (!node->left) return NULL;
             else return find_target(node->left, target);
         }
         if (!node->right) return NULL;
         return find_target(node->right, target);
     }
     int max_val(struct TreeNode* node) {
         while (node->left) node = node->left;
         return node->val;
     }
 public:
     bool findTarget(TreeNode* root, int k) {
         if (max_val(root) < (k/2)) return false;

         vector<struct TreeNode*> layer = {root};
         while (layer.size()) {
             struct TreeNode* node = layer.back();
             layer.pop_back();

             int diff = k - node->val;
             struct TreeNode* n1 = find_target(root, diff);
             if (n1) {
                 if (n1 != node) return true;
                 if (n1->right and (n1->right->val == diff)) return true;
             }
             if (node->left) layer.push_back(node->left);
             if (node->right) layer.push_back(node->right);
         }
         return false;
     }
 };
