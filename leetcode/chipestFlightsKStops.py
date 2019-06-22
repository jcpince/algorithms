#! /usr/bin/python3

# 787. Cheapest Flights Within K Stops
# Medium
#
# There are n cities connected by m flights. Each fight starts from city u and arrives at v with a price w.
#
# Now given all the cities and flights, together with starting city src and the destination dst, your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.
#
# Example 1:
# Input:
# n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
# src = 0, dst = 2, k = 1
# Output: 200
# Explanation:
# The graph looks like this:
#
# 
# The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
#
# Example 2:
# Input:
# n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
# src = 0, dst = 2, k = 0
# Output: 500
# Explanation:
# The graph looks like this:
#
#
# The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
#
# Note:
#
#     The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
#     The size of flights will be in range [0, n * (n - 1) / 2].
#     The format of each flight will be (src, dst, price).
#     The price of each flight will be in the range [1, 10000].
#     k is in the range of [0, n - 1].
#     There will not be any duplicated flights or self cycles.
#


from graph import GraphNode, Graph
from typing import List
import collections

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        nodes = [GraphNode(i) for i in range(0, n)]
        for flight in flights:
            [n0, n1, price] = flight
            nodes[n0].addEdge(n1, price)
        graph = Graph(nodes)
        price, flights = graph.djikstraK(nodes[src], nodes[dst], K+2)
        print("Flight from %d to %d with %d stops for $%d -- %s" % (src, dst, K, price, flights))
        return price

class Solution(object):
    def findCheapestPrice(self, n, flights, src, dst, K):
        graph = collections.defaultdict(dict)
        for u, v, c in flights:
            graph[u][v] = c
        visited = [0] * n
        ans = [float('inf')]
        self.dfs(graph, src, dst, K+1, 0, visited, ans)
        return -1 if ans[0] == float('inf') else ans[0]

    def dfs(self, graph, src, dst, k, cost, visited, ans):
        if dst == src:
            ans[0] = cost
        if k == 0:
            return

        for v, c in graph[src].items():
            if visited[v] == 1:
                continue
            if c + cost > ans[0]:
                continue
            visited[v] = 1
            self.dfs(graph, v, dst, k-1, cost+c, visited, ans)
            visited[v] = 0

def check_solution():
    s = Solution()
    n = 3
    edges = [[0,1,100],[1,2,100],[0,2,500]]
    assert(s.findCheapestPrice(n, edges, 0, 2, 1) == 200)
    assert(s.findCheapestPrice(n, edges, 0, 2, 2) == 200)
    assert(s.findCheapestPrice(n, edges, 0, 2, 0) == 500)
    assert(s.findCheapestPrice(n, edges, 1, 0, 5) == -1)
    assert(s.findCheapestPrice(n, edges, 1, 0, 0) == -1)

    n = 8
    edges = [[0,1,100],[0,5,100],[1,2,200],[1,4,200],[1,3,500],[2,3,200],[4,7,100],[5,4,100],
        [5,7,400],[5,6,200],[6,7,100],[7,3,200]]
    assert(s.findCheapestPrice(n, edges, 0, 2, 1) == 300)
    assert(s.findCheapestPrice(n, edges, 3, 2, 1) == -1)
    assert(s.findCheapestPrice(n, edges, 0, 3, 0) == -1)
    assert(s.findCheapestPrice(n, edges, 0, 3, 1) == 600)
    assert(s.findCheapestPrice(n, edges, 0, 3, 2) == 500)
    assert(s.findCheapestPrice(n, edges, 0, 3, 3) == 500)
    assert(s.findCheapestPrice(n, edges, 0, 7, 2) == 300)
    assert(s.findCheapestPrice(n, edges, 0, 7, 1) == 500)

    n = 4
    edges = [[0,1,1],[0,2,5],[1,2,1],[2,3,1]]
    assert(s.findCheapestPrice(n, edges, 0, 3, 1) == 6)

    n = 3
    edges = [[0,1,100],[1,2,100],[0,2,500]]
    assert(s.findCheapestPrice(n, edges, 0, 2, 0) == 500)

    n = 5
    edges = [[0,1,5],[1,2,5],[0,3,2],[3,1,2],[1,4,1],[4,2,1]]
    assert(s.findCheapestPrice(n, edges, 0, 2, 2) == 7)

    print("All tests passed!")



check_solution()
