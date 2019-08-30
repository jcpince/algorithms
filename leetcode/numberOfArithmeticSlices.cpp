#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    void getDistinctArithmeticSlicesSizes(vector<int>& A, vector<int>& slices_sizes) {
        int idx0 = 0, idx1, delta = A[idx0+1] - A[idx0];
        for (idx1 = 1 ; idx1 < (int)A.size() ; idx1++) {
            if (A[idx1] != (A[idx1-1] + delta)) {
                //printf("Check segment from idx0(%d) to idx1(%d)\n", idx0, idx1-1);
                if ((idx1 - idx0) > 2) {
                    // printf("New slice from %d to %d: [", idx0, idx1-1);
                    // for (int i = max(idx0 - 1, 0) ; i < min(idx1 + 1, (int)A.size()-1) ; i++)
                    //     printf("%d,", A[i]);
                    // printf("]\n");
                    slices_sizes.push_back(idx1 - idx0);
                }
                idx0 = idx1-1;
                if (idx1 < ((int)A.size() - 1)) delta = A[idx0+1] - A[idx0];
            }
        }
        idx1--;
        //printf("Check last segment from idx0(%d) to idx1(%d)\n", idx0, idx1);
        if (A[idx1] == (A[idx1-1] + delta)) {
            if ((idx1 - idx0) > 1) slices_sizes.push_back(idx1 - idx0 + 1);
        }
    }
public:
    int numberOfArithmeticSlices_slow(vector<int>& A) {
        if (A.size() < 3) return 0;

        vector<int> slices_sizes;
        getDistinctArithmeticSlicesSizes(A, slices_sizes);

        sort(slices_sizes.begin(), slices_sizes.end());
        int slice_size0 = 0, nbsubslices, ans = 0;
        for (int slice_size : slices_sizes) {
            //printf("slice_size: %d\n", slice_size);
            if (slice_size0 != slice_size) {
                int nbsubslice = slice_size - 3 + 1;
                nbsubslices = 0;
                while (nbsubslice) nbsubslices += nbsubslice--;
            }
            ans += nbsubslices;
            slice_size0 = slice_size;
        }
        return ans;
    }
    int numberOfArithmeticSlices(vector<int>& A) {
        int ans = 0;
        if (A.size() < 3) return 0;

        int slice, slice0 = 0;
        for (int idx = 2 ; idx < (int)A.size() ; idx++) {
            slice = ((A[idx] - A[idx-1]) == (A[idx-1] - A[idx-2])) ? slice0 + 1 : 0;
            ans += slice;
            slice0 = slice;
        }
        return ans;

    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> A = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.numberOfArithmeticSlices(A);

    if (result == expected) return 0;

    printf("numberOfArithmeticSlices(%s) returned %d but expected %d\n", array2str(A).c_str(),
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
