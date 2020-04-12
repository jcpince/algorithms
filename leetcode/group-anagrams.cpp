/*
Group Anagrams

Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

Note:

    All inputs will be in lowercase.
    The order of your output does not matter.

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
public:
        vector<vector<string>> groupAnagrams(const vector<string>& strs) {
                map<string, int> cache;
                vector<vector<string>> result;
                for (const string str : strs) {
                        string sorted = str;
                        sort(sorted.begin(), sorted.end());
                        if (cache.find(sorted) != cache.end()) {
                                /* already there */
                                result[cache[sorted]].push_back(str);
                        } else {
                                cache[sorted] = result.size();
                                result.push_back({str});
                        }
                }
                return result;
        }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<string> words = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<string>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<string>> result = s.groupAnagrams(words);

    if (result == expected) return 0;

    printf("groupAnagrams(%s) returned %s but expected %s\n",
        array2str(words).c_str(), array2str(result).c_str(),
        array2str(expected).c_str());
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
