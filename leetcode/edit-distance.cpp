/*
72. Edit Distance
Hard

Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:
Insert a character
Delete a character
Replace a character
 

Example 1:
Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

Example 2:
Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:
0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.

A table can be used to represent the distance.
distance[m, n] is the min distance between the m first
characters of the word1 and the n first characters of word2.
So distance[0,0] is the distance between 0 characters in word1 and word2 (=> 0).
distance[1,0] is the distance between the first character of word1 and no character of word2 (=>1)
distance[0,1] is the distance between the first character of word2 and no character of word1 (=>1)
distance[1,1] is the distance between the first character of word1 and the first character of word2 (=>1 if they are different else 0)

if(word1[m-1] == word2[n-1])
    // This is the distance of (m-1,n-1)
    distance[m,n] = min(distance[m-1,n-1])
else
    distance[m,n] = 1 + min(distance[m-1,n], min(distance[m-1,n-1], distance[m,n-1]))
*/

#define DEBUG 1
//#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>
#include <bits/stdc++.h>

const bool continue_on_failure = true;
using namespace std;

#if !DEBUG
#undef debug_print
#define debug_print(...)
#endif

class Solution {
    int editWord1(const char *word1, const char *word2, int current, int best) {
        if (current >= best) return best;

        // Same letters costs nothing
        while (*word1 and *word1 == *word2) {word1++;word2++;}

        if (! *word2) {
            // if word2 is empty, remove all the letters from word1
            while (*word1++) current++;
            return min(current, best);
        }

        if (! *word1) {
            // if word1 is empty, remove all the letters from word2
            while (*word2++) current++;
            return min(current, best);
        }

        // Insert the next letter of word2
        int resInsert = editWord1(word1, word2+1, current+1, best);
        // Delete the next letter of word1
        int resDelete = editWord1(word1+1, word2, current+1, best);
        // Replace the next letter of word1 with word2
        int resReplace = editWord1(word1+1, word2+1, current+1, best);

        return min(best, min(resInsert, min(resDelete, resReplace)));
    }
public:
    int minDistance_rec(string &word1, string &word2) {
        debug_print("word1: %s, word2: %s\n", word1.c_str(), word2.c_str());
        return editWord1(word1.c_str(), word2.c_str(), 0, max(word1.length(), word2.length()));
    }
    int minDistance(string word1, string word2) {
        int m = word1.length(), n = word2.length();
        if (!m || !n) return m + n;
        
        const char *w1 = word1.c_str(), *w2 = word2.c_str();
        int distance[m+1][n+1];

        distance[0][0] = 0;
        for (int idx = 1 ; idx < m+1 ; idx++) distance[idx][0] = idx;
        for (int idx = 1 ; idx < n+1 ; idx++) distance[0][idx] = idx;

        for (int idx = 1 ; idx < m+1 ; idx++)
            for (int jdx = 1 ; jdx < n+1 ; jdx++) {
                if (w1[idx-1] == w2[jdx-1]) distance[idx][jdx] = distance[idx-1][jdx-1];
                else distance[idx][jdx] = 1 + min(distance[idx-1][jdx-1], min(distance[idx-1][jdx], distance[idx][jdx-1]));
            }
        return distance[m][n];
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        string word1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["word1"];
        string word2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["word2"];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        int result = _s.minDistance(word1, word2);

        if (result == expected) return 0;

        printf("minDistance(%s, %s) returned %d but expected %d\n",
            word1.c_str(), word2.c_str(), result, expected);
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