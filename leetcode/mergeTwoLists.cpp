/*
21. Merge Two Sorted Lists
Easy

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

#include "listNode.h"

using namespace std;

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {

        if (!l1) return l2;
        if (!l2) return l1;

        ListNode *root, *current;
        if (l1->val < l2->val)
        {
            root = l1;
            l1 = l1->next;
        } else
        {
            root = l2;
            l2 = l2->next;
        }

        current = root;
        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                current->next = l1;
                l1 = l1->next;
            } else
            {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        if (l1) current->next = l1;
        else if (l2) current->next = l2;
        return root;
    }
};

int main(int argc, char **argv)
{
    Solution s;
    ListNode node1(1);
    ListNode node2(2);node1.next = &node2;
    ListNode node3(4);node2.next = &node3;
    ListNode node4(1);
    ListNode node5(3);node4.next = &node5;
    ListNode node6(4);node5.next = &node6;
    ListNode *l1 = &node1;
    ListNode *l2 = &node4;

    ListNode *l = s.mergeTwoLists(l1, l2);
    l->dump();

    cout << "All tests succeeded" << endl;
    return 0;
}
