#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    vector<vector<int>> kClosest_pq(vector<vector<int>>& points, int K) {
        if (K >= (int)points.size()) return points;

        auto cmp = [](pair<int, vector<int>> left, pair<int, vector<int>> right) {
            return (left.first > right.first);
        };
        priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>,
            decltype(cmp)> pqueue(cmp);

        for (int idx = 0 ; idx < (int)points.size() ; idx++) {
            int square_distance = points[idx][0]*points[idx][0] + points[idx][1]*points[idx][1];
            pqueue.push(make_pair(square_distance, points[idx]));
        }
        vector<vector<int>> result;
        for (int idx = 0 ; idx < K ; idx++) {
            pair<int, vector<int>> p = pqueue.top();
            result.push_back(p.second);
            pqueue.pop();
        }
        return result;
    }
    vector<vector<int>> kClosest_sepvector(vector<vector<int>>& points, int K) {
        if (K >= (int)points.size()) return points;
        vector<pair<int, int>> distances(points.size());

        struct closer {
            inline bool operator() (const pair<int, int>& p1, const pair<int, int>& p2) {
                return p1.first < p2.first;
            }
        };
        for (int idx = 0 ; idx < (int)points.size() ; idx++)
            distances[idx] = make_pair(points[idx][0] * points[idx][0] +
                                       points[idx][1] * points[idx][1], idx);

        sort(distances.begin(), distances.end(), closer());

        vector<vector<int>> result(K);
        for (int idx = 0 ; idx < K ; idx++)
            result[idx] = points[distances[idx].second];
        return result;
    }
    vector<vector<int>> kClosest_fullsort(vector<vector<int>>& points, int K) {
        if (K >= (int)points.size()) return points;


        struct closer
        {
            inline bool operator() (const vector<int>& p1, const vector<int>& p2)
            {
                return (p1[0] * p1[0] + p1[1] * p1[1]) < (p2[0] * p2[0] + p2[1] * p2[1]);
            }
        };
        sort(points.begin(), points.end(), closer());

        vector<vector<int>> result(points.begin(), points.begin()+K);
        return result;
    }
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        if (K >= (int)points.size()) return points;


        struct closer
        {
            inline bool operator() (const vector<int>& p1, const vector<int>& p2)
            {
                return (p1[0] * p1[0] + p1[1] * p1[1]) < (p2[0] * p2[0] + p2[1] * p2[1]);
            }
        };
        nth_element(points.begin(), points.begin()+K-1, points.end(), closer());
        points.resize(K);

        return points;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<vector<int>> points = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["points"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.kClosest(points, k);

    if (check_result(result, expected)) return 0;

    printf("kClosest(%s, %d) returned %s but expected %s\n", array2str(points).c_str(), k,
        array2str(result).c_str(), array2str(expected).c_str());
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
