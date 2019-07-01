/*
https://leetcode.com/problems/letter-combinations-of-a-phone-number/

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that
the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does
not map to any letters.

Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

const string mappings[] = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

class Solution {
private:
    const string& get_mapping(const char digit)
    {
        int mapping_number = digit - '2';
        return mappings[mapping_number];
    }
public:
    vector<string> letterCombinations(string digits) {
        if (digits.length() == 0) return {};

        vector<string> result;
        const char *digits_cstr = digits.c_str();
        const string mapping = get_mapping(*digits_cstr);
        for (char letter : mapping)
            result.push_back((string)"" + letter);
        while (*++digits_cstr) {
            const string mapping = get_mapping(*digits_cstr);
            size_t size = result.size();
            for (size_t jdx = 1 ; jdx < mapping.size() ; jdx++)
                for (size_t idx = 0 ; idx < size ; idx++)
                    result.push_back(result[idx] + mapping[jdx]);
            for (size_t idx = 0 ; idx < size ; idx++)
                result[idx] += mapping[0];
        }
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    string nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<string> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<string> result = s.letterCombinations(nums);
    if (result == expected) return 0;

    printf("letterCombinations(%s) returned %s but expected %s\n", nums.c_str(),
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
    return errors_count;
}
