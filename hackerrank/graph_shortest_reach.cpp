/*
https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach/problem?h_r=internal-search

BFS: Shortest Reach in a Graph

Consider an undirected graph consisting of
nodes where each node is labeled from to and the edge between any two nodes is always of length .
We define node to be the starting position for a BFS. Given a graph, determine the distances from
the start node to each of its descendants and return the list in node number order, ascending.
If a node is disconnected, it's distance should be

.

For example, there are
nodes in the graph with a starting node . The list of , and each has a weight of

.

image

Starting from node
and creating a list of distances, for nodes through we have

.

Function Description

Define a Graph class with the required methods to return a list of distances.

Input Format

The first line contains an integer,

, the number of queries.

Each of the following

sets of lines is as follows:

    The first line contains two space-separated integers,

and
, the number of nodes and the number of edges.
Each of the next
lines contains two space-separated integers, and , describing an edge connecting node to node
.
The last line contains a single integer,

    , the index of the starting node.

Constraints

Output Format

For each of the
queries, print a single line of space-separated integers denoting the shortest distances to each
of the other nodes from starting position . These distances should be listed sequentially by node
number (i.e., ), but should not include node . If some node is unreachable from , print

as the distance to that node.

Sample Input

2
4 2
1 2
1 3
1
3 1
2 3
2

Sample Output

6 6 -1
-1 6

Explanation

We perform the following two queries:

    The given graph can be represented as:
    image
    where our start node,

, is node . The shortest distances from to the other nodes are one edge to node , one edge to node ,
and there is no connection to node

    .
    The given graph can be represented as:

image
where our start node,
, is node . There is only one edge here, so node is unreachable from node and node has one edge
connecting it to node . We then print node 's distance to nodes and

(respectively) as a single line of space-separated integers: -1 6.

Note: Recall that the actual length of each edge is
, and we print as the distance to any node that's unreachable from .
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define UNREACHABLE_DISTANCE -1
#define NODES_DISTANCE       6

class Graph {
    int nodes_count;
    vector<int> distances;
    vector<vector<int>> _graph;
    public:
        Graph(int n): nodes_count(n) {_graph = vector<vector<int>>(n+1); }

        void add_edge(int u, int v) {
            _graph[u].push_back(v);
            _graph[v].push_back(u);
        }

        int inline get_distance_index(int start, int node) {
            int distance_index = node-1;
            dev_assert(start != node);
            if (node > start) distance_index--;
            return distance_index;
        }

        vector<int> shortest_reach(int start) {
            distances = vector<int>(nodes_count-1, UNREACHABLE_DISTANCE);

            vector<int> to_visit;
            to_visit.reserve(nodes_count);

            int index = 0, remaining = _graph[start].size();
            for (int v : _graph[start])
                if (v == start) continue; // self cycle?
                else {
                    int distance_index = get_distance_index(start, v);
                    distances[distance_index] = NODES_DISTANCE;
                    to_visit.push_back(v);
                }

            while (remaining-- > 0) {
                int node = to_visit[index++];
                dev_assert(node != start);

                int node_distance = distances[get_distance_index(start, node)];
                debug_print("Visiting %d\n", node);
                for (int v : _graph[node]) {
                    if (v == start) continue;
                    int distance_index = get_distance_index(start, v);
                    if (distances[distance_index] == UNREACHABLE_DISTANCE) {
                        to_visit.push_back(v);
                        distances[distance_index] = node_distance + NODES_DISTANCE;
                        remaining += 1;
                    }
                }
            }
            return distances;
        }
};

void run_perf_tests(TestCase *tc) {

    vector<vector<int>> edges = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["edges"];
    int nodes_count = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nodes_count"];
    int starting_node = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["starting_node"];
    Graph g(nodes_count);
    for (vector<int> edge : edges)
        g.add_edge(edge[0], edge[1]);
    for (int idx = 0 ; idx < PERFS_TESTS_COUNT ; idx++)
        g.shortest_reach(starting_node);
}

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);

    vector<vector<int>> edges = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["edges"];
    int nodes_count = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nodes_count"];
    int starting_node = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["starting_node"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Graph g(nodes_count);
    for (vector<int> edge : edges)
        g.add_edge(edge[0], edge[1]);
    vector<int> result = g.shortest_reach(starting_node);

    if (check_result(result, expected)) {
        run_perf_tests(tc);
        return 0;
    }

    printf("shortest_reach(%s, %d, %d) returned %s but expected %s\n", array2str(edges).c_str(),
        nodes_count, starting_node, array2str(result).c_str(), array2str(expected).c_str());
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
