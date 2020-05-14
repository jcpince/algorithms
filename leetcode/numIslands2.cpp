#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

static const auto _=[](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    return 0;
}();

class Solution {
        void swap_rows(int* (&row1), int* (&row2)) {
                int *tmp = row1;
                row1 = row2;
                row2 = tmp;
        }
public:
        int numIslands(vector<vector<char>>& grid) {
                map<int, int> cache;
                int rows = grid.size();
                if (!rows) return 0;

                int cols = grid[0].size(), nb_cells = rows*cols;
                int res = 0, id = 1;
                if (!nb_cells) return res;
                int row1[cols], row2[cols], *prev_row = row1, *row = row2;

                if (grid[0][0] == '1') {
                        prev_row[0] = ++id;
                        res++;
                        // printf("%d, %d: new island\n", 0, 0);
                } else prev_row[0] = 0;

                for (int idx = 1 ; idx < cols ; idx++) {
                        if (grid[0][idx] == '0') {
                                prev_row[idx] = 0;
                                continue;
                        }
                        if (prev_row[idx-1] == 0) {
                                // new island candidate
                                // printf("%d, %d: new island\n", 0, idx);
                                prev_row[idx] = ++id;
                                res++;
                        } else {
                                // same island
                                // printf("%d, %d: same island\n", 0, idx);
                                prev_row[idx] = id;
                        }
                }

                for (int idx = cols ; idx < nb_cells ; idx++) {
                        int row_idx = idx / cols;
                        int col = idx - row_idx * cols;

                        if (grid[row_idx][col] == '0') {
                                row[col] = 0;
                                if (col == cols-1) swap_rows(row, prev_row);
                                continue;
                        }

                        if (prev_row[col] == 0 &&
                                        (!col || row[col-1] == 0)) {
                                // new island candidate
                                // printf("%d, %d: new island\n", row_idx, col);
                                row[col] = ++id;
                                res++;
                        } else if (col && (!row[col-1] ||
                                        (prev_row[col] == row[col-1]))) {
                                // same island above
                                row[col] = prev_row[col];
                                // printf("%d, %d: same island\n", row_idx, col);
                        } else if (col && prev_row[col] &&
                                        prev_row[col] != row[col-1]) {
                                // merge island with upper one
                                row[col] = row[col-1];
                                // printf("%d, %d: merge islands\n", row_idx, col);
                                // then, propagate the new id
                                int old = prev_row[col];
                                for (int tmp = col+1 ; tmp < cols ; tmp++)
                                        if (prev_row[tmp] == old)
                                                prev_row[tmp] = row[col-1];
                                for (int tmp = 0 ; tmp < col ; tmp++)
                                        if (row[tmp] == old)
                                                row[tmp] = row[col-1];
                                res--;
                        } else if (!col && prev_row[col]) {
                                // same island as above
                                // printf("%d, %d: same island\n", row_idx, col);
                                row[col] = prev_row[col];
                        } else {
                                // same island as left
                                // printf("%d, %d: same island\n", row_idx, col);
                                row[col] = row[col-1];
                        }

                        if (col == cols-1) swap_rows(row, prev_row);
                }
                return res;
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

        printf("numIslands(%s) returned %d but expected %d\n",
                array2str(grid_str).c_str(), result, expected);
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

        int errors_id = uts.run_test_cases(tc_id, tests_ran);
        if (errors_id == 0)
        cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
        else
        cout << errors_id << " test(s) failed over a total of " << tests_ran << endl;

        return errors_id;
}
