/*
https://www.hackerrank.com/challenges/mandragora/problem

The evil forest is guarded by vicious mandragoras. Garnet and her pet must make a journey through.
She starts with health point () and

experience points.

As she encouters each mandragora, her choices are:

    Garnet's pet eats mandragora

. This increments by and defeats mandragora
.
Garnet's pet battles mandragora
. This increases by experience points and defeats mandragora

    .

Once she defeats a mandragora, it is out of play. Given a list of mandragoras with various health
levels, determine the maximum number of experience points she can collect on her journey.

For example, as always, she starts out with
health point and experience points. Mandragoras have the following health values: . For each of
the beings, she has two choices, at or

attle. We have the following permutations of choices and outcomes:

Action  s   p
_______ _   __
e, e, e 4   0
e, e, b 3   15
e, b, b 2   14
b, b, b 1   10
b, b, e 2   10
b, e, e 3   9
b, e, b 2   16
e, b, e 3   6

Working through a couple of rows, first, her pet can eat all three and she does not gain any
experience points. In the second row, her pet eats the first two to have
health points, then battles the beast with heatlth points to gain experience points. We see that
the best option is to eat the beast with points and battle the others to achieve

experience points.

Function Description

Complete the mandragora function in the editor below. It must return an integer that denotes the
maximum number of experience points that Garnet can earn.

mandragora has the following parameter(s):

    H: an array of integers that represents the health values of mandragoras

Input Format

The first line contains an integer,

, denoting the number of test cases. Each test case is described over two lines:

    The first line contains a single integer

, the number of mandragoras in the forest.
The second line contains
space-separated integers describing the respective health points for the mandragoras

    .

Constraints

, where The sum of all s in a single test case is

Output Format

For each test case, print a single line with an integer denoting the maximum number of experience
points that Garnet can earn.

Sample Input

1
3
3 2 2

Sample Output

10

Explanation

There are
mandragoras having the following health points: . Initially, and

. The following is an optimal sequence of actions for achieving the maximum number of experience
points possible:

    Eat the second mandragora (

). is increased from to , and is still
.
Battle the first mandragora (
). remains the same, but increases by
experience points.
Battle the third mandragora (
). remains the same, but increases by

    experience points.

Garnet earns
experience points.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

long mandragora2(vector<int> H, long s, long p, size_t start_index) {

    if (start_index == H.size()) return p;

    return max(mandragora2(H, s + 1, p, start_index+1),
        mandragora2(H, s, p + s * H[start_index], start_index+1));
}

long mandragora2(vector<int> &H) {

    sort(H.begin(), H.end());
    return mandragora2(H, 1, 0, 0);
}

long mandragora(vector<int> &H) {

    sort(H.begin(), H.end());
    long hsum = 0, p = 0, s = 1;
    for (auto h : H)
        hsum += h;

    for (auto h : H) {
        if ((s * hsum) > (s+1) * (hsum - h))
            p += s * h;
        else s += 1;
        hsum -= h;
    }
    return p;
}

long mandragora_bf(vector<int> H, vector<int> S, long s = 1, long p = 0) {

    // printf("%s(%s, %s, s(%ld), p(%ld))\n",
    //     __func__, array2str(H).c_str(), array2str(S).c_str(), s, p);

    if ((H.size() == 0) and (S.size() == 0)) return p;

    /* e or beat or skip the next in H or eat or beat or skip the next in skip */
    int h = -1;
    long p_eatS = 0, p_beatS = 0, p_skipS = 0, p_eatH = 0, p_beatH = 0, p_skipH = 0;
    if (H.size()) {
        h = H.back();
        H.pop_back();

        p_eatH = mandragora_bf(H, S, s + 1, p);
        p_beatH = mandragora_bf(H, S, s, p + s * h);

        S.emplace_back(h);
        p_skipH = mandragora_bf(H, S, s, p);
        S.pop_back();

        H.emplace_back(h);
    }
    if (S.size())
    {
        h = S.back();
        S.pop_back();
        p_eatS = mandragora_bf(H, S, s + 1, p);
        p_beatS = mandragora_bf(H, S, s, p + s * h);
        // if (H.size())
        // {
        //     S.emplace(S.begin(), h);
        //     p_skipS = mandragora(H, S, s, p);
        // }
    }
    return max(max(max(max(max(p_eatH, p_beatH), p_skipH), p_eatS), p_beatS), p_skipS);
}

long mandragora_bf(vector<int> &H) {

    vector<int> S;
    S.reserve(H.size());
    return mandragora_bf(H, S);
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> x = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    long expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    long result = mandragora(x);
    if (result == expected) return 0;

    printf("mandragora(%s) returned %ld but expected %ld\n", array2str(x).c_str(),
        result, expected);
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
