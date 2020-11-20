/*
61. Rotate List
Medium

Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <ListNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

const bool continue_on_failure = false;

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        //printf("%s(%d with ", __func__, k);head->dump();
        if (k == 0 || !head || !head->next) return head;

        ListNode* head0 = head, *prev_pivot = NULL, *pivot = NULL, *tail;
        int len = 0;
        pivot = head;
        while (head) {
            if (k == 0) {
                prev_pivot = pivot;
                pivot = pivot->next;
                //printf("set pivot1 to %d\n", pivot->val);
            } else k--;
            
            tail = head;
            head  = head->next;
            len++;
        }
        if (!prev_pivot) {
            //printf("k is %d\n", k);
            if ((k && (k % len)) || (k == 1)) {
                // do something here
                k = len - k % len - 1;
                prev_pivot = head0;
                //printf("reset prev_pivot1 to %d, len is %d, k is %d\n", prev_pivot->val, len, k);
                while (k--)
                    prev_pivot = prev_pivot->next;
                //printf("set prev_pivot to %d\n", prev_pivot->val);
                //assert(prev_pivot);
                pivot = prev_pivot->next;
                prev_pivot->next = NULL;
                tail->next = head0;
            }
        } else {
            // printf("prev_pivot is %p (%d)\n", prev_pivot, prev_pivot?prev_pivot->val:-1);
            // if (pivot)
            //     printf("pivot is %d\n", pivot->val);
            // else printf("pivot is NULL\n");

            prev_pivot->next = NULL;
            tail->next = head0;
        }
        return pivot;
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        vector<int> vin = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["list"];
        int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
        vector<int> vexpected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        ListNode _l1[vin.size()], *l1 = _l1;
        ListNode _l2[vexpected.size()], *l2 = _l2;
        if (vin.size()) vector2list(vin, l1);
            else l1 = NULL;
        if (vexpected.size()) vector2list(vexpected, l2);
            else l2 = NULL;

        Solution _s;
        ListNode *result = _s.rotateRight(l1, k);
        vector<int> vr;
        list2vector(result, vr);


        if (check_result(vr, vexpected)) return 0;

        printf("rotateRight(%s, %d) returned %s but expected %s\n",
            array2str(vin).c_str(), k, array2str(vr).c_str(), array2str(vexpected).c_str());
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
                cout << errors_count << " test(s) failed over a total of "
                        << tests_ran << endl;

        return errors_count;
}