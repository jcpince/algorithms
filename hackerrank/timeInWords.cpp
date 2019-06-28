/*
Given the time in numerals we may convert it into words, as shown below:

At
, use o' clock. For , use past, and for

use to. Note the space between the apostrophe and clock in o' clock. Write a program which prints the time in words for the input given in the format described.

Function Description

Complete the timeInWords function in the editor below. It should return a time string as described.

timeInWords has the following parameter(s):

    h: an integer representing hour of the day
    m: an integer representing minutes after the hour

Input Format

The first line contains
, the hours portion The second line contains

, the minutes portion

Constraints

Output Format

Print the time in words as described.

Sample Input 0

5
47

Sample Output 0

thirteen minutes to six

Sample Input 1

3
00

Sample Output 1

three o' clock

Sample Input 2

7
15

Sample Output 2

quarter past seven
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

const string first_thirty[] = {"o' clock", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen", "quarter", "sixteen", "seventeen", "eighteen", "nineteen",
    "twenty", "twenty one", "twenty two", "twenty three", "twenty four", "twenty five", "twenty six", "twenty seven", "twenty eight", "twenty nine",
    "half"};

string timeInWords(int h, int m) {

    assert(h > 0 and h <= 12);
    assert(m >= 0 and m < 60);

    if ((m % 15) == 0)
    {
        if (m == 0)
            return  first_thirty[h] + " " + first_thirty[m];
        if (m <= 30)
            return  first_thirty[m] + " past " + first_thirty[h];
        /* round the clock */
        h = h % 12;
        return  first_thirty[60 - m] + " to " + first_thirty[h + 1];
    }
    if (m == 1)
        return  first_thirty[m] + " minute past " + first_thirty[h];

    if (m < 30)
        return  first_thirty[m] + " minutes past " + first_thirty[h];

    /* finally, round the clock and... */
    h = h % 12;
    if (m == 59)
        return  first_thirty[60 - m] + " minute to " + first_thirty[h + 1];
    return  first_thirty[60 - m] + " minutes to " + first_thirty[h + 1];
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> input = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
    assert(input.size() == 2);

    string result = timeInWords(input[0], input[1]);
    if (result == expected) return 0;

    string sinput = array2str(input);
    printf("timeInWords(%s) returned %s but expected %s\n", sinput.c_str(), result.c_str(),
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
