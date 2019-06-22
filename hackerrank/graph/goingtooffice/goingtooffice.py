import sys

MAXINT = 2**32

def rsd(graph, start, destination, visited, closed_road):
    result = MAXINT
    for (neighbor, distance) in graph[start]:
        if (neighbor in closed_road) and (start in closed_road):
            print("start %d, visited %s, %d to destination is closed" %
                (start, visited, neighbor))
            continue
        if neighbor in visited:
            print("start %d, visited %s, %d already visited" %
                (start, visited, neighbor))
            continue
        if neighbor == destination:
            print("start %d, visited %s, found the destination %d, returns %d" %
                (start, visited, neighbor, distance))
            return distance
        print("start %d, visited %s, explore %d" % (start, visited, neighbor))
        v = visited.copy()
        v.append(neighbor)
        result = min(result, distance + rsd(graph, neighbor, destination, v, closed_road))
    print("returns %d" % result)
    return result

def call_rsd(graph, start, destination, closed_road):
    result = MAXINT
    for (neighbor, distance) in graph[start]:
        if (neighbor in closed_road) and (destination in closed_road):
            continue
        if neighbor == destination:
            result = min(result, distance)
        neighbor_distance = rsd(graph, neighbor, destination, [neighbor], closed_road)
        result = min(result, distance + neighbor_distance)
    if result >= MAXINT:
        return "Infinity"
    return result

def recursive_sd(graph, start, destination, visited0, current_distance,
        min_distance, closed_road):
    #print("recursive_sd(%s)" % str(
    #    ("graph", start, visited0, current_distance, min_distance)))
    for (neighbor, distance) in graph[start]:
        print("Visited %s, start %d, neighbor %d" % (visited0, start, neighbor))
        visited = visited0.copy()
        if (current_distance + distance) >= min_distance:
            continue
        if neighbor == destination:
            #print("Found destination(%d) returns %d" % (neighbor, distance))
            return current_distance + distance
        if neighbor in visited:
            continue
        if (neighbor in closed_road) and (start in closed_road):
            continue
        # else...
        visited.add(neighbor)
        #print("Visiting neighbor %d" % neighbor)
        neighbor_result = recursive_sd(graph, neighbor, destination,
            visited, current_distance + distance, min_distance, closed_road)
        #print("neighbor_result %d" % neighbor_result)
        min_distance = min(min_distance, neighbor_result)
    #print("returns2 %d" % min_distance)
    return min_distance

def shortest_distance(graph, start, destination, closed_road):
    min_distance = MAXINT
    visited0 = set()
    visited0.add(start)
    # makes sure that the start's neighbors won't be explored in recursive_sd
    for (neighbor, distance) in graph[start]:
        if (neighbor not in closed_road) or (start not in closed_road):
            visited0.add(neighbor)

    for (neighbor, distance) in graph[start]:
        if (neighbor in closed_road) and (start in closed_road):
            continue
        visited = visited0.copy()
        neighbor_result = recursive_sd(graph,
            neighbor, destination, visited, distance, min_distance, closed_road)
        min_distance = min(min_distance, neighbor_result)
    if min_distance >= MAXINT:
        return "Infinity"
    return min_distance

def filter_roads(graph, start, destination):
    # remove all the cul-de-sac not start or destination
    citys = list(graph.keys())
    for city in citys:
        if (city == start) or (city == destination):
            continue
        tos = graph[city]
        if len(tos) == 1:
            del graph[city]

def build_graph(roads):
    graph = dict()
    for road in roads:
        u, v, w = road
        if u not in graph.keys():
            graph[u] = list()

        graph[u].append((v, w))

        if v not in graph.keys():
            graph[v] = list()

        graph[v].append((u, w))

    return graph

stdin = sys.stdin

n, m = (int(i) for i in stdin.readline().strip('\n').split(' '))

roads = list()
for idx in range (0, m):
    (u, v, w) = (int(i) for i in stdin.readline().strip('\n').split(' '))
    roads.append((u, v, w))

start, destination = (int(i) for i in stdin.readline().strip('\n').split(' '))

nb_days = int(stdin.readline().strip('\n'))
closed_roads = list()
for idx in range (0, m):
    (u, v) = (int(i) for i in stdin.readline().strip('\n').split(' '))
    closed_roads.append((u, v))

graph = build_graph(roads)
filter_roads(graph, start, destination)

print(graph)
for closed_road in closed_roads:
    print("\n\nStart %d, Destination %d, close_road %s" % (start, destination,
        str(closed_road)))
    # print("%s: %s" % (str(closed_road),
    #     str(shortest_distance(graph, start, destination, closed_road))))
    print("%s: %s" % (str(closed_road),
        str(call_rsd(graph, start, destination, closed_road))))
    break
