/*
https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

430. Flatten a Multilevel Doubly Linked List
Medium

You are given a doubly linked list which in addition to the next and previous pointers, it could
have a child pointer, which may or may not point to a separate doubly linked list. These child
lists may have one or more children of their own, and so on, to produce a multilevel data structure,
as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. You are given
the head of the first level of the list.



Example:

Input:
 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL

Output:
1-2-3-7-8-11-12-9-10-4-5-6-NULL



Explanation for the above example:

Given the following multilevel doubly linked list:



We should return the following flattened doubly linked list:


*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    Node* flatten(Node* head) {
        vector<Node*> divergences;

        Node *node = head;
        while (node) {
            if (node->child) {
                if (node->next) divergences.push_back(node->next);
                node->next = node->child;
                node->next->prev = node;
                node->child = NULL;
            } else if (!node->next and divergences.size()) {
                node->next = divergences.back();
                node->next->prev = node;
                divergences.pop_back();
            }
            node = node->next;
        }
        return head;
    }
};
