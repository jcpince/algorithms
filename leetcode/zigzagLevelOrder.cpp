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
     vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
         if (!root) return {};
         vector<vector<int>> result = {};
         vector<TreeNode*> v1 = {root}, v2, *to_visit = &v1, *next_to_visit = &v2;

         bool zig = true;
         vector<int> level;
         while(to_visit->size()) {
             for (int idx = 0 ; idx < to_visit->size() ; idx++) {
                 size_t level_index = zig ? idx : to_visit->size() - idx - 1;
                 TreeNode *n = (*to_visit)[idx];

                 level.push_back((*to_visit)[level_index]->val);
                 if (n->left) next_to_visit->push_back(n->left);
                 if (n->right) next_to_visit->push_back(n->right);
             }

             result.push_back(level);
             level.clear();

             /*swap*/
             vector<TreeNode*> *tmp = to_visit;
             to_visit->erase(to_visit->begin(), to_visit->end());
             to_visit = next_to_visit;
             next_to_visit = tmp;

             zig = !zig;
         }
         return result;
     }
 };

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> result = {};
        vector<TreeNode*> v1 = {root}, v2, *to_visit = &v1, *next_to_visit = &v2;

        bool zig = true;
        while(to_visit->size()) {
            vector<int> level(2 * to_visit->size());
            int level_index = zig ? 0 : 2 * to_visit->size() - 1;
            for (TreeNode *n : *to_visit) {
                if (zig) level[level_index++] = n->val;
                else level[level_index--] = n->val;

                if (n->left) next_to_visit->push_back(n->left);
                if (n->right) next_to_visit->push_back(n->right);
            }
            if (zig) result.push_back(vector<int>(level.begin(), level.begin()+level_index));
            else result.push_back(vector<int>(level.begin()+level_index+1, level.end()));

            /*swap*/
            vector<TreeNode*> *tmp = to_visit;
            to_visit->erase(to_visit->begin(), to_visit->end());
            to_visit = next_to_visit;
            next_to_visit = tmp;

            zig = !zig;
        }
        return result;
    }
};
