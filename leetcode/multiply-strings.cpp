#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define c2n(c) (int)(c - '0')
#define n2c(n) (char)(n + '0')
#define natpos(s, pos) (pos >= 0 ? c2n(s[pos]) : 0)

class Solution {
public:
        /*string multiply(const string num1, const string num2) {
                int idx2, len1, len2, carry = 0, digit_idx;
                len1 = num1.length();
                len2 = num2.length();

                if (len2 < len1)
                        return multiply(num1, num2);

                string inverted_result = "0";
                for (digit_idx = 0 ; digit_idx < len1 ; digit_idx++) {
                        int digit1 = num1[len1-digit_idx-1] - '0';
                        int digit_mult = 0;
                        printf("digit1 is %d\n", digit1);

                        for (int idx = 0 ; idx < digit_idx ; idx++) {
                                int digit2 = num2[len2 - 1 - idx] - '0';
                                printf("digit1 is %d, digit2 is %d\n",
                                        digit1, digit2);
                                digit_mult += digit1 * digit2;
                        }
                        printf("Append (%d+%d)%%10=(%d) to the result\n",
                                digit_mult, carry, (digit_mult + carry) % 10);
                        inverted_result += to_string((digit_mult + carry) % 10);
                        carry = digit_mult / 10;
                }
                return inverted_result;
        }*/
        string multiply(const string sA, const string sB) {
                int i = 0, lenA, lenB, carry = 0;
                lenA = sA.length();
                lenB = sB.length();

                if (lenA < lenB)
                        return multiply(sB, sA);

                const char *A = sA.c_str(), *B = sB.c_str();
                char *array = (char*)calloc(lenA + lenB + 2, sizeof(char));
                char *result = &array[lenA + lenB - 1];

                while(i < (lenA + lenB)) {
                        // S[n-i] = Sum(j=0 to i) { A[n-j] * B[n-(i-j)]} + r[i-1]
                        int Sx = 0;
                        for (int j = 0 ; j <= i ; j++) {
                                //printf("Sx = %d * %d\n",
                                //        natpos(A, lenA-1-j), natpos(B, lenB-1-(i-j)));
                                Sx += natpos(A, lenA-1-j) * natpos(B, lenB-1-(i-j));
                        }
                        Sx += carry;
                        *result = n2c(Sx % 10);
                        carry = Sx / 10;
                        result--;
                        i++;
                        //printf("S[%d] = %d, new carry is %d\n", lenA-i, Sx, carry);
                }
                result++;
                while (*result == '0' && result[1]) result++;
                //printf("Returns %s\n", result);
                string ans = string(result);
                free(array);
                return ans;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        string num1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["num1"];
        string num2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["num2"];
        string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        string result = s.multiply(num1, num2);

        if (result == expected) return 0;

        printf("multiply(%s, %s) returned %s but expected %s\n",
                num1.c_str(), num2.c_str(), result.c_str(), expected.c_str());
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
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;

        return errors_count;
}
