/*
https://leetcode.com/problems/container-with-most-water/

11. Container With Most Water
Medium

Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.



The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.



Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    int maxArea(vector<int>& height) {

        int maxarea = 0;
        int idx_left = 0, idx_right = height.size() - 1;
        while (idx_left < idx_right) {
            int area = min(height[idx_left], height[idx_right]) * (idx_right - idx_left);
            maxarea = max(maxarea, area);
            if (height[idx_left] < height[idx_right])
                idx_left++;
            else if (height[idx_left] > height[idx_right])
                idx_right--;
            else while ((idx_left < idx_right) && (height[++idx_left] == height[--idx_right]));
        }
        return maxarea;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> x = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.maxArea(x);
    if (result == expected) return 0;

    printf("maxArea(%s) returned %d but expected %d\n", array2str(x).c_str(), result, expected);
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
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
