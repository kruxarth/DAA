# P7: Single-source shortest path in a directed multistage graph
# Vertices are numbered 1..n; edges must go from lower to higher stage/index.
INF = float("inf")

n = int(input("Enter number of vertices: "))
m = int(input("Enter number of directed edges: "))
graph = [[] for _ in range(n)]
print("Enter each edge as: source destination weight (vertices numbered 1 to n)")
for _ in range(m):
    u, v, w = map(int, input().split())
    graph[u - 1].append((v - 1, w))

source = int(input(f"Enter source vertex (1-{n}): ")) - 1
destination = int(input(f"Enter destination vertex (1-{n}): ")) - 1

# Reverse vertex order is a valid topological order for a multistage
# graph whose edges go from lower to higher vertex indices.
dist = [INF] * n
next_vertex = [None] * n
dist[destination] = 0

for u in range(n - 1, -1, -1):
    if u == destination:
        continue
    for v, weight in graph[u]:
        if dist[v] != INF and weight + dist[v] < dist[u]:
            dist[u] = weight + dist[v]
            next_vertex[u] = v

if dist[source] == INF:
    print("No path exists from source to destination.")
else:
    path = [source]
    current = source
    while current != destination:
        current = next_vertex[current]
        if current is None:
            break
        path.append(current)
    print("Shortest distance:", dist[source])
    print("Shortest path:", " -> ".join(str(v + 1) for v in path), "\n")
