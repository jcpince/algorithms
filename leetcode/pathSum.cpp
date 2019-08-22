class Solution {
    void dfs(TreeNode* root, int sum, vector<int> current, int csum, vector<vector<int>> &ans) {
        if (!root) return;

        current.push_back(root->val);
        csum += root->val;
        if (root->left or root->right) {
            if (root->left) dfs(root->left, sum, current, csum, ans);
            if (root->right) dfs(root->right, sum, current, csum, ans);
            return;
        }
        // leaf
        if (csum == sum) ans.push_back(current);
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> tmp;
        vector<vector<int>> ans;
        dfs(root, sum, tmp, 0, ans);
        return ans;
    }
};
