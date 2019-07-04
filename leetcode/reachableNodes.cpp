/*

https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/

882. Reachable Nodes In Subdivided Graph
Hard

Starting with an undirected graph (the "original graph") with nodes from 0 to N-1, subdivisions are made to some of the edges.

The graph is given as follows: edges[k] is a list of integer pairs (i, j, n) such that (i, j) is an edge of the original graph,

and n is the total number of new nodes on that edge.

Then, the edge (i, j) is deleted from the original graph, n new nodes (x_1, x_2, ..., x_n) are added to the original graph,

and n+1 new edges (i, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n-1}, x_n), (x_n, j) are added to the original graph.

Now, you start at node 0 from the original graph, and in each move, you travel along one edge.

Return how many nodes you can reach in at most M moves.



Example 1:

Input: edges = [[0,1,10],[0,2,1],[1,2,2]], M = 6, N = 3
Output: 13
Explanation:
The nodes that are reachable in the final graph after M = 6 moves are indicated below.

Example 2:

Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], M = 10, N = 4
Output: 23



Note:

    0 <= edges.length <= 10000
    0 <= edges[i][0] < edges[i][1] < N
    There does not exist any i != j for which edges[i][0] == edges[j][0] and edges[i][1] == edges[j][1].
    The original graph has no parallel edges.
    0 <= edges[i][2] <= 10000
    0 <= M <= 10^9
    1 <= N <= 3000
    A reachable node is a node that can be travelled to using at most M moves starting from node 0.

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Node;

/* -------------- INCOMPLETE -------------- */
class Node {
public:
    vector<pair<Node*, int>> neighbors;
    vector<int> edge_visited;
    int id;
    bool visited;

    Node() : visited(false) {}
};

class Solution {
    int browseGraph(const Node *root, int remaining, int maxNodes = 1) {

        if (!remaining) return maxNodes;

        int maxlocals = 0;
        for ( size_t idx = 0 ; idx < root->neighbors.size() ; idx++ ) {
            pair<Node*, int> p = root->neighbors[idx];
            //bool edge_visited =
            Node *n = p.first;
            int weight = p.second;
            printf("Visit node %d to node %d\n", root->id, n->id);
            if (weight <= remaining) {
                int visit_node_count = n->visited ? 0 : 1;
                if (n->visited) visit_node_count = 0;
                n->visited = true;

                maxlocals += browseGraph(n, remaining - weight, visit_node_count);
                printf("Node %d.%d has a max local of %d\n",
                    root->id, n->id, maxlocals);
            } else {
                printf("Node %d.%d cannot be used, increase local to %d\n",
                    root->id, n->id, remaining);
                maxlocals += remaining;
            }
        }
        return maxNodes + maxlocals;
    }
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        if (edges.size() == 0) return 1;

        Node nodes[N];

        for (int idx = 0; idx < N ; idx++) nodes[idx].id = idx;

        for (vector<int> edge : edges) {
            int id = edge[0], neighbor_id = edge[1], w = edge[2] + 1;
            Node *n0 = &nodes[id], *n1 = &nodes[neighbor_id];
            n0->neighbors.push_back(make_pair(n1, w));
            n0->edge_visited.push_back(false);
            n1->neighbors.push_back(make_pair(n0, w));
            n1->edge_visited.push_back(false);
        }
        return browseGraph(&nodes[0], M);
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> edges = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["edges"];
    int m = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["m"];
    int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["n"];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution sol;
    int result = sol.reachableNodes(edges, m, n);
    if (result == expected) return 0;

    printf("reachableNodes(%s, %d, %d) returned %d but expected %d\n", array2str(edges).c_str(),
        m, n, result, expected);
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
