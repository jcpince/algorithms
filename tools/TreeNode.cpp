#include <TreeNode.h>
#include <TestsHelper.h>

void vector2tree(vector<int> &v, struct TreeNode *tree) {
    size_t idx = 0;
    struct TreeNode *node = &tree[idx++];
    if (!v.size()) return;
    node->val = v[0];

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
        if (idx < v.size() and v[idx++] != -1) {
            node->right = &tree[idx-1];
            node->right->val = v[idx-1];
            vnodes.push_back(node->right);
            debug_print("node.val(%d) has a right child with value %d\n", node->val, node->right->val);
        } else { debug_print("node.val(%d) has no right child\n", node->val); }
    }
}

#if 0 /* bfs */
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
#endif

/*void print_queue(queue<struct TreeNode*> q)
{
        std::cout << "new queue: ";
        while (!q.empty())
        {
                struct TreeNode* node = q.front();
                int val = node ? node->val : -1;
                std::cout << val << " ";
                q.pop();
        }
        std::cout << std::endl;
}*/

vector<int> tree2vector(struct TreeNode *root) {
    vector<int> v;
    queue<TreeNode *> q1, q2, *layer = &q1, *nextlayer = &q2, *_tmp;
    layer->push(root);
    int nodecount = 0, next_nodecount = 0;
    //int new_layer = 1;

    while ( !layer->empty() )  {
        //if (new_layer) print_queue(*layer);
        //new_layer = 0;
        TreeNode *node = layer->front();
        layer->pop();

        if (!node) {
                if (nodecount > 0 || next_nodecount) {
                        //printf("push -1\n");
                        v.push_back(-1);
                }
        }
        else {
                //printf("Node %p->val %d\n", node, node->val);
                v.push_back(node->val);
                if (node->left) next_nodecount++;
                if (node->right) next_nodecount++;
                nextlayer->push(node->left);
                nextlayer->push(node->right);
                nodecount--;
        }

        if (layer->empty()) {
                /* swap the queues */
                _tmp = layer;
                if (next_nodecount > 0) {
                        layer = nextlayer;
                        nodecount = next_nodecount;
                }
                nextlayer = _tmp;
                next_nodecount = 0;
                //new_layer = 1;
        }
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
