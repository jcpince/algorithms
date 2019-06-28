/*
Lexicographical order is often known as alphabetical order when dealing with strings. A string is greater than another string if it comes later in a lexicographically sorted list.

Given a word, create a new word by swapping some or all of its characters. This new word must meet two criteria:

    It must be greater than the original word
    It must be the smallest word that meets the first condition

For example, given the word
, the next largest word is

.

Complete the function biggerIsGreater below to create and return the new string meeting the criteria. If it is not possible, return no answer.

Function Description

Complete the biggerIsGreater function in the editor below. It should return the smallest lexicographically higher string possible from the given string or no answer.

biggerIsGreater has the following parameter(s):

    w: a string

Input Format

The first line of input contains
, the number of test cases.
Each of the next lines contains

.

Constraints

    will contain only letters in the range ascii[a..z].

Output Format

For each test case, output the string meeting the criteria. If no answer exists, print no answer.

Sample Input 0

5
ab
bb
hefg
dhck
dkhc

Sample Output 0

ba
no answer
hegf
dhkc
hcdk

Explanation 0

    Test case 1:
    ba is the only string which can be made by rearranging ab. It is greater.
    Test case 2:
    It is not possible to rearrange bb and get a greater string.
    Test case 3:
    hegf is the next string greater than hefg.
    Test case 4:
    dhkc is the next string greater than dhck.
    Test case 5:
    hcdk is the next string greater than dkhc.

Sample Input 1

6
lmno
dcba
dcbb
abdc
abcd
fedcbabcd

Sample Output 1

lmon
no answer
no answer
acbd
abdc
fedcbabdc

*/

#include <bits/stdc++.h>
#include <algorithm>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

string biggerIsGreater(string w) {

    const char *w_str = w.c_str();

    /* check if w is already max... */
    while (w_str[0] and (w_str[0] >= w_str[1])) w_str++;
    if (!*w_str) return "no answer";

    /* parse the buffer backwards from the end until we meet a character < the prev */
    w_str = &w.c_str()[w.length()-1];
    while (*(w_str-1) >= *w_str) w_str--;
    int pivot_index = (int)(--w_str - w.c_str());
    char pivot_value = *w_str;

    /* swap the character right above with or pivot */
    w_str = &w.c_str()[pivot_index];
    char *overload = (char*)w_str+1;
    while (*w_str++) if ((*w_str > pivot_value) and (*w_str < *overload)) overload = (char*)w_str;
    w_str = &w.c_str()[pivot_index];
    char c = overload[0];
    overload[0] = pivot_value;
    ((char*)w_str)[0] = c;

    /* now, sort the trailing part */
    string::iterator it = w.begin();
    while(pivot_index-- >= 0) it++;
    sort(it, w.end());

    debug_print("biggerIsGreater(%s), pivot_index = %d, w_str = %c\n", w.c_str(), pivot_index, *w_str);
    return w;
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    string input = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    string result = biggerIsGreater(input);
    if (result == expected) return 0;

    printf("biggerIsGreater(%s) returned %s but expected %s\n", input.c_str(), result.c_str(),
        expected.c_str());
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
