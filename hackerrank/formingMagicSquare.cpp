/*
https://www.hackerrank.com/challenges/magic-square-forming/problem

We define a magic square to be an matrix of distinct positive integers from to where the sum of any row, column, or diagonal of length

is always equal to the same number: the magic constant.

You will be given a
matrix of integers in the inclusive range . We can convert any digit to any other digit in the range at cost of . Given

, convert it into a magic square at minimal cost. Print this cost on a new line.

Note: The resulting magic square must contain distinct integers in the inclusive range

.

For example, we start with the following matrix

:

5 3 4
1 5 8
6 4 2

We can convert it to the following magic square:

8 3 4
1 5 9
6 7 2

This took three replacements at a cost of

.

Function Description

Complete the formingMagicSquare function in the editor below. It should return an integer that represents the minimal total cost of converting the input square to a magic square.

formingMagicSquare has the following parameter(s):

    s: a

    array of integers

Input Format

Each of the lines contains three space-separated integers of row

.

Constraints

Output Format

Print an integer denoting the minimum cost of turning matrix

into a magic square.

Sample Input 0

4 9 2
3 5 7
8 1 5

Sample Output 0

1

Explanation 0

If we change the bottom right value,
, from to at a cost of ,

becomes a magic square at the minimum possible cost.

Sample Input 1

4 8 2
4 5 7
6 1 6

Sample Output 1

4

Explanation 1

Using 0-based indexing, if we make

-> at a cost of -> at a cost of -> at a cost of

    ,

then the total cost will be
.
*/

#include <bits/stdc++.h>
#include <climits>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

vector<vector<vector<int>>> cache = {
    {{2,7,6},{9,5,1},{4,3,8}},
    {{2,9,4},{7,5,3},{6,1,8}},
    {{4,3,8},{9,5,1},{2,7,6}},
    {{4,9,2},{3,5,7},{8,1,6}},
    {{6,1,8},{7,5,3},{2,9,4}},
    {{6,7,2},{1,5,9},{8,3,4}},
    {{8,1,6},{3,5,7},{4,9,2}},
    {{8,3,4},{1,5,9},{6,7,2}}
};

bool isMagic(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    if (a == b or a == c or a == d or a == e or a == f or a == g or a == h or a == i) return false;
    if (b == c or b == d or b == e or b == f or b == g or b == h or b == i) return false;
    if (c == d or c == e or c == f or c == g or c == h or c == i) return false;
    if (d == e or d == f or d == g or d == h or d == i) return false;
    if (e == f or e == g or e == h or e == i) return false;
    if (f == g or f == h or f == i) return false;
    if (g == h or g == i) return false;
    if (h == i) return false;

    int sum = a+b+c;
    if ((d+e+f) != sum) return false;
    if ((g+h+i) != sum) return false;
    if ((a+e+i) != sum) return false;
    if ((g+e+c) != sum) return false;
    if ((a+d+g) != sum) return false;
    if ((b+e+h) != sum) return false;
    if ((c+f+i) != sum) return false;
    return true;
}

bool isMagic(vector<vector<int>> square)
{
    return isMagic(square[0][0], square[0][1], square[0][2],
        square[1][0], square[1][1], square[1][2],
        square[2][0], square[2][1], square[2][2]);
}

int formingMagicSquare(vector<vector<int>> arr) {

    if (isMagic(arr)) return 0;
    int best = INT_MAX;

    for (vector<vector<int>> sol : cache)
    {
        int delta = 0;
        for (int idx = 0 ; idx < 3 ; idx++)
            for (int jdx = 0 ; jdx < 3 ; jdx++)
                delta += abs(sol[idx][jdx] - arr[idx][jdx]);

        /* delta is > 0, so, if 1 is found, the is the best solution */
        if (delta == 1) return 1;
        best = min(best, delta);
    }
    return best;
}

void printAllPossibleSolutions()
{
    int n = 9, solutions_count = 0;
    for (int a = 1 ; a <= n ; a++)
        for (int b = 1 ; b <= n ; b++)
            for (int c = 1 ; c <= n ; c++)
                for (int d = 1 ; d <= n ; d++)
                    for (int e = 1 ; e <= n ; e++)
                        for (int f = 1 ; f <= n ; f++)
                            for (int g = 1 ; g <= n ; g++)
                                for (int h = 1 ; h <= n ; h++)
                                    for (int i = 1 ; i <= n ; i++)
                                        if (isMagic(a,b,c,d,e,f,g,h,i))
                                            {printf("{{%d,%d,%d},{%d,%d,%d},{%d,%d,%d}},\n",
                                                a,b,c,d,e,f,g,h,i);solutions_count++;}
    printf("Found %d solutions\n", solutions_count);
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> row0 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["row0"];
    vector<int> row1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["row1"];
    vector<int> row2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["row2"];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];
    assert(row0.size() == 3);
    assert(row1.size() == 3);
    assert(row2.size() == 3);
    vector<vector<int>> input = {row0, row1, row2};

    int result = formingMagicSquare(input);
    if (result == expected) return 0;

    string sinput = array2str(input);
    printf("formingMagicSquare(%s) returned %d but expected %d\n", sinput.c_str(), result, expected);
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
