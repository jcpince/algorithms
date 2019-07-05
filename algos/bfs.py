from typing import List
import json
import sys

class Graph(object):
    UNREACHABLE_DISTANCE = -1

    def __init__(self, n):
        self.nodes_count = n
        self.adj = [[self.UNREACHABLE_DISTANCE for _ in range(n)] for _ in range(n)]

    def add_edge(self, u, v, dist: int) -> None:
        self.adj[u][v] = dist

    def set_distance(self, starting_node: int, node: int, distance: int, distances: List[int]) -> None:
        assert(node != starting_node)
        if node < starting_node:
            distances[node] = distance
        else:
            distances[node - 1] = distance

    def get_distance(self, starting_node: int, node: int, distances: List[int]) -> int:
        assert(node != starting_node)
        if node < starting_node:
            return distances[node]
        return distances[node - 1]

    def get_distances_from(self, starting_node: int) -> List[int]:
        distances = [self.UNREACHABLE_DISTANCE for _ in range(self.nodes_count - 1)]
        to_visit = []
        remaining = 0
        starting_node -= 1

        for neighbor, dist in enumerate(self.adj[starting_node]):
            if dist != self.UNREACHABLE_DISTANCE and neighbor != starting_node:
                to_visit.append(neighbor)
                self.set_distance(starting_node, neighbor, dist, distances)
                remaining += 1

        while len(to_visit) > 0:
            node = to_visit.pop(0)
            node_distance = self.get_distance(starting_node, node, distances)
            for neighbor, dist in enumerate(self.adj[node]):
                if (neighbor == starting_node or neighbor == node): continue
                neighbor_distance = self.get_distance(starting_node, neighbor, distances)
                if (neighbor_distance != self.UNREACHABLE_DISTANCE or
                    self.adj[node][neighbor] == self.UNREACHABLE_DISTANCE):
                    continue
                # Valid univisted neighbor
                to_visit.append(neighbor)
                self.set_distance(starting_node, neighbor, node_distance + dist, distances)
        return distances

def run_test_case(jin: json, jexpected : json, tc_idx: int) -> None:
    print('running test case %d' % tc_idx)
    edges = jin['edges']
    nodes_count = jin['nodes_count']
    starting_node = jin['starting_node']
    expected = jexpected

    g = Graph(nodes_count)
    for [u, v] in edges:
        g.add_edge(u-1, v-1, 6)
        g.add_edge(v-1, u-1, 6)

    result = g.get_distances_from(starting_node)
    if len(expected) != len(result):
        print("compute_distances(%s, %d, %d) returned %s but expected %s" % (
            edges, nodes_count, starting_node, result, expected))
    else:
        for idx, e in enumerate(expected):
            if e != result[idx]:
                print("compute_distances(%s, %d, %d) returned %s but expected %s" % (
                    edges, nodes_count, starting_node, result, expected))
                break
    del g


def run_tests(json_filename: str, test_case_id: int) -> None:
    jfile = open(json_filename, 'r')
    j = json.load(jfile)['tests']
    tc_idx = 0
    if test_case_id is not None:
        j = [j[test_case_id]]
        tc_idx = test_case_id
    for jtc in j:
        run_test_case(jtc['in'], jtc['expected'], tc_idx)
        tc_idx+=1
    del j

if __name__ == '__main__':
    if len(sys.argv) == 1:
        # run smoke mini test here
        g = Graph(5)
        g.add_edge(2,2,5)
        print(g.adj)
    elif len(sys.argv) != 2 and len(sys.argv) != 3:
        print('Error: usage %s [json file name] [test case id] but args are %s' %
            (sys.argv[0], sys.argv[1:]))
    else:
        json_filename = sys.argv[1]
        test_case_id = None if len(sys.argv) == 2 else int(sys.argv[2])
        run_tests(json_filename, test_case_id)
