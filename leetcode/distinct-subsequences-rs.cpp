#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

extern "C" { int num_distinct_rs(const char *s, const char *t); }

int numDistinct(const char *s, const char *t) {
	int tlen = strlen(t);
	int slen = strlen(s);
	if (slen < tlen) return 0;
	if (slen == tlen) {
		if (s == t) return 1;
		else return 0;
	}
	if (tlen == 0) return 1;

	int dp[slen+1];
	for (int i = 0 ; i < slen+1 ; i++) dp[i] = 1;

	for ( int i  = 1 ; i < tlen+1 ; i++) {
		int dp0 = dp[0];
		dp[0] = 0;
		for ( int j  = 1 ; j < slen+1 ; j++) {
			int _dp0 = dp[j];
			dp[j] = dp[j-1];
			if (s[j-1] == t[i-1])
				dp[j] += dp0;
			dp0 = _dp0;
		}
	}
	return dp[slen];
}

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        string s = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s"];
        string t = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["t"];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        int result = num_distinct_rs(s.c_str(), t.c_str());

        if (result == expected) return 0;

        printf("num_distinct_rs(%s, %s) returned %d but expected %d\n",
		s.c_str(), t.c_str(), result, expected);
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

/*const char* ucs[][2] = {
	{"baaab", "baab"},
	{"rabbbit", "rabbis"},
	{"rabbbit", "rabbit"},
	{"rbbbt", "rbbt"},
	{"rbbt", "rbt"},
	{"babgbag", "bag"},
	{"", ""}
};

int main(int argc, char **argv) {
	unsigned idx;

	for (idx = 0 ; idx < sizeof(ucs)/sizeof(ucs[0]) ; idx++) {
		int expected = numDistinct(ucs[idx][0], ucs[idx][1]);
		int rs_result = num_distinct_rs(ucs[idx][0], ucs[idx][1]);
		if (expected == rs_result)
			printf("num_distinct(%s, %s) returns %d\n",
				ucs[idx][0], ucs[idx][1], rs_result);
		else printf("num_distinct(%s, %s) returns %d instead of %d!!!\n",
			ucs[idx][0], ucs[idx][1], rs_result, expected);
	}
	return 0;
}*/
