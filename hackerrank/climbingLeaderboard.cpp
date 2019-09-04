#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

int findIndex(vector<int> &scores, int l, int r, int score) {

    /*while (l <= r) {
        if (scores[l] <= score) return l;
        l++;
    }
    return r;*/
    while (l < r) {
        if ((l + 1) >= r) {
            //if (scores[r] == score) return r;
            if (scores[r] <= score) return r;
            return l;
        }
        int m = l + (r - l) / 2;
        if ((scores[m] == score) or
            (((m == 0) or (scores[m-1] > score))and (scores[m] < score))) return m;
        if (scores[m] < score) r = m;
        else l = m;
    }
    return r;
}

// Complete the climbingLeaderboard function below.
vector<int> climbingLeaderboard(vector<int> &scores, vector<int> &alice) {

    vector<int> ans(alice.size(), 1);
    if ((scores.size() == 0) || (alice.size() == 0)) return ans;

    vector<int> ranks(scores.size(), 1);
    int last_score = scores.front(), rank = 1, idx = 0;
    for (int new_score : scores) {
        if (new_score < last_score) rank++;
        ranks[idx++] = rank;
        last_score = new_score;
    }

    int alice_idx = 0;
    for (int new_score : alice) {
        if (new_score < scores.back()) {
            ans[alice_idx++] = ranks.back()+1;
        } else if (new_score >= scores.front()) {
            ans[alice_idx++] = 1;
        } else {
            int score_idx = findIndex(scores, 0, scores.size()-1, new_score);
            assert(score_idx >= 0);
            ans[alice_idx++] = ranks[score_idx];
        }
    }
    return ans;
}

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> scores = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["scores"];
    vector<int> alice = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["alice"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<int> result = climbingLeaderboard(scores, alice);

    if (check_result(result, expected)) return 0;

    printf("climbingLeaderboard(%s, %s) returned %s but expected %s\n", array2str(scores).c_str(),
        array2str(alice).c_str(), array2str(result).c_str(), array2str(expected).c_str());
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
