#include <TreeNode.h>
#include <TestsHelper.h>

void vector2tree(vector<int> &v, struct TreeNode *tree) {
    size_t idx = 0;
    struct TreeNode *node = &tree[idx++];
    node->val = v[idx-1];

    vector<struct TreeNode *> vnodes = {node};
    while ( idx < v.size() )  {
        node = vnodes.front();
        vnodes.erase(vnodes.begin());
        if (v[idx++] != -1) {
            node->left = &tree[idx-1];
            node->left->val = v[idx-1];
            vnodes.push_back(node->left);
            debug_print("node.val(%d) has a left child with value %d\n", node->val, node->left->val);
        } else { debug_print("node.val(%d) has no left child\n", node->val); }
        if (v[idx++] != -1) {
            node->right = &tree[idx-1];
            node->right->val = v[idx-1];
            vnodes.push_back(node->right);
            debug_print("node.val(%d) has a right child with value %d\n", node->val, node->right->val);
        } else { debug_print("node.val(%d) has no right child\n", node->val); }
    }
}

vector<int> tree2vector(struct TreeNode *tree) {
    vector<int> v;
    queue<TreeNode *> q;
    q.push(tree);

    while ( !q.empty() )  {
        TreeNode *node = q.front();
        q.pop();

        if (node) {
            if (node->left)
                debug_print("node.val(%d) has a left child with value %d\n", node->val, node->left->val);
            else {debug_print("node.val(%d) has no left child\n", node->val);}
            if (node->right)
                debug_print("node.val(%d) has a right child with value %d\n", node->val, node->right->val);
            else {debug_print("node.val(%d) has no right child\n", node->val);}
        }

        if (node) {
            v.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        } else v.push_back(-1);
    }
    return v;
}

void deleteDynTree(TreeNode *tree) {
    queue<TreeNode *> q;
    q.push(tree);

    while ( !q.empty() )  {
        TreeNode *node = q.front();
        q.pop();

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
        delete node;
    }
}
