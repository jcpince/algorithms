# You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.
#
# paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.
#
# Also, there is no garden that has more than 3 paths coming into or leaving it.
#
# Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.
#
# Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.  It is guaranteed an answer exists.
#
#
#
# Example 1:
#
# Input: N = 3, paths = [[1,2],[2,3],[3,1]]
# Output: [1,2,3]
#
# Example 2:
#
# Input: N = 4, paths = [[1,2],[3,4]]
# Output: [1,2,1,2]
#
# Example 3:
#
# Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
# Output: [1,2,3,4]
#
#
#
# Note:
#
#     1 <= N <= 10000
#     0 <= paths.size <= 20000
#     No garden has 4 or more paths coming into or leaving it.
#     It is guaranteed an answer exists.

from typing import List

class Node():
    def __init__(self, index):
        self.index = index
        self.tos = []
        self.froms = []
        self.flower = -1

    def add_to(self, to):
        self.tos.append(to)

    def add_from(self, fr):
        self.froms.append(fr)

class Solution:
    def _gardenNoAdj(self, nodes : List[Node], index : int):
        if index >= len(nodes): return

        node = nodes[index]
        if self.flowers[index] != -1:
            self._gardenNoAdj(nodes, index+1)
            return

        flowers_available = [1,2,3,4]
        for n in node.tos:
            if n.flower != -1:
                #print("Node %d flower is %d" % (n.index + 1, n.flower))
                flowers_available[n.flower-1] = -1

        for n in node.froms:
            if n.flower != -1:
                #print("Node %d flower is %d" % (n.index + 1, n.flower))
                flowers_available[n.flower-1] = -1

        for flower in flowers_available:
            if flower != -1:
                self.flowers[index] = flower
                node.flower = flower
                break

        assert(self.flowers[index] != -1)
        self._gardenNoAdj(nodes, index+1)


    def gardenNoAdj(self, N: int, paths: List[List[int]]) -> List[int]:
        g = []
        self.flowers = []
        for i in range(N):
            g.append(Node(i+1))
            self.flowers.append(-1)

        for path in paths:
            g[path[0] - 1].add_to(g[path[1] - 1])
            g[path[1] - 1].add_from(g[path[0] - 1])

        self._gardenNoAdj(g, 0)
        return self.flowers

    def gardenNoAdjFast(self, N: int, paths: List[List[int]]) -> List[int]:
        res = [0] * N
        m = [[] for _ in range(N + 1)]
        for x, y in paths:
            m[x].append(y)
            m[y].append(x)
        for i in range(1, N+1):
            used = set()
            for j in m[i]:
                used.add(res[j-1])
            for j in range(1, 5):
                if j not in used:
                    res[i-1] = j
                    break
        return res

s = Solution()
#print(s.gardenNoAdj(3, [[1,2],[2,3],[3,1]]))
#print(s.gardenNoAdj(4, [[1,2],[3,4]]))
print(s.gardenNoAdjFast(4, [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]))
for _ in range(500000):
    s.gardenNoAdjFast(4, [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]])
