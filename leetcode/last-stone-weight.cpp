/*
Last Stone Weight

We have a collection of stones, each stone has a positive integer weight.

Each turn, we choose the two heaviest stones and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:

    If x == y, both stones are totally destroyed;
    If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.

At the end, there is at most 1 stone left.  Return the weight of this stone (or 0 if there are no stones left.)



Example 1:

Input: [2,7,4,1,8,1]
Output: 1
Explanation:
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of last stone.



Note:

    1 <= stones.length <= 30
    1 <= stones[i] <= 1000

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <ListNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        if (stones.size() < 2) return stones[0];
        sort(stones.begin(), stones.end());

        int nb_stones = stones.size();
        ListNode _l[nb_stones], *l, *heaviest = &_l[nb_stones-1];
        int idx = nb_stones-1;
        for ( ; idx >= 0 ; idx-- ) {
            l = &_l[idx];
            int stone = stones[idx];
            l->val = stone;
            l->next = idx > 0 ? &_l[idx-1] : NULL;
        }

        while (heaviest && heaviest->next) {
            ListNode *second = heaviest->next;
            if (second->val == heaviest->val) {
                heaviest = second->next;
            } else {
                ListNode *new_stone = heaviest, *new_head = second->next, *prev = NULL;
                new_stone->val = heaviest->val - second->val;
                if (!new_head) return new_stone->val;
                if (new_head->val <= new_stone->val) {
                    heaviest->next = new_head;
                    continue;
                }
                /* insert the new stone at its place in the list */
                heaviest = new_head;
                while(new_head && new_head->val > new_stone->val) {
                    prev = new_head;
                    new_head = new_head->next;
                }
                new_stone->next = prev->next;
                prev->next = new_stone;
            }
        }
        return heaviest ? heaviest->val : 0;
    }
};


int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> stones = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    bool result = s.lastStoneWeight(stones);

    if (result == expected) return 0;

    printf("lastStoneWeight(%s) returned %d but expected %d\n",
        array2str(stones).c_str(), result, expected);
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
