/*
45. Jump Game II
Hard

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

Example:

Input: [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2.
Jump 1 step from index 0 to 1, then 3 steps to the last index.

Note:

You can assume that you can always reach the last index.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
        int _j(const vector<int>& jumps, const int target,
                const int current_jumps, const int current_pos, int minjumps) {

                //printf("jump called from %d to %d\n", current_pos, target);

                if (current_pos + jumps[current_pos] >= target) {
                        return min(minjumps, current_jumps+1);
                }

                for (int steps = 1; steps <= jumps[current_pos] ; steps++) {
                        minjumps = _j(jumps, target, current_jumps + 1,
                                        current_pos + steps, minjumps);
                        if (minjumps == current_jumps+2)
                                break;
                }
                return minjumps;
        }

        int _j2(vector<int>& jumps, int target) {

                jumps[target] = 0;
                for (int offset = target - 1 ; offset >= 0 ; offset--) {
                        if (!jumps[offset]) {
                                // Dead end
                                jumps[offset] = INT_MAX;
                                continue;
                        }
                        if (jumps[offset] >= target - offset) {
                                jumps[offset] = 1;
                                continue;
                        }
                        int min_steps = INT_MAX;
                        for (int steps = 1 ; min_steps > 1 && steps <= jumps[offset] ; steps++)
                                min_steps = min(jumps[offset + steps], min_steps);
                        if (min_steps == INT_MAX)
                                jumps[offset] = INT_MAX; // dead end
                        else
                                jumps[offset] = 1 + min_steps;
                }
                return jumps[0];
        }
        int _j3(const vector<int>& jumps, int target) {

                int res = 0;
                for (int offset = 0 ; offset <= target ; ) {
                        int best_hop = 0, best_jump = 0;
                        for (int hop = jumps[offset] ; hop > 0 ; hop--) {
                                if (offset + hop >= target)
                                        return res + 1;
                                int hop_target = jumps[offset + hop];
                                if (hop_target + offset >= target)
                                        return res + 2;
                                if (hop_target && hop + hop_target > best_jump) {
                                        best_hop = hop;
                                        best_jump = hop + hop_target;
                                }
                        }
                        res++;
                        offset += best_hop;
                }
                return res;
        }
public:
        int jump(vector<int>& jumps) {

                if (jumps.size() < 2) return 0;

                printf("Array size %ld\n", jumps.size());

                //return _j(jumps, jumps.size()-1, 0, 0, INT_MAX);
                return _j3(jumps, jumps.size()-1);
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> jumps = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        int result = s.jump(jumps);

        if (result == expected) return 0;

        printf("jump(%s) returned %d but expected %d\n",
        array2str(jumps).c_str(), result, expected);
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
