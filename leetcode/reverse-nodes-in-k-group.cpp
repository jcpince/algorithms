#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

#include "ListNode.h"

using namespace std;

const bool continue_on_failure = false;

class Solution {
    ListNode *getKth(ListNode* head, int k) {
        ListNode *node = head;
        while(node && --k) node = node->next;
        return k ? NULL : node;
    }
    ListNode *swap_seg(ListNode *prev_chain, ListNode *seg_tail) {

        ListNode *head = prev_chain->next, *next_chain = seg_tail->next;
        ListNode *n0, *n1, *n2;
        n0 = prev_chain->next;
        n1 = n0->next;
        n2 = n1->next;
        while (n0 != seg_tail) {
            n1->next = n0;
            n0 = n1;
            n1 = n2;
            n2 = n2 ? n2->next : NULL;
        }
        prev_chain->next = seg_tail;
        // head is now our tail...
        head->next = next_chain;
        return head;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *next_chain, *pre_chain, pre_head, *seg_tail;

        if (k < 2 || !head || !head->next) return head;

        pre_head.next = head;
        seg_tail = getKth(head, k);
        head = &pre_head;
        pre_chain = head;

        while(seg_tail) {
            next_chain = seg_tail->next;
            pre_chain = swap_seg(pre_chain, seg_tail);
            head = next_chain;
            seg_tail = getKth(head, k);
        }
        return pre_head.next;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> vin = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["vin"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    vector<int> vexpected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
    ListNode _l1[vin.size()], *l1 = _l1;
    ListNode _l2[vexpected.size()], *l2 = _l2;
    if (vin.size()) vector2list(vin, l1);
        else l1 = NULL;
    if (vexpected.size()) vector2list(vexpected, l2);
        else l2 = NULL;

    Solution s;
    ListNode *result = s.reverseKGroup(l1, k);
    vector<int> vr;
    list2vector(result, vr);

    if (check_result(vr, vexpected)) return 0;

    printf("s.reverseKGroup(%s, %d) returned %s but expected %s\n", array2str(vin).c_str(), k,
        array2str(vr).c_str(), array2str(vexpected).c_str());
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
