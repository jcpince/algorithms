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

class BinaryMatrix {
        vector<vector<int>> m;
public:
        BinaryMatrix(vector<vector<int>> &matrix) : m(matrix) {}
        vector<int> dimensions() {
                int y = m.size();
                int x = 0;
                if (y) x = m[0].size();
                return {y, x};
        }
        int get(int y, int x) { return m[y][x]; }
};

class Solution {
        int findFirstOne(BinaryMatrix &bm, int y, int xmax) {
                // printf("Dichotomy with y = %d, xmax = %d\n", y, xmax);
                if(!xmax) return -1;
                if (bm.get(y, 0)) return 0;
                int xmaxval = bm.get(y, xmax);
                // printf("[[%d, %d], [%d, %d]]\n", bm.get(0, 0), bm.get(0, 1),
                //               bm.get(1, 0), bm.get(1, 1));
                if (!xmaxval) return -1;
                if (xmax == 1) return xmaxval ? xmax : -1;

                int start = 1;
                while (start < xmax)
                {
                        int idx = start + (xmax - start) / 2;
                        int v = bm.get(y, idx-1);
                        if (!v && bm.get(y, idx)) return idx;
                        if (start + 1 == xmax) return !v && bm.get(y, xmax) ? xmax : -1;
                        if (v) xmax = idx;
                        else start = idx;
                }
                return -1;
        }
public:
        int leftMostColumnWithOne(BinaryMatrix &bm) {
                vector<int> dims = bm.dimensions();
                int left_most = -1, nb_rows = dims[0], y = 0;
                while (left_most && y < nb_rows) {
                        int r = findFirstOne(bm, y, left_most < 0 ? dims[1] -1 : left_most);
                        // printf("findFirstOne(%d, %d) returned %d\n", y,
                        //         (left_most < 0 ? dims[1]-1 : left_most), r);
                        if (r >= 0 && ((left_most < 0) || (r < left_most))) left_most = r;
                        y++;
                }
                return left_most;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<vector<int>> m = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        BinaryMatrix bm(m);
        int result = s.leftMostColumnWithOne(bm);

        if (result == expected) return 0;

        printf("leftMostColumnWithOne(%s) returned %d but expected %d\n",
                array2str(m).c_str(), result, expected);
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
