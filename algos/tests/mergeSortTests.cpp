#include <bits/stdc++.h>

#include <MergeSort.h>

//#define DEBUG 1
#undef DEBUG
#define PERF_TESTS_COUNT            1000
#define PERF_TESTS_ARRAY_SIZE       10000
#define PERF_TESTS_ARRAY_ITEM_RANGE 10000

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

void run_perf_tests() {

    vector<int> x(PERF_TESTS_ARRAY_SIZE);
    vector<int> expected(PERF_TESTS_ARRAY_SIZE), result(PERF_TESTS_ARRAY_SIZE);
    for (int test_count = 0 ; test_count < PERF_TESTS_COUNT ; test_count++)
    {
        for (int idx = 0 ; idx < PERF_TESTS_ARRAY_SIZE ; idx++) {
            int r = rand() % PERF_TESTS_ARRAY_ITEM_RANGE;
            expected[idx] = r;
            result[idx] = r;
            x[idx] = r;
        }
        sort(expected.begin(), expected.end());

        result = mergeSort(x);
        //sort(result.begin(), result.end());

        if (check_result(result, expected)) continue;

        printf("mergeSort(%s) returned %s but expected %s\n", array2str(x).c_str(),
            array2str(result).c_str(), array2str(expected).c_str());
        assert(continue_on_failure);
    }
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> x = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<int> result = mergeSort(x);
    if (check_result(result, expected)) return 0;

    printf("mergeSort(%s) returned %s but expected %s\n", array2str(x).c_str(),
        array2str(result).c_str(), array2str(expected).c_str());
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

    run_perf_tests();
    return errors_count;
}
