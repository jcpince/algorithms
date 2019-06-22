#! /usr/bin/python3


# 785. Is Graph Bipartite?
# Medium
#
# Given an undirected graph, return true if and only if it is bipartite.
#
# Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.
#
# The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.
#
# Example 1:
# Input: [[1,3], [0,2], [1,3], [0,2]]
# Output: true
# Explanation:
# The graph looks like this:
# 0----1
# |    |
# |    |
# 3----2
# We can divide the vertices into two groups: {0, 2} and {1, 3}.
#
# Example 2:
# Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
# Output: false
# Explanation:
# The graph looks like this:
# 0----1
# | \  |
# |  \ |
# 3----2
# We cannot find a way to divide the set of nodes into two independent subsets.
#
#
#
# Note:
#
#     graph will have length in range [1, 100].
#     graph[i] will contain integers in range [0, graph.length - 1].
#     graph[i] will not contain i or duplicate values.
#     The graph is undirected: if any element j is in graph[i], then i will be in graph[j].
#
#

from typing import List
import itertools

class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        if len(graph) < 2:
            # print("len(graph) is %d" % len(graph))
            return True

        g1 = {0}
        g2 = set(graph[0])

        # We build g1 and g2 and every time we add some element to one, we check it is not in the
        # second (if dst_node in g2: return false)
        # We alternate g1 and g2 to factorize the code
        # When we can't grow g1 and g2 (islands), we append one of the group with the next
        # unexplored node (list(set(range(len(graph))).difference(g1.union(g2)))[0]) and
        # we continue
        changed = True
        while changed:
            changed = False
            for src_node in g2:
                #print("explore the node %d from %s" % (src_node, g2))
                for dst_node in graph[src_node]:
                    if dst_node in g2:
                        # print("-- g1", g1)
                        # print("Aye! %d already in g2(%s)" % (dst_node, g2))
                        return False
                    if dst_node not in g1:
                        #print("append %d to g1(%s)" % (dst_node, g1))
                        g1.add(dst_node)
                        changed = True

            if not changed and ((len(g1) + len(g2)) < len(graph)):
                # append unexplored node
                l = list(set(range(len(graph))).difference(g1.union(g2)))
                #print("Isolated nodes found; append %d to %s" % (l[0], g1))
                g1.add(l[0])
                changed = True

            # swap groups
            tmp = g2
            g2 = g1
            g1 = tmp

        # print("g1", g1)
        # print("g2", g2)
        return True


def check_solution():
    s = Solution()

    graph = [[1,3], [0,2], [1,3], [0,2]]
    result = s.isBipartite(graph)
    assert(result == True)

    graph = [[1,2,3], [0,2], [0,1,3], [0,2]]
    result = s.isBipartite(graph)
    assert(result == False)

    graph = [[1,3,4], [0,2], [1,3,4], [0,2], []]
    result = s.isBipartite(graph)
    assert(result == True)

    graph = [[1,3,4,6], [0,2], [1,3,4,5], [0,2], [0,2], [2,6], [0,5]]
    result = s.isBipartite(graph)
    assert(result == False)

    graph = [[3],[2,4],[1],[0,4],[1,3]]
    result = s.isBipartite(graph)
    assert(result == True)

    graph = [[]]
    result = s.isBipartite(graph)
    assert(result == True)

    graph = [[],[2,4,6],[1,4,8,9],[7,8],[1,2,8,9],[6,9],[1,5,7,8,9],[3,6,9],[2,3,4,6,9],[2,4,5,6,7,8]]
    result = s.isBipartite(graph)
    assert(result == False)

    graph = [[47],[48],[52,58,62],[77,84],[9,13,24,73],[15,41,47,49,55,68,83,85,88],[72],
        [10,37,57,79],[12,14,42,58],[4,26,65,74],[7,26,33,37],[41,53,83,90],[8],[4,68,81],[8,86],
        [5,19,51,54,96],[39,81],[47,74,76],[55,60,64,77],[15,23,44,74,88,90,91],[22,39,57,72],
        [59,77],[20,48],[19,59,90,92,98],[4,84,87],[43,63,81,90,91,92],[9,10,64,84,91],[42,54],
        [54,83,87],[36,45,77],[59],[32,40,52,57],[31,65],[10,79],[35,46,62,70,89,91],[34,70],
        [29,78],[7,10,43,75,99],[55,56],[16,20,65,74],[31,42,58,63],[5,11,45,63],[8,27,40,65,72,78],
        [25,37],[19,53],[29,41,66,97],[34],[0,5,17,59,66,91],[1,22,81],[5,55,64,78,98],[68,71],
        [15,52,87,97],[2,31,51,91],[11,44,54,66,70,74],[15,27,28,53],[5,18,38,49,63,83],[38,69,75],
        [7,20,31],[2,8,40,90],[21,23,30,47,67,96],[18,84],[],[2,34],[25,40,41,55],[18,26,49],
        [9,32,39,42],[45,47,53,96,99],[59,70,77],[5,13,50],[56,83,89,94],[34,35,53,67],[50,83,85],
        [6,20,42],[4,83],[9,17,19,39,53],[37,56],[17],[3,18,21,29,67,90],[36,42,49,83],[7,33,90],
        [90,91],[13,16,25,48,99],[],[5,11,28,55,69,71,73,78,90],[3,24,26,60],[5,71],[14],[24,28,51],
        [5,19,93],[34,69],[11,19,23,25,58,77,79,80,83,92],[19,25,26,34,47,52,80],[23,25,90],[88,95],
        [69,96],[93,99],[15,59,66,94],[45,51],[23,49],[37,66,81,95]]
    result = s.isBipartite(graph)
    assert(result == False)

    graph = [[],[10,44,62],[98],[59],[90],[],[31,59],[52,58],[],[53],[1,63],[51,71],[18,64],
        [24,26,45,95],[61,67,96],[],[40],[39,74,79],[12,21,72],[35,85],[86,88],[18,76],[71,80],
        [27,58,85],[13,26,87],[75,94],[13,24,68,77,82],[23],[56,96],[67],[56,73],[6],[41],
        [50,88,91,94],[],[19,72,92],[59],[49],[49,89],[17],[16],[32,84,86],[61,73,77],[94,98],
        [1,74],[13,57,90],[],[93],[],[37,38,54,68],[33],[11],[7,85],[9],[49],[61],[28,30,87,93],
        [45,69,77],[7,23,76],[3,6,36,62],[81],[14,42,55,62],[1,59,61],[10],[12,93],[],[96],
        [14,29,70,73],[26,49,71,76],[57,83],[67],[11,22,68,89],[18,35],[30,42,67],[17,44],[25],
        [21,58,68],[26,42,57,95],[],[17],[22,83],[60],[26,83,84,94],[69,80,82],[41,82],[19,23,52],
        [20,41],[24,56],[20,33],[38,71,99],[4,45],[33],[35],[47,56,64],[25,33,43,82],[13,77],
        [14,28,66],[],[2,43],[89]]
    result = s.isBipartite(graph)
    assert(result == False)

    graph = [[1],[0],[4],[4],[2,3]]
    result = s.isBipartite(graph)
    assert(result == True)

    print("All tests passed successfully!!")

check_solution()


    # def isBipartite(self, graph: List[List[int]]) -> bool:
    #     g1 = graph[0]
    #     g2 = list()
    #     for n in graph[1:]:
    #         found = False
    #         for e in n:
    #             if e in g1:
    #                 found = True
    #                 g1 += n
    #                 for e in n:
    #                     if e in g2:
    #                         return False
    #                 break
    #         if not found:
    #             g2 += n
    #     return len(g2) != 0
