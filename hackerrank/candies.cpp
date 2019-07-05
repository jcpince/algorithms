/*
https://www.hackerrank.com/challenges/candies/problem

Candies
1207 more points to get your next star!
Rank: 72068|Points: 993/2200
Problem Solving

    Problem
    Submissions
    Leaderboard
    Discussions
    Editorial

Alice is a kindergarten teacher. She wants to give some candies to the children in her class.  All the children sit in a line and each of them has a rating score according to his or her performance in the class.  Alice wants to give at least 1 candy to each child. If two children sit next to each other, then the one with the higher rating must get more candies. Alice wants to minimize the total number of candies she must buy.

For example, assume her students' ratings are [4, 6, 4, 5, 6, 2]. She gives the students candy in the following minimal amounts: [1, 2, 1, 2, 3, 1]. She must buy a minimum of 10 candies.

Function Description

Complete the candies function in the editor below. It must return the minimum number of candies Alice must buy.

candies has the following parameter(s):

    n: an integer, the number of children in the class
    arr: an array of integers representing the ratings of each student

Input Format

The first line contains an integer,
, the size of .
Each of the next lines contains an integer indicating the rating of the student at position

.

Constraints

Output Format

Output a single line containing the minimum number of candies Alice must buy.

Sample Input 0

3
1
2
2

Sample Output 0

4

Explanation 0

Here 1, 2, 2 is the rating. Note that when two children have equal rating, they are allowed to have different number of candies. Hence optimal distribution will be 1, 2, 1.

Sample Input 1

10
2
4
2
6
1
7
8
9
2
1

Sample Output 1

19

Explanation 1

Optimal distribution will be

Sample Input 2

8
2
4
3
5
2
6
4
5

Sample Output 2

12

Explanation 2

Optimal distribution will be 12
*/

#include <bits/stdc++.h>
#include <climits>

#define DEBUG 1
//#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

long candies(int n, const vector<int> &arr) {

    UNUSED(n);
    if (!arr.size()) return 0;
    if (arr.size() == 1) return 1;

    vector<int> candies(arr.size());
    vector<int>::iterator cprevit = candies.begin(), cit = cprevit + 1;
    vector<int>::const_iterator aprevit = arr.begin(), ait = aprevit + 1;

    int current_candies = 1;
    *cprevit = current_candies;
    for ( ; ait < arr.end() ; ait++, cit++, cprevit++, aprevit++) {
        if ( *aprevit < *ait ) current_candies++;
        else current_candies = 1;
        *cit = current_candies;
    }

    ait = aprevit--;
    cit = cprevit--;
    long sum = 0;
    for ( ; ait > arr.begin() ; ait--, cit--, cprevit--, aprevit--) {
        sum += *cit;
        if ( ( *ait < *aprevit ) and ( *cit >= *cprevit ) ) *cprevit = *cit + 1;
    }
    sum += *cit;

    return sum;
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> ratings = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    int result = candies(ratings.size(), ratings);
    if (result == expected) return 0;

    printf("candies(%s) returned %d but expected %d\n", array2str(ratings).c_str(),
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
