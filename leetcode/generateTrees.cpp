/*
Unique Binary Search Trees II

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

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
        void insert(TreeNode *root, TreeNode *node) {
                // vector<int> vtree = tree2vector(root);
                // TreeNode *root0 = root;
                // printf("Insert %d in tree %s -> ", node->val,
                //         array2str(vtree).c_str());
                do {
                        if (node->val > root->val) {
                                if (root->right)
                                        root = root->right;
                                else {
                                        root->right = node;
                                        // vtree = tree2vector(root0);
                                        // printf("%s\n", array2str(vtree).c_str());
                                        return;
                                }
                        }
                        else {
                                if (root->left)
                                        root = root->left;
                                else {
                                        root->left = node;
                                        // vtree = tree2vector(root0);
                                        // printf("%s\n", array2str(vtree).c_str());
                                        return;
                                }
                        }
                } while(root);
                assert(false);
        }
        bool sameTree(TreeNode *tree0, TreeNode *tree1) {
                if (tree0->val != tree1->val) return false;
                if ((bool)tree0->right ^ (bool)tree1->right)
                        return false;
                if ((bool)tree0->left ^ (bool)tree1->left)
                        return false;
                if (tree0->right && !sameTree(tree0->right, tree1->right))
                        return false;
                if (tree0->left && !sameTree(tree0->left, tree1->left))
                        return false;
                return true;
        }
        bool already_there(vector<TreeNode*> cache, TreeNode *root) {
                for (TreeNode *node : cache)
                        if (sameTree(node, root))
                                return true;
                return false;
        }
public:
    vector<TreeNode*> generateTrees2(int n) {
        vector<int> combination;
        vector<TreeNode*> result;

        if (!n) return {};

        for (int idx = 1 ; idx <= n ; idx++)
                combination.push_back(idx);

        do {
                TreeNode *root = NULL;
                for (int num : combination) {
                        TreeNode *node = new TreeNode(num);
                        if (!root) root = node;
                        else insert(root, node);
                }
                // vector<int> vtree = tree2vector(root);
                // printf("combination: %s -> tree %s\n",
                //         array2str(combination).c_str(), array2str(vtree).c_str());

                if (!already_there(result, root))
                        result.push_back(root);
                else deleteDynTree(root);
        } while (next_permutation(combination.begin(), combination.end()));

        return result;
    }

    vector<TreeNode*> generateTrees(int n) {
            if (n == 0) return {};
            return helper(1, n);
    }

    vector<TreeNode*> helper(int start, int end) {
            vector<TreeNode*> result;
            if (start > end) result.push_back(nullptr);
            for (int i = start; i <= end; i++) {
                    vector<TreeNode*> left = helper(start, i - 1);
                    vector<TreeNode*> right = helper(i + 1, end);
                    for (auto l : left) {
                            for (auto r : right) {
                                    TreeNode* root = new TreeNode(i);
                                    root->left = l;
                                    root->right = r;
                                    result.push_back(root);
                                    // printf("i = %d, root is %s\n", i,
                                    //     array2str(tree2vector(root)).c_str());
                            }
                    }
            }
            return result;
    }
};

void cleanup_vtree(vector<TreeNode*> vtree) {
        queue<TreeNode *> q;
        /* delete in 2 steps to avoids double free when nodes are reused */
        set<TreeNode*> todelete;

        for (TreeNode* tree : vtree) {
                q.push(tree);

                while ( !q.empty() )  {
                        TreeNode *node = q.front();
                        q.pop();

                        if (node->left) q.push(node->left);
                        if (node->right) q.push(node->right);
                        todelete.insert(node);
                }
        }
        for (TreeNode* tree : todelete)
                delete tree;
}

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];


        Solution s;
        vector<TreeNode*> result = s.generateTrees(n);
        vector<vector<int>> vres;
        for (TreeNode* tree : result)
                vres.push_back(tree2vector(tree));
        cleanup_vtree(result);

        if (vres == expected) return 0;

        printf("generateTrees(%d) returned %s but expected %s\n", n,
                array2str(vres).c_str(), array2str(expected).c_str());
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
