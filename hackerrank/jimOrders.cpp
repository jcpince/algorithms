/*
https://www.hackerrank.com/challenges/jim-and-the-orders/problem

Jim's Burgers has a line of hungry customers. Orders vary in the time it takes to prepare them.
Determine the order the customers receive their orders. Start by numbering each of the customers
from to

, front of the line to the back. You will then be given an order number and a preparation time for
each customer.

The time of delivery is calculated as the sum of the order number and the preparation time. If two
orders are delivered at the same time, assume they are delivered in ascending customer number order.

For example, there are
customers in line. They each receive an order number and a preparation time

.:

Customer	1	2	3	4	5
Order #		8	5	6	2	4
Prep time	3	6	2	3	3
Calculate:
Serve time	11	11	8	5	7

We see that the orders are delivered to customers in the following order:

Order by:
Serve time	5	7	8	11	11
Customer	4	5	3	1	2

Function Description

Complete the jimOrders function in the editor below. It should return an array of integers that
represent the order that customers' orders are delivered.

jimOrders has the following parameter(s):

    orders: a 2D integer array where each

is in the form

    .

Input Format

The first line contains an integer
, the number of customers.
Each of the next lines contains two space-separated integers, an order number and prep time for

.

Constraints

Output Format

Print a single line of
space-separated customer numbers (recall that customers are numbered from to

) that describes the sequence in which the customers receive their burgers. If two or more
customers receive their burgers at the same time, print their numbers in ascending order.

Sample Input 0

3
1 3
2 3
3 3

Sample Output 0

1 2 3

Explanation 0

Jim has the following orders:

. This order is delivered at time
.
. This order is delivered at time
.
. This order is delivered at time

    .

The orders were delivered in the same order as the customers stood in line. The index in

is the customer number and is what is printed. In this case, the customer numbers match the order
numbers.

Sample Input 1

5
8 1
4 2
5 6
3 1
4 3

Sample Output 1

4 2 5 1 3

Explanation 1

Jim has the following orders:

. This order is delivered at time
.
. This order is delivered at time
.
. This order is delivered at time
.
. This order is delivered at time
.
. This order is delivered at time

    .

When we order these by ascending fulfillment time, we get:

: customer
.
: customer
.
: customer
.
: customer
.
: customer

    .

We print the ordered numbers in the bulleted listed above as 4 2 5 1 3.

Note: While not demonstrated in these sample cases, recall that any orders fulfilled at the same
time must be listed by ascending order number.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define COUNT_ITERATIONS 1

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

struct less_than_order
{
    inline bool operator() (const vector<int>& order1, const vector<int>& order2)
    {
        if (order1[2] == order2[2]) return order1[3] < order2[3];
        return order1[2] < order2[2];
    }
};

vector<int> jimOrders(vector<vector<int>> &orders) {

    for (size_t idx = 0 ; idx < orders.size() ; idx++) {
        orders[idx].push_back(orders[idx][0] + orders[idx][1]);
        orders[idx].push_back(idx+1);
    }

    debug_print("jimOrders(%s)\n", array2str(orders).c_str());
    sort(orders.begin(), orders.end(), less_than_order());

    vector<int> result;
    for (size_t idx = 0 ; idx < orders.size() ; idx++)
        result.push_back(orders[idx].back());
    return result;
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<int> ordids = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["ordids"];
    vector<int> preptime = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["prep"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    vector<vector<int>> orders;
    int idx = 0;
    for ( int o : ordids)
        orders.push_back({o, preptime[idx++]});

    vector<int> result = jimOrders(orders);
    if (check_result(result, expected)) return 0;

    printf("jimOrders(%s) returned %s but expected %s\n", array2str(orders).c_str(),
        array2str(result).c_str(), array2str(expected).c_str());
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
