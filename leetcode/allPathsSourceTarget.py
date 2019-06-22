#! /usr/bin/python3

# 797. All Paths From Source to Target
# Medium
#
# Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.
#
# The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.
#
# Example:
# Input: [[1,2], [3], [3], []]
# Output: [[0,1,3],[0,2,3]]
# Explanation: The graph looks like this:
# 0--->1
# |    |
# v    v
# 2--->3
# There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
#
# Note:
#
#     The number of nodes in the graph will be in the range [2, 15].
#     You can print different paths in any order, but you should keep the order of nodes inside one path.

from typing import List

class Solution:
    def allPathsSourceTarget(self, graph: List[List[int]]) -> List[List[int]]:
        # Acyclic so no need to check for visited node
        # A DFS stopping on destination should be ok
        def dfs(graph, current, destination, results, local_result = None):
            #print("dfs(%d) -- %s -- local_result %s" % (current, graph[current], local_result))
            if local_result is None:
                local_result = [current]
            if current == destination:
                results.append(local_result)
                return
            if len(graph[current]) == 0:
                return
            for node in graph[current][:-1]:
                #print("Calling dfs(%d)" % node)
                tmp = local_result.copy()
                tmp.append(node)
                dfs(graph, node, destination, results, tmp)
            node = graph[current][-1]
            #print("Calling last node dfs(%d)" % node)
            local_result.append(node)
            dfs(graph, node, destination, results, local_result)

        results = []
        dfs(graph, 0, len(graph)-1, results)
        print("Results: %s" % results)
        return results

def check_solution():
    s = Solution()

    assert(len(s.allPathsSourceTarget([[1,2], [3], [3], []])) == 2)

    print("All tests passed successfully!!")

check_solution()
