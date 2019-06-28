/*
https://www.hackerrank.com/challenges/wet-shark-and-two-subsequences/problem

One day, Wet Shark was given an array . As always, he started playing with its subsequences.

When you came to know about this habit, you presented him a task of finding all pairs of subsequences, , which satisfies all of the following constraints. We will represent a pair of subsequence as and
and must be of same length, i.e.,
.
Please help Wet Shark determine how many possible subsequences and can exist. Because the number of choices may be big, output your answer modulo

.

Note:

    Two segments are different if there's exists at least one index

such that element

    is present in exactly one of them.
    Both subsequences can overlap each other.
    Subsequences do not necessarily have to be distinct

Input Format

The first line consists of 3 space-separated integers
, , , where denotes the length of the original array, , and and are as defined above.
The next line contains space-separated integers, , representing the elements of

.

Constraints

Output Format

Output total number of pairs of subsequences,
, satisfying the above conditions. As the number can be large, output it's modulo

Sample Input 0

4 5 3
1 1 1 4

Sample Output 0

3

Explanation 0

For array

there are three pairs of subsequences:

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

struct subsets_priv {
    vector<uint64_t> *v1;
    vector<uint64_t> *v2;
    size_t size;
};

#define initialize_subsets_priv(ss_priv, subset_size) {     \
        ss_priv.v1 = new vector<uint64_t>(subset_size+1);   \
        ss_priv.v2 = new vector<uint64_t>(subset_size+1);   \
        ss_priv.size = subset_size;                         \
    }

#define destroy_subsets_priv(ss_priv) \
    { delete ss_priv.v1; delete ss_priv.v2; }

/* Returns the number of subsets given an array size */
vector<uint64_t> *get_subsets_count(struct subsets_priv *p)
{
    vector<uint64_t> *v1 = p->v1, *v2 = p->v2;
    size_t subset_size = p->size;
    dev_assert(subset_size >= 1);

    vectorat((*v1), 0) = 1;
    vectorat((*v2), 0) = 1;
    vectorat((*v1), 1) = subset_size > 1 ? 2 : 1;
    if (subset_size > 1) vectorat((*v1), 2) = 1;

    vector<uint64_t> *old = v2, *current = v1;
    /* based on the fact that when the subset size increases, the number of subsets of a given
     * size is the sum of the previous size and size-1
     */
    for (size_t j = 2 ; j < subset_size; j++)
    {
        /* swap the vectors */
        vector<uint64_t> *tmp = current;
        current = old;
        old = tmp;

        for (size_t i = 1 ; i < j + 1 ; i++)
            vectorat((*current), i) = (vectorat((*old), i) + vectorat((*old), (i-1))) % (uint64_t)1e9;

        vectorat((*current), (j + 1)) = 1;
    }
    return current;
}

/* Returns the number of subsets of a given size and sum */
int getSubsetsSizeCount(vector<int> x, size_t target_size, int tsum, int curr_sum = 0,
    size_t curr_size = 0, size_t curr_idx = 0)
{
    debug_print("target_size(%ld), tsum(%d), curr_sum(%d), curr_size(%ld), curr_idx(%ld)\n",
         target_size, tsum, curr_sum, curr_size, curr_idx);
    /* stop conditions */
    if (curr_sum > tsum) return 0;
    if (curr_size == target_size) return curr_sum == tsum ? 1 : 0;
    if (curr_idx >= x.size()) return 0;

    int res;
    res = getSubsetsSizeCount(x, target_size, tsum, curr_sum + x[curr_idx],
        curr_size + 1, curr_idx + 1);
    res += getSubsetsSizeCount(x, target_size, tsum, curr_sum, curr_size,
        curr_idx + 1);
    return res;
}

bool getAllSubsetsCount(const vector<int> &x, const int &tsum, vector<uint64_t> &sizes, int curr_sum = 0,
    size_t curr_size = 0, size_t curr_idx = 0)
{
    bool res = false;
    debug_print("target_sum(%d), curr_sum(%d), curr_size(%ld), curr_idx(%ld)\n",
        tsum, curr_sum, curr_size, curr_idx);

    /* stop conditions */
    if (curr_sum > tsum) return false;
    if (curr_sum == tsum) {
        debug_print("index = %ld, increase count for size %ld\n", curr_idx, curr_size);
        sizes[curr_size-1]++;
        return true;
    }
    if (curr_idx < x.size()) {
        int elem = x[curr_idx++];
        res = getAllSubsetsCount(x, tsum, sizes, curr_sum, curr_size, curr_idx) +
            getAllSubsetsCount(x, tsum, sizes, curr_sum + elem, curr_size + 1, curr_idx);
    }
    return res;
}

int twoSubsequences(vector<int> x, int r, int s) {

    /*{
        //for (int idx = 1 ; idx <= 100 ; idx++)
        {
            subsets_priv priv;
            initialize_subsets_priv(priv, 100);
            vector<uint64_t> *v = get_subsets_count(&priv);
            printf("Size 50 %ld\n", (*v)[50]);
        }
        return 0;
    }*/

    /*
     * sum(ai + bi) = r => sum(ai) + sum(bi) = r
     * sum(ai - bi) = s => sum(ai) - sum(bi) = s
     * => 2*sum(ai) = r + s
     * => 2*sum(bi) = r - s
     */
    /* check if r+-s is odd => no solution */
    if ((r + s) % 2) return 0;
    if ((r - s) % 2) return 0;
    if (x.size() == 0) return 0;
    debug_print("r(%d), s(%d), x %s\n", r, s, array2str(x).c_str());

    sort(x.begin(), x.end());

    /* Filter out values which could be greater than (r - s) / 2 */
    int v = (r + s) / 2;
    while ((x.size() > 0) and (x.back() > v)) x.pop_back();
    if (x.size() == 0) return 0;
    printf("r(%d), s(%d), x filtered %s\n", r, s, array2str(x).c_str());

    if (x.front() == x.back())
    {
        debug_print("Duplicates x %s", array2str(x).c_str());
        subsets_priv A_priv, B_priv;
        if ( (((r - s) / 2) % x.front()) or (((r + s) / 2) % x.front()) ) {
            /* r +- s / 2 not divisible by x's elements */
            printf("\n");
            return 0;
        }
        int B_size = ((r - s) / 2) / x.front(), A_size = ((r + s) / 2) / x.front();
        initialize_subsets_priv(A_priv, x.size());
        initialize_subsets_priv(B_priv, x.size());
        vector<uint64_t> *B_sizes = get_subsets_count(&B_priv);
        debug_print(", B_sizes: %s\n", array2str(*B_sizes).c_str());
        vector<uint64_t> *A_sizes;
        if (s == 0) A_sizes = B_sizes;
        else A_sizes = get_subsets_count(&A_priv);
        uint64_t total = (((*A_sizes)[A_size] % (uint64_t)1e9) * ((*B_sizes)[B_size] % (uint64_t)1e9));
        destroy_subsets_priv(A_priv);
        destroy_subsets_priv(B_priv);
        return total % (uint64_t)1e9;
    }

    uint64_t total = 0;
    int B_sum = (r - s) / 2;
    vector<uint64_t> B_sizes(x.size());
    bool res = getAllSubsetsCount(x, B_sum, B_sizes);
    debug_print("B_sizes: %s\n", array2str(B_sizes).c_str());
    if (!res) return 0;

    int A_sum = (r + s) / 2;
    vector<uint64_t> A_sizes(x.size());
    if (!getAllSubsetsCount(x, A_sum, A_sizes)) return 0;
    debug_print("A_sizes: %s\n", array2str(A_sizes).c_str());

    for (size_t curr_size = 0 ; curr_size < x.size() ; curr_size++)
    {
        uint64_t bi_count = B_sizes[curr_size];
        debug_print("Found %d subsequences of size %ld with sum %d\n", bi_count, curr_size+1, B_sum);
        if (bi_count == 0) continue;
        uint64_t ai_count = A_sizes[curr_size];
        debug_print("Found %d subsequences of size %ld with sum %d\n", ai_count, curr_size+1, A_sum);

        total = (total + (ai_count * bi_count)) % (uint64_t)1e9;
    }
    return total;
}

int twoSubsequences_slow(vector<int> x, int r, int s) {

    /*
     * sum(ai + bi) = r => sum(ai) + sum(bi) = r
     * sum(ai - bi) = s => sum(ai) - sum(bi) = s
     * => 2*sum(ai) = r + s
     * => 2*sum(bi) = r - s
     */
    /* check if r+-s is odd => no solution */
    if ((r + s) % 2) return 0;
    if ((r - s) % 2) return 0;
    if (x.size() == 0) return 0;

    int ai_sum = (r + s) / 2, bi_sum = (r - s) / 2;

    sort(x.begin(), x.end());

    uint64_t total = 0;
    for (size_t curr_size = 1 ; curr_size < x.size() ; curr_size++)
    {
        int bi_count = getSubsetsSizeCount(x, curr_size, bi_sum);
        debug_print("Found %d subsequences of size %ld with sum %d\n", bi_count, curr_size, bi_sum);
        if (bi_count == 0) continue;
        int ai_count = getSubsetsSizeCount(x, curr_size, ai_sum);
        debug_print("Found %d subsequences of size %ld with sum %d\n", ai_count, curr_size, ai_sum);

        total = (total + (ai_count * bi_count)) % (uint64_t)1e9;
    }
    return total;
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> x = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["x"];
    int r = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["r"];
    int s = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s"];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    int result = twoSubsequences(x, r, s);
    if (result == expected) return 0;

    printf("twoSubsequences(%s, %d, %d) returned %d but expected %d\n", array2str(x).c_str(), r, s,
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
