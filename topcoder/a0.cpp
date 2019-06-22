/*
Problem Statement

"Letter", "Legal", and "Tabloid" are examples of paper sizes. Both Letter and Legal are 8 and
half inches wide, but while Legal has length 14 inches, Letter is 11 inches long. This means that
14 letters have the same total length as 11 legals. Unless, of course, by "Letter" we mean
"Government Letter" or instead of "Legal" we want "Junior Legal". In the days of manual paper
making, the length of 11 inches was quite practical, as it is reportedly about a quarter of
"the average maximum stretch of an experienced vatman's arms". Luckily for you, this problem is
about a much more systematic way of cutting paper: the A series.

The papers in the A series are numbered A0, A1, A2, and so on until infinity. A0 is the largest
of these papers. The area of an A0 paper is exactly 1 square meter.

All paper sizes in the A series have the same aspect ratio. More precisely, the ratio between the
longer side and the shorter side of any paper in the A series is exactly equal to the
square root of 2.

For each i, the longer side of the A(i+1) paper is equal to the shorter side of the A(i) paper.

From the previous two definitions it follows that the A series has the following useful property:
Whenever you take an A(i) paper and you cut it in half (using a cut that passes through the centers
of its longer sides), you will get two pieces of an A(i+1) paper. In other words, A1 is one
half of A0, A2 is one half of A1, and so on.

You are given a A. A[i] represents the number of papers of size A(i) you have in stock.
For example, A[4] is the number of A4 papers you currently have.

You are not allowed to cut paper in any way. You can only connect papers (seamlessly and without
any waste) by taping them together. The papers you connect this way must not overlap. Can you take
some of the papers you have and assemble a paper of size A0? Return "Possible" if it can be done
and "Impossible" otherwise.

Definition
Class:
A0Paper
Method:
canBuild
Parameters:
int[]
Returns:
String
Method signature:
String canBuild(int[] A)
(be sure your method is public)
Limits
Time limit (s):
2.000
Memory limit (MB):
256
Notes
- The return value is case-sensitive. Make sure you return the string exactly as shown in the problem statement.
Constraints
- A will contain between 1 and 21 elements, inclusive.
- Each element of A will be between 0 and 220, inclusive.
Examples
0)
{0,3}
Returns: "Possible"
We have 0 pieces of A0 paper and 3 pieces of A1 paper. We can combine the two of the three A1 papers to get an A0.
1)
{0,1,2}
Returns: "Possible"
This time, we can combine two A2 papers to get a second A1. Afterwards, the two of A1s (the original one and the one we made from the two A2s) can be combined to obtain an A0.
2)
{0,0,0,0,15}
Returns: "Impossible"
An A0 paper can be assembled from 16 A4 papers, but here we only have 15.
3)
{2,0,0,0,0,0,0,3,2,0,0,5,0,3,0,0,1,0,0,0,5}
Returns: "Possible"
We already have two pieces of A0 paper, so we can just take one of them and we are done.
This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2003, TopCoder, Inc. All rights reserved.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

//#define DEBUG 1
#undef DEBUG
#ifdef DEBUG
#define debug_print printf
#define debug_assert assert
#else
#define debug_print(...)
#define debug_assert(...)
#define debug_print_papers(...)
#endif

const bool continue_on_failure = false;

class A0Paper
{
public:
    string canBuild(vector<int> A)
    {
        uint64_t missing = 1;
        for (int number : A)
            if (number >= missing) return "Possible";
            else missing = (missing - number) * 2;

        debug_print("Missing %ld papers\n", missing);
        return "Impossible";
    }
};

#ifdef DEBUG
void debug_print_papers(vector<int> &papers, bool succeeded)
{
    debug_print("canBuild(");
    for (int number : papers)
        debug_print("%d, ", number);
    if (succeeded)
        debug_print(") -> succeeded\n");
    else
        debug_print(") -> failed\n");
}
#endif

int check_solution(A0Paper &a0, vector<int> &papers, bool expected)
{

    string str_result = a0.canBuild(papers);
    bool succeeded = (expected == (str_result == "Possible"));
    debug_print_papers(papers, succeeded);
    if (succeeded)
        return 0;

    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    A0Paper a0;
    int errors = 0, tests_count = 0;
    vector<int> papers;

    papers = {0, 3}; errors += check_solution(a0, papers, true); tests_count++;
    papers = {0, 1, 2}; errors += check_solution(a0, papers, true); tests_count++;
    papers = {0,0,0,0,15}; errors += check_solution(a0, papers, false); tests_count++;
    papers = {2,0,0,0,0,0,0,3,2,0,0,5,0,3,0,0,1,0,0,0,5}; errors += check_solution(a0, papers, true); tests_count++;
    papers = {2,0,0,0,0,0,0,3,2,0,0,5,0,3,0,0,1,0,0,0,5}; errors += check_solution(a0, papers, true); tests_count++;

    /* Perfs test */
    papers = {0};
    for (int i = 0 ; i < 20 ; i++)
        papers.push_back(1);
    vector<int> papers2 = {0};
    for (int i = 0 ; i < 20 ; i++)
        papers2.push_back(1);
    papers2[20]++;
    vector<int> papers3 = {0};
    for (int i = 0 ; i < 20 ; i++)
        papers3.push_back(0);

    for (int i = 0 ; i < 400 ; i++)
    {
        errors += check_solution(a0, papers, false);
        errors += check_solution(a0, papers2, true);
        errors += check_solution(a0, papers3, false);
        tests_count++;
    }

    if (errors == 0)
        cout << "All tests succeeded!!!" << endl;
    else
        cout << errors << " tests failed over a total of " << tests_count << endl;
    return 0;
}
