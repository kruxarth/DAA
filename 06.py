# P6: Minimum spanning tree using Kruskal's algorithm

def find(parent, vertex):
    if parent[vertex] != vertex:
        parent[vertex] = find(parent, parent[vertex])
    return parent[vertex]


def union(parent, rank, u, v):
    root_u, root_v = find(parent, u), find(parent, v)
    if root_u == root_v:
        return False
    if rank[root_u] < rank[root_v]:
        parent[root_u] = root_v
    elif rank[root_u] > rank[root_v]:
        parent[root_v] = root_u
    else:
        parent[root_v] = root_u
        rank[root_u] += 1
    return True


n = int(input("Enter number of vertices: "))
m = int(input("Enter number of edges: "))
edges = []
print("Enter each edge as: source destination weight (vertices numbered 1 to n)")
for _ in range(m):
    u, v, w = map(int, input().split())
    edges.append((w, u - 1, v - 1))

parent = list(range(n))
rank = [0] * n
mst = []
total = 0

for weight, u, v in sorted(edges):
    if union(parent, rank, u, v):
        mst.append((u, v, weight))
        total += weight
        if len(mst) == n - 1:
            break

if len(mst) != n - 1:
    print("Graph is disconnected; a spanning tree does not exist.\n")
else:
    print("Edges in the minimum spanning tree:")
    for u, v, weight in mst:
        print(f"{u + 1} - {v + 1}: {weight}")
    print("Total MST weight:", total, "\n")
