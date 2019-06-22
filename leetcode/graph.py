#! /usr/bin/python3
from heapq import heappush, heappop
from typing import List

class GraphEdge(object):
    def __init__(self, fr: int, to: int, weight: int):
        self.fr = fr
        self.to = to
        self.weight = weight

    def __lt__(self, other):
        return self.weight < other.weight

    def __str__(self):
        return "[%d, %d]" % (self.to, self.weight)

class GraphNode(object):
    def __init__(self, id: int):
        self.id = id
        self.tos = []
        # total_weight is used for visited flag
        self.total_weight = -1

    def addEdge(self, to: int, weight: int):
        heappush(self.tos, GraphEdge(self.id, to, weight))

    def __str__(self):
        string = "(%d ,[" % self.id
        for edge in self.tos:
            string += str(edge)
        return string + "])"

class GraphPath(object):
    def __init__(self, weight: int, nodes: List[int]):
        self.weight = weight
        self.nodes = nodes

    def __lt__(self, other):
        return self.weight < other.weight

class Graph(object):
    def __init__(self, nodes: List[GraphNode] = []):
        self.nodes = nodes

    def addNode(self, node: GraphNode) -> None:
        self.nodes.append(node)

    def __str__(self):
        string = "(%d nodes: [" % len(self.nodes)
        for node in self.nodes:
            string += str(node)
        return string + "])"

    def topologicalOrder(self) -> List[int]:
        N = len(self.nodes)
        result = []
        in_degree = [0] * N
        # initialize the array of inedges per node
        for node in self.nodes:
            for edge in node.tos:
                in_degree[edge.to] += 1

        # Push the nodes with no incoming edge to our resulting array
        queue = []
        for node_idx, degree in enumerate(in_degree):
            if degree == 0:
                queue.append(node_idx)
                in_degree[node_idx] = -1

        while len(queue) != 0:
            node = self.nodes[queue.pop(0)]
            result.append(node.id)
            for edge in node.tos:
                to = edge.to
                if in_degree[to] == -1: continue
                in_degree[to] -= 1
                if in_degree[to] == 0:
                    queue.append(to)
                    in_degree[to] = -1
        return result

    def djikstra(self, start: GraphNode, end: GraphNode) -> List[int]:
        if start.id == end.id:
            return 0, [start.id]

        if len(start.tos) == 0:
            return -1, None

        for node in self.nodes:
            node.total_weight = -1

        paths = []
        for edge in start.tos:
            heappush(paths, GraphPath(edge.weight, [start.id, edge.to]))
            self.nodes[edge.to].total_weight = edge.weight

        while len(paths) > 0:
            path = heappop(paths)
            path_end = self.nodes[path.nodes[-1]]
            if path_end is end:
                return path.weight, path.nodes
            create_route = len(path_end.tos)
            for edge in path_end.tos:
                next = self.nodes[edge.to]
                create_route -= 1
                if ((next.total_weight == -1) or
                        (next.total_weight > (path_end.total_weight + edge.weight))):
                    next.total_weight = path_end.total_weight + edge.weight
                else:
                    continue
                if create_route > 0:
                    nodes = path.nodes.copy()
                    nodes.append(next.id)
                    heappush(paths, GraphPath(next.total_weight, nodes))
                else:
                    path.nodes.append(next.id)
                    path.weight = next.total_weight
                    heappush(paths, path)
        return -1, None

    def djikstraK(self, start: GraphNode, end: GraphNode, max_path_len: int) -> List[int]:
        if start.id == end.id:
            return 0, [start.id]

        if len(start.tos) == 0:
            return -1, None

        paths = []
        for edge in start.tos:
            heappush(paths, GraphPath(edge.weight, [start.id, edge.to]))
            self.nodes[edge.to].total_weight = edge.weight

        while len(paths) > 0:
            path = heappop(paths)
            path_end = self.nodes[path.nodes[-1]]
            if path_end is end:
                return path.weight, path.nodes
            if len(path.nodes) == max_path_len:
                continue
            create_route = len(path_end.tos)
            for edge in path_end.tos:
                next = self.nodes[edge.to]
                create_route -= 1
                # print("(len(path.nodes)(%d) >= (max_path_len(%d) - 1)) and next(%d) is not end(%d)" %
                #     (len(path.nodes), max_path_len, next.id, end.id))
                if create_route > 0:
                    nodes = path.nodes.copy()
                    nodes.append(next.id)
                    new_path = GraphPath(path.weight + edge.weight, nodes)
                    heappush(paths, new_path)
                else:
                    path.nodes.append(next.id)
                    path.weight += edge.weight
                    heappush(paths, path)
        return -1, None

if __name__ == "__main__":
    nodes = [GraphNode(i) for i in range(0, 6)]
    nodes[0].addEdge(1, 1)
    nodes[0].addEdge(2, 1)
    nodes[1].addEdge(2, 1)
    nodes[1].addEdge(3, 2)
    nodes[2].addEdge(3, 1)
    nodes[2].addEdge(4, 1)
    nodes[4].addEdge(5, 1)
    graph = Graph(nodes)
    print("Graph: %s" % graph)
    print("Topological order: %s" % graph.topologicalOrder())
    w, route = graph.djikstra(nodes[3], nodes[5])
    print("Shortest path from 3 to 5 is (%d km) %s" % (w, route))
    assert(w == -1 and route is None)
    w, route = graph.djikstra(nodes[0], nodes[3])
    print("Shortest path from 0 to 3 is (%d km) %s" % (w, route))
    assert(w == 2 and len(route) == 3)
    w, route = graph.djikstra(nodes[0], nodes[5])
    print("Shortest path from 0 to 5 is (%d km) %s" % (w, route))
    assert(w == 3 and len(route) == 4)
    w, route = graph.djikstraK(nodes[0], nodes[5], 3)
    print("Shortest path from 0 to 5 is (%d km) %s" % (w, route))
    assert(w == -1 and route is None)
    w, route = graph.dfs(nodes[0], nodes[5], 3)
    print("Shortest path from 0 to 5 is (%d km) %s" % (w, route))
    assert(w == -1 and route is None)
