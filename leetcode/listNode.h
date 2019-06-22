#ifndef __LISTNODE__
#define __LISTNODE__

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

#endif /* __LISTNODE__ */
