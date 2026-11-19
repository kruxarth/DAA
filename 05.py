# P5: Minimum spanning tree using Prim's algorithm

import heapq


def prim_mst(graph, start=0):
    n = len(graph)
    visited = [False] * n
    min_heap = [(0, start, -1)]  # weight, vertex, parent
    mst_edges = []
    total_weight = 0

    while min_heap and len(mst_edges) < n - 1:
        weight, vertex, parent = heapq.heappop(min_heap)
        if visited[vertex]:
            continue

        visited[vertex] = True
        if parent != -1:
            mst_edges.append((parent, vertex, weight))
            total_weight += weight

        for neighbor, edge_weight in enumerate(graph[vertex]):
            if edge_weight is not None and not visited[neighbor]:
                heapq.heappush(min_heap, (edge_weight, neighbor, vertex))

    if not all(visited):
        raise ValueError("Graph is disconnected; an MST does not exist.")
    return mst_edges, total_weight


# Use None for no edge; use 0 for a zero-weight edge.
n = int(input("Enter number of vertices: "))
print("Enter the adjacency matrix row by row; use -1 for no edge.")
graph = []
for _ in range(n):
    row = list(map(int, input().split()))
    if len(row) != n:
        raise ValueError("Each row must contain n values.")
    graph.append([None if x == -1 else x for x in row])

start = int(input(f"Enter start vertex (1-{n}): ")) - 1
edges, total = prim_mst(graph, start)
print("Edges in the minimum spanning tree:")
for u, v, weight in edges:
    print(f"{u + 1} - {v + 1}: {weight}")
print("Total MST weight:", total, "\n")
