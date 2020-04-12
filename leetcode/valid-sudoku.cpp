#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define c2n(c) (c - '0' - 1)

class Solution {
        int coord2box(int row, int col) {
                int xoff = col / 3;
                if (row < 3)
                        return xoff;
                else if (row < 6)
                        return 3 + xoff;
                else
                        return 6 + xoff;
        }

public:
        bool isValidSudoku(vector<vector<char>>& board) {
                int columns[9][9] = {{0}}, suboxes[9][9] = {{0}};
                int row_index = 0, box_index;

                for (const vector<char> row : board) {
                        int curr_row[9] = {0}, col_index = -1;
                        for ( char c : row) {
                                int num = c2n(c);
                                col_index++;
                                box_index = coord2box(row_index, col_index);
                                if (c == '.') continue;
                                // printf("board[%d][%d] is %d\n",
                                //         row_index, col_index, num+1);
                                if (curr_row[num]) {
                                        // printf("%c(%d) already in the row %d\n",
                                        //         c, num+1, row_index);
                                        return false;
                                }
                                if (columns[col_index][num]) {
                                        // printf("%c(%d) already in the col %d\n",
                                        //         c, num+1, col_index);
                                        return false;
                                }
                                if (suboxes[box_index][num]) {
                                        // printf("%c(%d) already in the box %d\n",
                                        //         c, num+1, box_index);
                                        return false;
                                }
                                curr_row[num] = 1;
                                columns[col_index][num] = 1;
                                suboxes[box_index][num] = 1;
                        }
                        row_index++;
                }
                return true;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<vector<string>> sboard = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["board"];
        bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        /* vector<vector<string>> to vector<vector<char>>*/
        vector<vector<char>> board;
        for ( vector<string> row : sboard) {
                vector<char> crow;
                for ( string num : row)
                        crow.push_back(num[0]);
                board.push_back(crow);
        }

        Solution s;
        bool result = s.isValidSudoku(board);

        if (result == expected) return 0;

        printf("isValidSudoku(%s) returned %d but expected %d\n",
                array2str(sboard).c_str(), result, expected);
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
