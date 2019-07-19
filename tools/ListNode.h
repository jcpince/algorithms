#ifndef __LISTNODE__
#define __LISTNODE__

#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(NULL) {}
    ListNode(int x) : val(x), next(NULL) {}
    void dump() {
        struct ListNode *current = this;
        printf("[");
        do {
            printf("%d ", current->val);
            current = current->next;
        } while (current);
        printf("]\n");
    }
};

void list2vector(ListNode *root, vector<int> &v) {
    while (root) {
        v.push_back(root->val);
        root = root->next;
    }
}

void vector2list(vector<int> &v, ListNode *root) {
    for (vector<int>::iterator it = v.begin() ; it != v.end() ; it++) {
        int num = *it;
        root->val = num;
        if ((it+1) == v.end()) root->next = NULL;
        else root->next = root+1;
        root = root->next;
    }
}

#endif /* __LISTNODE__ */
