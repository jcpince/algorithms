/*71. Simplify Path
Medium

Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.

In a UNIX-style file system, a period '.' refers to the current directory. Furthermore, a double period '..' moves the directory up a level.

Note that the returned canonical path must always begin with a slash '/', and there must be only a single slash '/' between two directory names. The last directory name (if it exists) must not end with a trailing '/'. Also, the canonical path must be the shortest string representing the absolute path.

Example 1:

Input: path = "/home/"
Output: "/home"
Explanation: Note that there is no trailing slash after the last directory name.
Example 2:

Input: path = "/../"
Output: "/"
Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
Example 3:

Input: path = "/home//foo/"
Output: "/home/foo"
Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
Example 4:

Input: path = "/a/./b/../../c/"
Output: "/c"
 

Constraints:

1 <= path.length <= 3000
path consists of English letters, digits, period '.', slash '/' or '_'.
path is a valid Unix path.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#ifndef debug_print
#define debug_print(...)
#endif

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    string simplifyPath(string path) {
        debug_print("%s(%s)\n", __func__, path.c_str());
        if (path.length() < 2) return path;

        const char *p = path.c_str();
        char canonical[path.length()+2];
        /* ptr starts at 1 and sets the first to 0 so we know to stop when
         * roling back one directory
         */
        char *ptr = &canonical[1];
        canonical[0] = 0;

        /* DEBUG */
#if DEBUG
        assert(*p == '/');
        memset(canonical, 0, path.length()+1);
#endif
    

        while (*p) {
            if (*p == '/' and p[1] == '.' and (!p[2] or p[2] == '/')) {
                // /./ or final /.
                debug_print("just skip %c%c\n", p[0], p[1]);
                p += 2;
            }
            else if (*p == '/' and (!p[1] or p[1] == '/')) {
                // //
                debug_print("just skip %c%c\n", p[0], p[1]);
                p += 1;
            }
            else if (*p == '/' and p[1] == '.' and p[2] == '.' and (!p[3] or p[3] == '/')) {
                // move canonical path back wards 1 level
                debug_print("move '%s' one folder back to ", &canonical[1]);
                if (*(ptr - 1)) {
                    ptr--;
                    while (*ptr and *ptr != '/') ptr--;
                }
                p += 3;

                /* DEBUG */
#if DEBUG
                *ptr = 0;
#endif
                debug_print("'%s' (ptr = %p, canonical = %p)\n",
                    &canonical[1], ptr, &canonical[1]);
            } else {
                debug_print("Build up '%s' with %c to ", &canonical[1], *p);
                *ptr++ = *p++;
                debug_print("'%s'\n", &canonical[1]);
            }
        }
        if (ptr == &canonical[1]) {
            /* empty */
            debug_print("Returns /\n\n");
            return "/";
        }

        *ptr = 0;
        debug_print("Returns '%s'\n\n", &canonical[1]);
        return &canonical[1];
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        string path = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        string result = _s.simplifyPath(path);

        if (result == expected) return 0;

        printf("simplifyPath(%s) returned %s but expected %s\n",
            path.c_str(), result.c_str(), expected.c_str());
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
                cout << errors_count << " test(s) failed over a total of "
                        << tests_ran << endl;

        return errors_count;
}