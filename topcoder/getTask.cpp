/*
https://community.topcoder.com/stat?c=problem_statement&pm=1585&rd=6535
Problem Statement for BusinessTasks
Problem Statement


A busy businessman has a number of equally important tasks which he must accomplish. To decide
which of the tasks to perform first, he performs the following operation.

He writes down all his tasks in the form of a circular list, so the first task is adjacent to the
last task. He then thinks of a positive number. This number is the random seed, which he calls n.
Starting with the first task, he moves clockwise (from element 1 in the list to element 2 in the
list and so on), counting from 1 to n. When his count reaches n, he removes that task from the list
and starts counting from the next available task. He repeats this procedure until one task remains.
It is this last task that he chooses to execute.

Given a String[] list representing the tasks and an int n, return the task which the businessman
chooses to execute.

Definition

Class:	BusinessTasks
Method:	getTask
Parameters:	String[], int
Returns:	String
Method signature:	String getTask(String[] list, int n)
(be sure your method is public)


Constraints
-	list will contain between 2 and 50 elements inclusive.
-	Each element in list will contain between 1 and 50 characters inclusive.
-	Each element in list will contain only characters 'a'-'z'.
-	n will be between 1 and 10000000 inclusive.

Examples
0)


{"a","b","c","d"}

2

Returns: "a"

We start counting from a. So a is 1, b is 2. We remove b, so list is now {a,c,d}. We continue
from c. So c is 1, d is 2. We remove d, so list is now {a,c}. We continue from a. So a is 1, c is 2.
We remove c, and now we are left with the last task a.
1)


{"a","b","c","d","e"}

3

Returns: "d"

We start counting from a. So a is 1, b is 2, c is 3. We remove c, now list = {a,b,d,e}. We continue
from d. So d is 1, e is 2, a is 3. We remove a, now list = {b,d,e}. We continue from b. So b is 1,
d is 2, e is 3. We remove e, now list = {b,d}. We continue from b. So b is 1, d is 2 and finally
b is 3. We remove b, and now we are left with just one task d.
2)


{"alpha","beta","gamma","delta","epsilon"}

1

Returns: "epsilon"

3)


{"a","b"}

1000

Returns: "a"

4)


{"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t",
"u","v","w","x","y","z"}

17

Returns: "n"

5)


{"zlqamum","yjsrpybmq","tjllfea","fxjqzznvg","nvhekxr","am","skmazcey","piklp",
"olcqvhg","dnpo","bhcfc","y","h","fj","bjeoaxglt","oafduixsz","kmtbaxu",
"qgcxjbfx","my","mlhy","bt","bo","q"}

9000000

Returns: "fxjqzznvg"

This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized
use or reproduction of this information without the prior written consent of TopCoder, Inc. is
strictly prohibited. (c)2010, TopCoder, Inc. All rights reserved.
This problem was used for:
      Single Round Match 236 Round 1 - Division I, Level One
      Single Round Match 236 Round 1 - Division II, Level Two

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

string getTask(vector<string> list, int n) {
    assert(n > 0);

    if (n == 1) return list.back();

    size_t index = 0;
    while (list.size() > 1) {
        index = (index + n - 1) % list.size();
        list.erase(list.begin() + index);
        // Reposition our index if we removed the last element
        if (index == list.size()) index = 0;
    }
    return list[0];
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<string> tasks = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["tasks"];
    int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["n"];
    string expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    string result = getTask(tasks, n);
    if (result == expected) return 0;

    printf("getTask(%s, %d) returned %s but expected %s\n", array2str(tasks).c_str(), n,
        result.c_str(), expected.c_str());
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
