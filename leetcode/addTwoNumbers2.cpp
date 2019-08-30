#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include "ListNode.h"
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

/*class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<pair<int, int>> s;
        int l1len = 0, l2len = 0;
        ListNode* _l1 = l1, *_l2 = l2;
        while (_l1 or _l2) {
            if (_l1) {
                _l1 = _l1->next;
                l1len++;
            }
            if (_l2) {
                _l2 = _l2->next;
                l2len++;
            }
        }

        if (l1len != l2len) {
            if (l1len > l2len) {
                while (l1len > l2len) {
                    s.push(make_pair(l1->val, 0));
                    l1 = l1->next;
                    l1len--;
                }
            } else {
                while (l1len < l2len) {
                    s.push(make_pair(0, l2->val));
                    l2 = l2->next;
                    l1len++;
                }
            }
        }

        while (l1) {
            s.push(make_pair(l1->val, l2->val));
            l1 = l1->next;
            l2 = l2->next;
        }
        ListNode *result = nullptr;
        int v1, v2, carry = 0;
        while (!s.empty()) {
            pair<int, int> p = s.top();
            s.pop();
            v1 = p.first;
            v2 = p.second;
            v1 += v2 + carry;
            carry = v1 > 9 ? 1 : 0;
            if (carry) v1 -= 10;
            ListNode *node = new ListNode(v1);
            node->next = result;
            result = node;
            //printf("result[%d] is %d\n", s.size(), v1);
        }
        if (carry) {
            ListNode *node = new ListNode(1);
            node->next = result;
            result = node;
        }
        return result;
    }
};*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    void list2vector(const ListNode* l, vector<int> &v) {
        while (l) {v.push_back(l->val); l = l->next;}
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        vector<int> v1, v2, *vl, *vs;
        list2vector(l1, v1);
        list2vector(l2, v2);

        if (!v1.size()) return l2;
        if (!v2.size()) return l1;

        ListNode *longest, *shortest, *result;
        vector<int>::iterator it, resultit;
        if (v1.size() > v2.size()) {
            longest = l1;
            shortest = l2;
            vl = &v1;
            vs = &v2;
        }
        else {
            longest = l2;
            shortest = l1;
            vl = &v2;
            vs = &v1;
        }

        int carry = 0;
        for ( it = vs->end()-1, resultit = vl->end()-1 ; it != vs->begin() ; it--, resultit--) {
            // printf("Adds %d and %d and %d => ", *it, *resultit, carry);
            *resultit += *it + carry;
            if (*resultit >= 10) {
                *resultit -= 10;
                carry = 1;
            } else carry = 0;
            // printf("%d\n", *resultit);
        }
        bool add1node = false;
        int last_num = *it;
        do {
            // printf("Adds %d and %d and %d => ", *it, *resultit, carry);
            *resultit += last_num + carry;
            if (*resultit >= 10) {
                *resultit -= 10;
                carry = 1;
            } else carry = 0;
            // printf("%d\n", *resultit);
            if (carry and (resultit == vl->begin())) {
                add1node = true;
                break;
            }
            resultit--;
            last_num = 0;
        } while (carry);

        // printf("v1 = %s\n", array2str(v1).c_str());
        // printf("v2 = %s\n", array2str(v2).c_str());

        result = longest;
        if (add1node) {
            shortest->val = 1;
            shortest->next = longest;
            result = shortest;
        }
        //printf("sums up from longest %d\n", longest->val);
        for (size_t idx = 0 ; idx < vl->size() ; idx++) {
            longest->val = (*vl)[idx];
            longest = longest->next;
        }

        return result;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> v1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["l1"];
    vector<int> v2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["l2"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
    ListNode l1[v1.size()];
    ListNode l2[v2.size()];
    vector2list(v1, l1);
    vector2list(v2, l2);

    Solution s;
    ListNode *result = s.addTwoNumbers(l1, l2);
    vector<int> vr;
    list2vector(result, vr);

    if (check_result(vr, expected)) return 0;

    printf("addTwoNumbers(%s, %s) returned %s but expected %s\n", array2str(v1).c_str(),
        array2str(v2).c_str(), array2str(vr).c_str(), array2str(expected).c_str());
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
