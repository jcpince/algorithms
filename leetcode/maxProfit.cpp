#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    int rec_profit(vector<int>& prices, const int &fee, const int day = 0,
            const bool has_stock = false, int current_profit = 0) {

        if (day >= (int)prices.size()) return current_profit;

        if (has_stock) {
            // Choices are sell or keep
            int p0 = INT_MIN;
            if ((day+1) < (int)prices.size())    // cannot keep on the last day,
                                            // better would have been not to buy...
                p0 = rec_profit(prices, fee, day + 1, has_stock, current_profit);
            return max(p0, rec_profit(prices, fee, day + 1, false, current_profit + prices[day] - fee));

        } else {
            // Choices are buy or skip
            int p0 = INT_MIN;
            if ((day+1) < (int)prices.size()) // can skip on the last day
                p0 = rec_profit(prices, fee, day + 1, has_stock, current_profit);
            return max(p0, rec_profit(prices, fee, day + 1, true, current_profit - prices[day]));
        }
    }
    void rec_profit2(vector<int>& prices, const int &fee, vector<int>& cache, const int day = 0,
            int bought_at = -1, int current_profit = 0) {

        if (day >= (int)prices.size()) return;

        if (bought_at != -1) {
            // Choices are sell or keep
            if ((day+1) < (int)prices.size())    // cannot keep on the last day,
                                            // better would have been not to buy...
                rec_profit2(prices, fee, cache, day + 1, bought_at, current_profit);
            if ((prices[day] - bought_at) < fee) return;
            current_profit += prices[day] - fee;
            // If we have already a better path where we sold our stock, we can just stop
            if (current_profit > cache[day]) {
                cache[day] = current_profit;
                rec_profit2(prices, fee, cache, day + 1, -1, current_profit);
            }
        } else {
            // Choices are buy or skip
            if ((day+1) < (int)prices.size()) // can't skip on the last day
                rec_profit2(prices, fee, cache, day + 1, -1, current_profit);
            bought_at = prices[day];
            current_profit -= bought_at;
            rec_profit2(prices, fee, cache, day + 1, bought_at, current_profit);
        }
    }
public:
    int maxProfit2(vector<int>& prices, int fee) {
        vector<int> cache(prices.size(), 0);
        rec_profit2(prices, fee, cache);

        printf("cache: %s\n", array2str(cache).c_str());
        return cache.back();
    }

    int maxProfit(vector<int>& prices, int fee) {

        int len = (int)prices.size();
        if (len < 2) return 0;

        int buy = prices[0], sell = 0;
        for(int idx = 1 ; idx < len ; idx++)
        {
            buy = min(prices[idx] - sell, buy);
            sell = max(prices[idx] - buy - fee, sell);
        }
        return sell;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> prices = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["prices"];
    int fee = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["fee"];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.maxProfit(prices, fee);

    vector<int> p2;
    for (int idx = 0 ; idx < 50000 ; idx++)
        p2.push_back(idx+1);
    s.maxProfit(p2, fee);

    if (result == expected) return 0;

    printf("maxProfit(%s, %d) returned %d but expected %d\n", array2str(prices).c_str(), fee,
        result, expected);
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
