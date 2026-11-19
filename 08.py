# P8: All-pairs shortest paths using Floyd-Warshall
# For a multistage graph, this also finds shortest paths between all vertex pairs.
INF = float("inf")

n = int(input("Enter number of vertices: "))
print("Enter the adjacency matrix row by row; use -1 for no edge.")
dist = []
for i in range(n):
    row = list(map(int, input().split()))
    if len(row) != n:
        raise ValueError("Each row must contain n values.")
    dist.append([0 if i == j else (INF if x == -1 else x)
                 for j, x in enumerate(row)])

for k in range(n):
    for i in range(n):
        for j in range(n):
            if dist[i][k] != INF and dist[k][j] != INF:
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

print("All-pairs shortest distance matrix (-1 means unreachable):")
for row in dist:
    print(" ".join("-1" if x == INF else str(int(x)) for x in row))
print("\n")

# Sample input:
# 4
# 0 5 10 -1
# -1 0 3 9
# -1 -1 0 1
# -1 -1 -1 0

# Sample output:
# 0 5 8 9
# -1 0 3 4
# -1 -1 0 1
# -1 -1 -1 0
