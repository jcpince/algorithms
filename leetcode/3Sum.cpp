// 15. 3Sum
// Medium
//
// Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
//
// Note:
//
// The solution set must not contain duplicate triplets.
//
// Example:
//
// Given array nums = [-1, 0, 1, 2, -1, -4],
//
// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <set>

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

//#define DEBUG 1
#undef DEBUG

void inline encode(uint64_t &encoded, int first, int second, int third)
{
    int upper = min(min(first, second), third);
    int lower;
    if (upper == first) lower = min(second, third);
    else if (upper == second) lower = min(first, third);
    else lower = min(first, second);
    encoded = ((uint64_t)upper << 32) | ((uint64_t)lower & 0xffffffff);
    debug_print("encode(%d, %d, %d) => 0x%lx\n", first, second, third, encoded);
}

void inline decode(uint64_t encoded, int &first, int &second, int &third)
{
    first = (int)(encoded >> 32);
    second = (int)(encoded & 0xffffffff);
    third = 0 - first - second;
    debug_print("decode(0x%lx) => %d, %d, %d\n", encoded, first, second, third);
}

const bool continue_on_failure = true;

class Solution {
private:
    vector<vector<int>> set2vector(set<uint64_t> results)
    {
        vector<vector<int>> vresults;
        vresults.reserve(results.size());
        for (uint64_t encoded : results)
        {
            int first, second, third;
            decode(encoded, first, second, third);
            vector<int> result = {first, second, third};
            vresults.push_back(result);
        }
        return vresults;
    }

public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};

        set<uint64_t> results;
        uint64_t encoded;
        sort(nums.begin(), nums.end());

        //printf("Sorted array is %s\n", array2str(nums).c_str());

        int smallest = nums.front(), biggest = nums.back();
        int end_idx = nums.size() - 1;

        int first0 = smallest - 1;

        for (int idx1 = 0 ; idx1 < end_idx-1 ; idx1++)
        {
            int first = vectorat(nums, idx1), second0 = first0;
            if (first == first0) continue;
            if (first > 0) break;
            first0 = first;

            int found0 = end_idx+1;
            //first_found0 = end_idx + 1;
            //printf("Second loop with idx1 %d\n", idx1);
            for (int idx2 = idx1 + 1 ; idx2 < end_idx ; idx2++)
            {
                int second = vectorat(nums, idx2);
                if (second == second0) continue;
                if ((first + second) > 0) break;
                second0 = second;

                int third = 0 - first - second;
                if (third < smallest || third > biggest) continue;

                encode(encoded, first, second, third);

                if (results.find(encoded) != results.end()) continue;

                /*printf("Candidate (%d, %d, %d) - search %d between %d and %d\n",
                    first, second, third, third, idx2+1, found0-1);*/
                int found = find_element(nums, third, idx2+1, found0-1);

                //printf("Here third is %d, idx1(%d), idx2(%d), found0(%d) => %d\n", third, idx1, idx2, found0, found);
                if (found != -1)
                {
                    //printf("Found is %d, Insert %d, %d, %d\n", found, first, second, third);
                    // printf("Found is %d, Insert %d, %d, %d\n", found, first, second, third);
                    assert(found < found0);
                    results.insert(encoded);
                    found0 = found;
                    //if (first_found0 == (end_idx+1)) first_found0 = found0;
                }
            }
        }
        return set2vector(results);
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    vector<int> in = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<vector<int>> result = ((Solution *)_s)->threeSum(in);
    if (check_result(result, expected)) return 0;

    string sin = array2str(in), sout = array2str(result), sexp = array2str(expected);
    printf("threeSum(%s) returned %s but expected %s\n", sin.c_str(), sout.c_str(), sexp.c_str());
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    Solution s;
    int tests_ran = 0;
    const char *tc_id = NULL;

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
        cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
            endl;
        return -1;
    }

    UnitTests uts((void*)&s, &run_test_case, argv[1]);

    if (argc == 3) tc_id = argv[2];

    int errors_count = uts.run_test_cases(tc_id, tests_ran);
    if (errors_count == 0)
        cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
    else
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;
    return errors_count;
}
