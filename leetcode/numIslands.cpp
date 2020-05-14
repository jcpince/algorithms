/*
https://leetcode.com/problems/number-of-islands/

200. Number of Islands
Medium

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is
surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may
assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1

Example 2:

Input:
11000
11000
00100
00011

Output: 3

*/

#include <bits/stdc++.h>
#include <climits>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

static const auto _=[](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);cout.tie(nullptr);
        return 0;
}();

class Solution {
public:
        int numIslands(vector<vector<char>>& grid) {
                int num_islands = 0;
                if (!grid.size()) return 0;

                long current_island_id = 1, ysize = (long)grid.size(), xsize = (long)grid[0].size();
                vector<long> upper_line(xsize, 0);

                for (int y = 0 ; y < ysize ; y++) {
                        debug_print("y = %d, num_islands is %d, upper line is %s\n", y, num_islands,
                        array2str(upper_line).c_str());
                        int prev_id = 0;
                        for (int x = 0 ; x < xsize ; x++) {
                                if (grid[y][x] == '0') {
                                        prev_id = 0;
                                        upper_line[x] = 0;
                                        continue;
                                }

                                // We are an island, shall we merge it to any adjacent island?
                                bool expand_horizontally = prev_id != 0;
                                bool expand_vertically = upper_line[x] != 0;
                                long island_id;
                                if (!expand_horizontally and !expand_vertically) {
                                        // no adjacent island
                                        num_islands +=1;
                                        island_id = current_island_id++;
                                } else if (expand_horizontally and !expand_vertically) {
                                        // simply expand the island horizontally
                                        island_id = prev_id;
                                } else if (!expand_horizontally and expand_vertically) {
                                        // simply expand the island vertically
                                        island_id = upper_line[x];
                                } else {
                                        // expand the island both horizontally and vertically
                                        if (prev_id == upper_line[x]) {
                                                island_id = prev_id;
                                        }
                                        else {
                                                // Both islands shall be merged
                                                num_islands -=1;
                                                island_id = prev_id;
                                                int to_replace = upper_line[x];
                                                for (int x1 = 0 ; x1 < xsize ; x1++)
                                                if (upper_line[x1] == to_replace)
                                                upper_line[x1] = island_id;
                                        }
                                }
                                upper_line[x] = island_id;
                                prev_id = island_id;
                        }
                }
                debug_print("num_islands is %d, upper line is %s\n", num_islands,
                array2str(upper_line).c_str());
                return num_islands;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<vector<string>> grid_str = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
        vector<vector<char>> grid;
        for (vector<string> line : grid_str) {
                vector<char> cline;
                for (string c : line)
                cline.push_back(c == "0" ? '0' : '1');
                grid.push_back(cline);
        }

        Solution s;
        int result = s.numIslands(grid);

        if (result == expected) return 0;

        printf("search(%s) returned %d but expected %d\n", array2str(grid_str).c_str(),
        result, expected);
        dev_assert(continue_on_failure);
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
