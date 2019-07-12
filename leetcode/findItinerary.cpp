/*
https://leetcode.com/problems/reconstruct-itinerary/

332. Reconstruct Itinerary
Medium

Given a list of airline tickets represented by pairs of departure and arrival airports [from, to],
reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus,
the itinerary must begin with JFK.

Note:

    If there are multiple valid itineraries, you should return the itinerary that has the smallest
    lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a
    smaller lexical order than ["JFK", "LGB"].
    All airports are represented by three capital letters (IATA code).
    You may assume all tickets form at least one valid itinerary.

Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]

Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
             But it is larger in lexical order.


*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    map<string, priority_queue<string>*> destinations;
public:
    vector<string> findItinerary2(vector<vector<string>>& tickets) {
        vector<string> route = {"JFK"};
        for (vector<string> ticket : tickets) {
            if (destinations.find(ticket[0]) == destinations.end())
                destinations[ticket[0]] = new priority_queue<string>();
            destinations[ticket[0]]->emplace(ticket[1]);
        }

        map<string, priority_queue<string>*>::iterator it;
        string start = "JFK";
        while ((it = destinations.find(start)) != destinations.end()) {
            priority_queue<string> *possibilities = it->second;
            if (possibilities->size() == 0) break;
            start = possibilities->top();
            possibilities->pop();
            route.push_back(start);
        }
        for (it = destinations.begin(); it != destinations.end() ; it++)
            delete it->second;
        return route;
    }

private:
    void explore(vector<string> &route, unordered_map<string, multiset<string>> &_map,
            const string &start) {

        while (!_map[start].empty()) {
            multiset<string>::iterator it = _map[start].begin();
            string dest = *it;
            _map[start].erase(it);

            explore(route, _map, dest);
        }
        route.push_back(start);
    }

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {

        unordered_map<string, multiset<string>> _map;
        for (vector<string> ticket : tickets) _map[ticket[0]].insert(ticket[1]);

        vector<string> route;
        string start = "JFK";
        explore(route, _map, start);
        reverse(route.begin(), route.end());
        return route;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<string>> tickets = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<string> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<string> result = s.findItinerary(tickets);

    if (check_result(result, expected)) return 0;

    printf("findItinerary(%s) returned %s but expected %s\n", array2str(tickets).c_str(),
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
