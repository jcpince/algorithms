/*
https://leetcode.com/problems/n-ary-tree-level-order-traversal/

429. N-ary Tree Level Order Traversal
Easy

Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right,
level by level).

For example, given a 3-ary tree:





We should return its level order traversal:

[
     [1],
     [3,2,4],
     [5,6]
]



Note:

    The depth of the tree is at most 1000.
    The total number of nodes is at most 5000.

*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if (!root) return {};
        vector<vector<int>> result = {{root->val}};
        vector<Node*> v1 = {root}, v2, *to_visit = &v1, *next_to_visit = &v2;

        vector<int> level;
        while(to_visit->size()) {
            for (Node *n : *to_visit) {
                for (Node *child : n->children) {
                    next_to_visit->push_back(child);
                    level.push_back(child->val);
                }
            }
            if (level.size()) result.push_back(level);
            level.erase(level.begin(), level.end());

            /*swap*/
            vector<Node*> *tmp = to_visit;
            to_visit->erase(to_visit->begin(), to_visit->end());
            to_visit = next_to_visit;
            next_to_visit = tmp;
        }
        return result;
    }
};
