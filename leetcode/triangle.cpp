#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define POSITIVE_TRIANGLE 0

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    int recurse(vector<vector<int>>& triangle, int rowid = 0, int index = 0, int cursum=0) {
        if (rowid == (int)triangle.size()) return cursum;
        if (index == (int)triangle[rowid].size()) return INT_MAX;

        return min(recurse(triangle, rowid+1, index, cursum + triangle[rowid][index]),
                  recurse(triangle, rowid+1, index+1, cursum + triangle[rowid][index]));
    }
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        return recurse(triangle);
    }
    typedef struct {
        int row, column;
    } triangle_elem_t;

    int minimumTotal3(vector<vector<int>>& triangle) {
        // consider the problem as the shortest path where each node has two neighbors only
        auto cmp = [](pair<int, triangle_elem_t> left, pair<int, triangle_elem_t> right) {
            return (left.first > right.first);
        };
        priority_queue<pair<int, triangle_elem_t>, vector<pair<int, triangle_elem_t>>,
            decltype(cmp)> pqueue(cmp);

        int sum = triangle[0][0], best_sum = INT_MAX;
        triangle_elem_t e = {0, 0};
        pqueue.push(make_pair(sum, e));
        while (!pqueue.empty()) {
            pair<int, triangle_elem_t> p = pqueue.top();
            pqueue.pop();
            e = p.second;
            sum = p.first;
            debug_print("explore e(%d, %d), sum is %d\n", e.row, e.column, sum);

#if POSITIVE_TRIANGLE
            // The following is ok if all elements of the triangle are > 0 => sum grows monotically
            if (sum >= best_sum) continue;

            if (e.row == (int)(triangle.size()-1)) {
                best_sum = sum;
                continue;
            }
#else
            if (e.row == (int)(triangle.size()-1)) {
                if (sum < best_sum) best_sum = sum;
                continue;
            }
#endif

            // First child node
            e.row += 1;
            pqueue.push(make_pair(sum + triangle[e.row][e.column], e));
            // Second child node
            e.column += 1;
            pqueue.push(make_pair(sum + triangle[e.row][e.column], e));
        }
        return best_sum;
    }

    int minimumTotal2(vector<vector<int>>& triangle) {

        if (triangle.size() == 1) return triangle[0][0];

        vector<int> best_paths = triangle.back();
        vector<vector<int>>::iterator it = triangle.end() - 2;
        int remaining_rows = triangle.size() - 1;
        while (remaining_rows) {
            //printf("best_paths %s\n", array2str(best_paths).c_str());
            for (int idx = 0 ; idx < remaining_rows ; idx++)
                best_paths[idx] = (*it)[idx] + min(best_paths[idx], best_paths[idx+1]);
            remaining_rows--;
            it--;
        }
        //printf("best_paths %s\n", array2str(best_paths).c_str());
        return best_paths[0];
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<vector<int>> triangle = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.minimumTotal2(triangle);

    if (result == expected) return 0;

    printf("minimumTotal(%s) returned %d but expected %d\n", array2str(triangle).c_str(),
        result, expected);
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
