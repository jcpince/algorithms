/*
https://leetcode.com/problems/longest-absolute-file-path/

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext

The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing
a file file.ext.

The string
"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext

The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file
file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level
sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our
file system. For example, in the second example above, the longest absolute path is
"dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest
absolute path to file in the abstracted file system. If there is no file in the system, return 0.

Note:

    The name of a file contains at least a . and an extension.
    The name of a directory or sub-directory will not contain a ..

Time complexity required: O(n) where n is the size of the input string.

Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path
aaaaaaaaaaaaaaaaaaaaa/sth.png
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    int lengthLongestPath(string input) {
        int max_len = 0, current_dir_len = 0;
        const char *s = input.c_str();
        vector<string> current_dir;
        while (*s) {
            bool new_file = false;
            int rel_pos = 0;
            string name;
            while (*s and *s != '\n') {
                if (*s == '\t') rel_pos++;
                else name += *s;
                if (*s == '.') new_file = true;
                s++;
            }
            assert(rel_pos <= (int)current_dir.size());

            // Rewind if necessary
            while ((int)current_dir.size() > rel_pos) {
                current_dir_len -= current_dir.back().length() + 1;
                current_dir.pop_back();
            }
            if (!current_dir.size()) current_dir_len = 0;

            if (!new_file) {
                current_dir_len += name.length();
                if (current_dir.size()) current_dir_len++;
                current_dir.push_back(name);
                //printf("New dir %s at rel pos %d, current_dir_len is %d\n", name.c_str(),
                //  rel_pos, current_dir_len);

            } else {
                int filepath = current_dir_len + (int)name.length();
                if (current_dir.size()) filepath++;
                max_len = max(max_len, filepath);
                //printf("New file %s at rel pos %d, current_dir_len is %d\n", name.c_str(),
                //  rel_pos, current_dir_len);
            }

            if (*s) s++;
        }
        return max_len;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    string key = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.lengthLongestPath(key);

    if (result == expected) return 0;

    printf("lengthLongestPath(%s) returned %d but expected %d\n", key.c_str(),
        result, expected);
    dev_assert(continue_on_failure);
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
