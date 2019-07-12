/*
https://leetcode.com/problems/max-increase-to-keep-city-skyline/

807. Max Increase to Keep City Skyline
Medium

In a 2 dimensional array grid, each value grid[i][j] represents the height of a building located
there. We are allowed to increase the height of any number of buildings, by any amount (the amounts
can be different for different buildings). Height 0 is considered to be a building as well.

At the end, the "skyline" when viewed from all four directions of the grid, i.e. top, bottom, left,
and right, must be the same as the skyline of the original grid. A city's skyline is the outer
contour of the rectangles formed by all the buildings when viewed from a distance. See the following
example.

What is the maximum total sum that the height of the buildings can be increased?

Example:
Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
Output: 35
Explanation:
The grid is:
[ [3, 0, 8, 4],
  [2, 4, 5, 7],
  [9, 2, 6, 3],
  [0, 3, 1, 0] ]

The skyline viewed from top or bottom is: [9, 4, 8, 7]
The skyline viewed from left or right is: [8, 7, 9, 3]

The grid after increasing the height of buildings without affecting skylines is:

gridNew = [ [8, 4, 8, 7],
            [7, 4, 7, 7],
            [9, 4, 8, 7],
            [3, 3, 3, 3] ]

Notes:

    1 < grid.length = grid[0].length <= 50.
    All heights grid[i][j] are in the range [0, 100].
    All buildings in grid[i][j] occupy the entire grid cell: that is, they are a 1 x 1 x grid[i][j]
        rectangular prism.
*/

#include <bits/stdc++.h>
#include <climits>

#define DEBUG 1
//#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {

        int hskyline[grid.size()], vskyline[grid.size()];
        bzero(hskyline, grid.size() * sizeof(int));
        bzero(vskyline, grid.size() * sizeof(int));
        for (size_t i = 0 ; i < grid.size() ; i++) {
            for (size_t j = 0 ; j < grid[0].size() ; j++) {
                hskyline[i] = max(hskyline[i], grid[i][j]);
                vskyline[j] = max(vskyline[j], grid[i][j]);
            }
        }

        int increase = 0;
        for (size_t i = 0 ; i < grid.size() ; i++) {
            for (size_t j = 0 ; j < grid[0].size() ; j++) {
                dev_assert(grid[i][j] <= min(hskyline[i], vskyline[j]));
                increase += min(hskyline[i], vskyline[j]) - grid[i][j];
            }
        }
        return increase;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> grid = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.maxIncreaseKeepingSkyline(grid);
    if (result == expected) return 0;

    printf("maxIncreaseKeepingSkyline(%s) returned %d but expected %d\n", array2str(grid).c_str(),
        result, expected);
    dev_assert(continue_on_failure);
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
