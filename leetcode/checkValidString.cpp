#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
        bool recurse(const char *s, int count) {
                if (!*s) return count == 0;
                if (count < 0) return false;

                if (*s == '*')
                        return recurse(s+1, count) ||
                                recurse(s+1, count+1) || recurse(s+1, count-1);

                return recurse(s+1, count + (*s == '(' ? 1 : -1));
        }
public:
        bool checkValidString(string s) {
                int lo = 0, hi = 0;
                for (char c: s) {
                        lo += c == '(' ? 1 : -1;
                        hi += c != ')' ? 1 : -1;
                        if (hi < 0) break;
                        lo = max(lo, 0);
                }
                return lo == 0;
        }
        bool checkValidString2(string s) {

                return recurse(s.c_str(), 0);
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        string str = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        bool result = s.checkValidString(str);

        if (result == expected) return 0;

        printf("checkValidString(%s) returned %d but expected %d\n",
                str.c_str(), result, expected);
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
