/*
79. Word Search
Medium

Given an m x n board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where "adjacent" cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.


Example 1:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true


Example 2:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true


Example 3:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:
m == board.length
n = board[i].length
1 <= m, n <= 200
1 <= word.length <= 103
board and word consists only of lowercase and uppercase English letters.
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
    int inline encode(const int row, const int col) {
        return row << 16 | col;
    }
    bool dfs(vector<vector<char>>& board, const int rows, const int cols,
        const char *s, int row, int col, set<int> &visited) {
        if (row < 0 or col < 0 or (row > (rows-1)) or (col > (cols-1))) return false;
        int pos_code = encode(row, col);
        if (*s != board[row][col] or visited.find(pos_code) != visited.end()) return false;
        if (!s[1]) return true;
        
        visited.insert(pos_code);
        if (dfs(board, rows, cols, s+1, row-1, col, visited) or
            dfs(board, rows, cols, s+1, row, col-1, visited) or
            dfs(board, rows, cols, s+1, row+1, col, visited) or
            dfs(board, rows, cols, s+1, row, col+1, visited)) return true;
        
        visited.erase(pos_code);
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        const char *s = word.c_str();
        int row = 0, col, rows = board.size(), cols = board[0].size();
        if (rows*cols < (int)word.length()) return false;
        
        for (vector<char> line : board) {
            col = 0;
            for (char c : line) {
                set<int> visited;
                if (c == *s and dfs(board, rows, cols, s, row, col, visited))
                    return true;
                col++;
            }
            row++;
        }
        return false;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<string>> sboard = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["board"];
    string word = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["word"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<vector<char>> board;
    for (vector<string> sv : sboard) {
        vector<char> sc;
        for (string s : sv)
            sc.push_back(s[0]);
        board.push_back(sc);
    }

    Solution s;
    int result = s.exist(board, word);

    if (result == expected) return 0;

    printf("exist(%s, %s) returned %d but expected %d\n", array2str(board).c_str(), word.c_str(),
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