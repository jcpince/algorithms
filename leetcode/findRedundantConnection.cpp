/*
https://leetcode.com/problems/redundant-connection/

684. Redundant Connection
Medium

In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N),
with one additional edge added. The added edge has two different vertices chosen from 1 to N, and
was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v]
with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are
multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v]
should be in the same format, with u < v.

Example 1:

Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3

Example 2:

Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3

Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input
array.


Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly the graph is an
undirected graph. For the directed graph follow up please see Redundant Connection II).
We apologize for any inconvenience caused.
*/

#include <bits/stdc++.h>

#define DEBUG 1
//#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Node;

class Node {
public:
    vector<Node*> neighbors;
    size_t nidx_to_visit;
    int id;
    bool visited;

    Node() : nidx_to_visit(0), visited(false) {}
};

string to_string(Node *&node) { return to_string(node->id); }

class Solution {
    void findCycle(Node *root, vector<Node*> &cycle) {

        if (!root->neighbors.size()) return;

        root->visited = true;
        cycle.emplace_back(root);

        Node *current = root->neighbors.front(), *prev = root;
        root->nidx_to_visit++;

        while (current) {
            debug_print("Visits %d\n", current->id);

            cycle.emplace_back(current);
            current->visited = true;

            // Choose next by going deeper first
            while (current->nidx_to_visit < current->neighbors.size() and
                current->neighbors[current->nidx_to_visit] == prev)
                    current->nidx_to_visit++;

            while (current->nidx_to_visit >= current->neighbors.size()) {
                // current is all-visited, get the previous from the cycle
                dev_assert(cycle.size() > 1);
                cycle.pop_back();                   // remove the all-visited node
                current = cycle.back();             // get the last visited as current
                if (current != root) {
                    prev = cycle[cycle.size()-2];   // get the prev
                    while (current->nidx_to_visit < current->neighbors.size() and
                        current->neighbors[current->nidx_to_visit] == prev)
                            current->nidx_to_visit++;
                }
            }

            // Change the current and mark it as visited
            debug_print("current(%d)->to_visit is %d\n", current->id,
                current->neighbors[current->nidx_to_visit]->id);
            prev = current;
            current->nidx_to_visit++;
            current = current->neighbors[current->nidx_to_visit-1];
            if (current->visited == true)
            {
                cycle.emplace_back(current);
                debug_print("Found a cycle %s\n", array2str(cycle).c_str());
                return;
            }
        }
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int max_node_id = 0;
        for (vector<int> edge : edges)
            max_node_id = max(max(max_node_id, edge[0]),  edge[1]);

        if (edges.size() == 0) return {};

        vector<Node> nodes(max_node_id);

        for (int idx = 0; idx < max_node_id ; idx++) nodes[idx].id = idx+1;

        for (vector<int> edge : edges) {
            int id = edge[0], neighbor_id = edge[1];
            Node *n0 = &nodes[id-1], *n1 = &nodes[neighbor_id-1];
            n0->neighbors.push_back(n1);
            n1->neighbors.push_back(n0);
        }
        vector<Node*> cycle;
        findCycle(&nodes[0], cycle);
        debug_print("Cycle returned is %s\n", array2str(cycle).c_str());
        int cycle_first_idx = 0;
        while (cycle[cycle_first_idx]->id != cycle.back()->id) cycle_first_idx++;

        dev_assert((cycle.size() - cycle_first_idx) > 2);
        int orig = -1, dest = -1;
        bool found = false;

        for (int eidx = edges.size()-1 ; eidx >= 0 and !found; eidx--) {
            vector<int> edge = edges[eidx];
            orig = edge[0];
            dest = edge[1];
            for (size_t idx = cycle_first_idx ; idx < cycle.size() - 1 ; idx++) {
                if      ( ( (orig == cycle[idx]->id) and (dest == cycle[idx+1]->id) ) or
                          ( (dest == cycle[idx]->id) and (orig == cycle[idx+1]->id) ) )  {
                    found = true;
                    break;
                }
            }
        }
        dev_assert(found);
        vector<int> result(2);
        result[0] = min(orig, dest);
        result[1] = max(orig, dest);
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> edges = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution sol;
    vector<int> result = sol.findRedundantConnection(edges);
    if (check_result(result, expected)) return 0;

    debug_print("findRedundantConnection(%s) returned %s but expected %s\n", array2str(edges).c_str(),
        array2str(result).c_str(), array2str(expected).c_str());
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
