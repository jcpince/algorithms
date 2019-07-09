

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define INITIAL_VALUE 1000000

class Solution {
    void find0(const vector<vector<int>>& matrix, int &x, int &y) {
        for (y = 0 ; y < (int)matrix.size() ; y++)
            for (x = 0 ; x < (int)matrix[y].size() ; x++)
                if (matrix[y][x] == 0) return;
    }
    void bfs(const vector<vector<int>>& matrix, vector<vector<int>> &result, int x0, int y0) {

        if (y0 < 0 or (y0+1) > (int)matrix.size()) return;
        if (x0 < 0 or (x0+1) > (int)matrix[y0].size()) return;

        // printf("x0 %d, y0 %d, matrix.size(%ld, %ld), result.size(%ld, %ld)\n", x0, y0,
        //     matrix[y0].size(), matrix.size(), result[y0].size(), result.size());
        int min_distance = result[y0][x0];
        if (matrix[y0][x0] == 0) min_distance = 0;
        else {
            if (x0 > 0)                         min_distance = min(result[y0][x0-1] + 1, min_distance);
            if ((x0+1) < (int)matrix[0].size()) min_distance = min(result[y0][x0+1] + 1, min_distance);
            if (y0 > 0)                         min_distance = min(result[y0-1][x0] + 1, min_distance);
            if ((y0+1) < (int)matrix.size())    min_distance = min(result[y0+1][x0] + 1, min_distance);
        }
        if (result[y0][x0] == min_distance) return;

        result[y0][x0] = min_distance;
        bfs(matrix, result, x0+1, y0);
        bfs(matrix, result, x0-1, y0);
        bfs(matrix, result, x0, y0+1);
        bfs(matrix, result, x0, y0-1);
    }
public:
    vector<vector<int>> updateMatrixSlow(vector<vector<int>>& matrix) {
        vector<vector<int>> result;
        for (vector<int> row : matrix)
            result.push_back(vector<int>(row.size(), INITIAL_VALUE));

        int x0 = 0, y0 = 0;
        find0(matrix, x0, y0);
        bfs(matrix, result, x0, y0);
        return result;
    }
    vector<vector<int>> updateMatrix2(vector<vector<int>>& matrix) {
        vector<vector<int>> result;
        for (vector<int> row : matrix)
            result.push_back(vector<int>(row.size(), INITIAL_VALUE));

        for (int y = 0 ; y < (int)matrix.size() ; y++)
            for (int x = 0 ; x < (int)matrix[y].size() ; x++) {
                if (matrix[y][x]) {
                    if (x > 0) result[y][x] = min(result[y][x], result[y][x-1] + 1);
                    if (y > 0) result[y][x] = min(result[y][x], result[y-1][x] + 1);
                }
                else result[y][x] = 0;
            }

        for (int y = (int)matrix.size() - 1 ; y >= 0 ; y--)
            for (int x = (int)matrix[y].size() - 1 ; x >= 0 ; x--) {
                if (matrix[y][x]) {
                    if ((x+1) < (int)matrix[y].size()) result[y][x] = min(result[y][x], result[y][x+1] + 1);
                    if ((y+1) < (int)matrix.size()) result[y][x] = min(result[y][x], result[y+1][x] + 1);
                }
            }
        return result;
    }
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {

        for (int y = 0 ; y < (int)matrix.size() ; y++)
            for (int x = 0 ; x < (int)matrix[y].size() ; x++) {
                if (matrix[y][x]) {
                    if (x > 0) matrix[y][x] = min(matrix[y][x] + 1, matrix[y][x-1] + 1);
                    if (y > 0) matrix[y][x] = min(matrix[y][x] + 1, matrix[y-1][x] + 1);
                }
                else matrix[y][x] = 0;
            }

        for (int y = (int)matrix.size() - 1 ; y >= 0 ; y--)
            for (int x = (int)matrix[y].size() - 1 ; x >= 0 ; x--) {
                if (matrix[y][x]) {
                    if ((x+1) < (int)matrix[y].size()) matrix[y][x] = min(matrix[y][x] + 1, matrix[y][x+1] + 1);
                    if ((y+1) < (int)matrix.size()) matrix[y][x] = min(matrix[y][x] + 1, matrix[y+1][x] + 1);
                }
            }
        return matrix;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> matrix = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.updateMatrix(matrix);

    if (check_result(result, expected)) return 0;

    printf("updateMatrix(%s) returned %s but expected %s\n", array2str(matrix).c_str(),
        array2str(result).c_str(), array2str(expected).c_str());
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
