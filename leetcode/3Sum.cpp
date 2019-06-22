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
#include <cassert>
#include <vector>
#include <set>

#include <UnitTests.h>

using namespace std;

//#define DEBUG 1
#undef DEBUG
#ifdef DEBUG
#define vectorat(v, idx) v[idx]
#define debug_print printf
#define dev_assert assert
#else
#define vectorat(v, idx) v.at(idx)
#define debug_print(...)
#define dev_assert(...)
#endif

string array2str(vector<int> &nums);
string array2str(vector<vector<int>> &vnums);

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

const bool continue_on_failure = false;

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

    bool find_third(int value, vector<int>::iterator start, vector<int>::iterator end)
    {
        while (start < end)
        {
            if (*start == value)
                return true;
            start++;
        }
        return false;
    }

    /* binary search / dichotomy */
    int find_third(vector<int> nums, int value, int start, int end)
    {
#ifdef DEBUG
        string sin = array2str(nums);
        debug_print("find_third(%s, %d, %d, %d)...\n", sin.c_str(), value, start, end);
#endif
        int middle = start + (end - start + 1) / 2;
        while (middle < end)
        {
            debug_print("Value %d, sme(%d, %d, %d)\n", value, start, middle, end);
            if (nums[middle] > value)
                end = middle;
            else
                start = middle;
            if (nums[middle] == value)
                return middle;
            middle = start + (end - start + 1) / 2;
        }
        return -1;
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) return {};

        set<uint64_t> results;
        vector<int>::iterator it1, it2, it_start, it_end;
        sort(nums.begin(), nums.end());
        it_start = nums.begin();
        it_end = nums.end();
        int first0 = (*it_start)-1;

        int start_idx = 0, end_idx = nums.size();
        for (it1 = it_start ; it1 < it_end ; it1++, start_idx++)
        {
            int first = *it1, second0 = -1;
            if (it1 < (it_end-1)) second0 = *(it1+1) - 1;
            if (first == first0) continue;
            first0 = first;
            int idx2 = start_idx + 1;
            for (it2 = it1+1 ; it2 < it_end ; it2++, idx2++)
            {
                int found;
                int second = *it2;
                if (second == second0) continue;
                int third = 0 - first - second;
                debug_print("Check the triplet(%d, %d, %d)\n", first, second, third);
                uint64_t encoded;
                encode(encoded, first, second, third);

                if (results.find(encoded) != results.end()) continue; /* already there... */

                if (third < first)
                {
                    found = find_third(nums, third, 0, start_idx-1);
                }
                else if (third < second)
                {
                    found = find_third(nums, third, start_idx+1, idx2-1);
                }
                else found = find_third(nums, third, idx2+1, end_idx);

                if (found != -1)
                {
                    debug_print("Insert %d, %d, %d\n", first, second, third);
                    results.insert(encoded);
                }

                /* Update second0 so we don't endup looking more than once for a+b+b*/
                second0 = second;
            }
        }
        return set2vector(results);
    }
};

bool check_result(vector<vector<int>> &result, vector<vector<int>> &expected)
{
    if (result.size() != expected.size()) return false;
    for (vector<int> v : result)
    {
        bool found = false;
        for (vector<int> e : expected)
        {
            size_t idx = 0;
            for ( ; idx < e.size() ; idx++)
            {
                if (vectorat(e, idx) != vectorat(v, idx)) break;
            }
            if (idx == e.size()) { found = true; break; }
        }
        if (!found) return false;
    }
    return true;
}

string array2str(vector<int>& nums)
{
    string s = "[";
    for (int i : nums)
        s += to_string(i) + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

string array2str(vector<vector<int>> &vnums)
{
    string s = "[";
    for (vector<int> v : vnums)
        s += array2str(v) + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

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
