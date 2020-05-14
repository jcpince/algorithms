/*
Perform String Shifts

You are given a string s containing lowercase English letters, and a matrix shift, where shift[i] = [direction, amount]:

direction can be 0 (for left shift) or 1 (for right shift).
amount is the amount by which string s is to be shifted.
A left shift by 1 means remove the first character of s and append it to the end.
Similarly, a right shift by 1 means remove the last character of s and add it to the beginning.

Return the final string after all operations.



Example 1:

Input: s = "abc", shift = [[0,1],[1,2]]
Output: "cab"
Explanation:
[0,1] means shift to left by 1. "abc" -> "bca"
[1,2] means shift to right by 2. "bca" -> "cab"

Example 2:

Input: s = "abcdefg", shift = [[1,1],[1,1],[0,2],[1,3]]
Output: "efgabcd"
Explanation:
[1,1] means shift to right by 1. "abcdefg" -> "gabcdef"
[1,1] means shift to right by 1. "gabcdef" -> "fgabcde"
[0,2] means shift to left by 2. "fgabcde" -> "abcdefg"
[1,3] means shift to right by 3. "abcdefg" -> "efgabcd"



Constraints:

1 <= s.length <= 100
s only contains lower case English letters.
1 <= shift.length <= 100
shift[i].length == 2
0 <= shift[i][0] <= 1
0 <= shift[i][1] <= 100

*/


#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

class Solution {
        void inline copyright(char *src, char *dst, const int &amount, const int &len) {
                memcpy(dst, src + len - amount, amount);
                memcpy(dst + amount, src, len - amount);
                //printf("%s(%s, %d) returns %s\n", __func__, src, amount, dst);
        }
        void inline copyleft(char *src, char *dst, const int &amount, const int &len) {
                memcpy(dst, src + amount, len - amount);
                memcpy(dst + len - amount, src, amount);
                //printf("%s(%s, %d) returns %s\n", __func__, src, amount, dst);
        }
public:
        string stringShift2(string _s, const vector<vector<int>>& shifts) {
                if (!shifts.size()) return _s;

                // acumulate right-shift and left-shift in pairs
                char *s = strdup(_s.c_str()), *dest = strdup(_s.c_str());
                int nb_shifts = shifts.size(), slen = _s.length();
                int direction, cum_shifts[2], delta = 0;

                for (int idx = 0 ; idx < nb_shifts ;) {
                        if (delta) {
                                // swap s and stmp
                                char *tmp = dest;
                                dest = s;
                                s = tmp;
                        }
                        printf("0 - idx %d: direction %d, shift %d\n",
                                idx, shifts[idx][0], shifts[idx][1]);

                        direction = shifts[idx][0];
                        cum_shifts[direction] = shifts[idx][1];
                        printf("1 - idx %d: cum_left %d, cum_right %d\n",
                                idx, cum_shifts[0], cum_shifts[1]);
                        while(idx+1 < nb_shifts && direction == shifts[idx+1][0]) {
                                cum_shifts[direction] += shifts[idx+1][1];
                                printf("2 - idx %d: cum_left %d, cum_right %d\n",
                                        idx, cum_shifts[0], cum_shifts[1]);
                                idx++;
                        }
                        idx++;

                        printf("3 - idx %d: cum_left %d, cum_right %d\n",
                                idx, cum_shifts[0], cum_shifts[1]);
                        if (idx < nb_shifts) {
                                direction = shifts[idx][0];
                                cum_shifts[direction] = shifts[idx][1];
                                /*while(idx+1 < nb_shifts && direction == shifts[idx+1][0]) {
                                        cum_shifts[direction] += shifts[idx+1][1];
                                        idx++;
                                }*/
                                idx++;
                        } else {
                                direction = direction ? 0 : 1;
                                cum_shifts[direction] = 0;
                        }

                        delta = (cum_shifts[1] - cum_shifts[0]) % slen;
                        printf("idx %d: cum_left %d, cum_right %d => delta %d\n",
                                idx, cum_shifts[0], cum_shifts[1], delta);
                        if (!delta) continue;
                        if (delta > 0) copyright(s, dest, delta, slen);
                        else copyleft(s, dest, 0 - delta, slen);
                }

                string res(dest);
                free(dest);
                free(s);
                return res;
        }
        string stringShift(string _s, const vector<vector<int>>& shifts) {
                if (!shifts.size()) return _s;

                // acumulate right-shift and left-shift in pairs
                char *s = strdup(_s.c_str()), *dest = strdup(_s.c_str());
                int nb_shifts = shifts.size(), slen = _s.length();

                for (int idx = 0 ; idx < nb_shifts ;) {
                        // printf("0 - idx %d: direction %d, shift %d\n",
                        //         idx, shifts[idx][0], shifts[idx][1]);

                        int direction = shifts[idx][0];
                        int cum_shift = shifts[idx][1];
                        // printf("1 - idx %d: cum_shift %d\n", idx, cum_shift);
                        while(idx+1 < nb_shifts &&
                                                direction == shifts[idx+1][0]) {
                                cum_shift += shifts[idx+1][1];
                                // printf("2 - idx %d: cum_shift %d\n", idx, cum_shift);
                                idx++;
                        }
                        idx++;

                        cum_shift = cum_shift % slen;
                        if (!cum_shift) continue;

                        // swap s and stmp
                        char *tmp = dest;
                        dest = s;
                        s = tmp;

                        if (direction) copyright(s, dest, cum_shift, slen);
                        else copyleft(s, dest, cum_shift, slen);
                }

                string res(dest);
                free(dest);
                free(s);
                return res;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        string s = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s"];
        vector<vector<int>> shifts = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["shifts"];
        string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution __s;
        string result = __s.stringShift(s, shifts);

        if (result == expected) return 0;

        printf("stringShift(%s, %s) returned %s but expected %s\n",
                s.c_str(), array2str(shifts).c_str(), result.c_str(), expected.c_str());
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
