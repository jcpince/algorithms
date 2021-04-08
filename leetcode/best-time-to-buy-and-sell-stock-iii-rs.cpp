#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

extern "C" { int max_profit_rs(const int *prices, const int len); }

int run_test_case(void *__s, TestCase *tc) {
	UNUSED(__s);
	vector<int> prices = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
	int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

	int result = max_profit_rs(prices.data(), prices.size());

	if (result == expected) return 0;

	printf("max_profit_rs(%s, %ld) returned %d but expected %d\n",
		array2str(prices).c_str(), prices.size(), result, expected);
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
