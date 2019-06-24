/*
https://www.hackerrank.com/challenges/apple-and-orange/problem


Sam's house has an apple tree and an orange tree that yield an abundance of fruit. In the diagram
below, the red region denotes his house, where is the start point, and is the endpoint.
The apple tree is to the left of his house, and the orange tree is to its right. You can assume
the trees are located on a single point, where the apple tree is at point , and the orange tree is
at point.

Apple and orange(2).png

When a fruit falls from its tree, it lands
units of distance from its tree of origin along the -axis. A negative value of means the fruit
fell units to the tree's left, and a positive value of means it falls

units to the tree's right.

Given the value of
for apples and oranges, determine how many apples and oranges will fall on Sam's house (i.e., in
the inclusive range

)?

For example, Sam's house is between
and . The apple tree is located at and the orange at . There are apples and oranges. Apples are
thrown units distance from , and units distance. Adding each apple distance to the position of the
tree, they land at . Oranges land at . One apple and two oranges land in the inclusive range

so we print

1
2

Function Description

Complete the countApplesAndOranges function in the editor below. It should print the number of
apples and oranges that land on Sam's house, each on a separate line.

countApplesAndOranges has the following parameter(s):

    s: integer, starting point of Sam's house location.
    t: integer, ending location of Sam's house location.
    a: integer, location of the Apple tree.
    b: integer, location of the Orange tree.
    apples: integer array, distances at which each apple falls from the tree.
    oranges: integer array, distances at which each orange falls from the tree.

Input Format

The first line contains two space-separated integers denoting the respective values of
and .
The second line contains two space-separated integers denoting the respective values of and .
The third line contains two space-separated integers denoting the respective values of and .
The fourth line contains space-separated integers denoting the respective distances that each apple
falls from point .
The fifth line contains space-separated integers denoting the respective distances that each orange
falls from point

.

Constraints

Output Format

Print two integers on two different lines:

    The first integer: the number of apples that fall on Sam's house.
    The second integer: the number of oranges that fall on Sam's house.

Sample Input 0

7 11
5 15
3 2
-2 2 1
5 -6

Sample Output 0

1
1

Explanation 0

The first apple falls at position
.
The second apple falls at position .
The third apple falls at position .
The first orange falls at position .
The second orange falls at position .
Only one fruit (the second apple) falls within the region between and , so we print as our first
line of output.
Only the second orange falls within the region between and , so we print as our second line of
output.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

void countApplesAndOranges(int s, int t, int a, int b, vector<int> apples, vector<int> oranges,
    int &apples_count, int &oranges_count) {

        apples_count = 0;
        oranges_count = 0;
        for (int apple : apples)
        {
            apple += a;
            if ((apple >= s) and (apple <= t)) apples_count++;
        }
        for (int orange : oranges)
        {
            orange += b;
            if ((orange >= s) and (orange <= t)) oranges_count++;
        }
}

void countApplesAndOranges(int s, int t, int a, int b, vector<int> apples, vector<int> oranges) {

    int apples_count, oranges_count;
    countApplesAndOranges(s, t, a, b, apples, oranges, apples_count, oranges_count);
    cout << apples_count << endl << oranges_count << endl;
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> stab = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["stab"];
    vector<int> apples = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["apples"];
    vector<int> oranges = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["oranges"];
    assert(stab.size() == 4);
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
    assert(expected.size() == 2);

    int acount, ocount;
    countApplesAndOranges(stab[0], stab[1], stab[2], stab[3], apples, oranges, acount, ocount);
    if ((acount == expected[0]) and (ocount == expected[1])) return 0;

    string sapples = array2str(apples), soranges = array2str(oranges);
    printf("countApplesAndOranges(%d, %d, %d, %d, %s, %s) returned (%d, %d) but expected (%d, %d)\n",
        stab[0], stab[1], stab[2], stab[3], sapples.c_str(), soranges.c_str(), acount, ocount,
        expected[0], expected[1]);
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
