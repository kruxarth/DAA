# Experiment 6: Minimum Spanning Tree using Kruskal's Algorithm

(For what an MST is, see the [Prim's notes](05-prims-mst.md).)

## Kruskal's idea in plain words
1. **Sort all edges** by weight, smallest first.
2. Go through them one by one: **take the edge if it does NOT make a cycle**, otherwise skip it.
3. Stop when you have **V − 1 edges**.

Greedy: always the cheapest remaining edge overall.

## How do we detect a cycle? Union-Find (Disjoint Set)
- Each vertex starts in its own group: `parent[i] = i`.
- `findParent(parent, x)` returns the **leader** (root) of x's group.
- For edge u–v: if both ends have the same root (`rootU == rootV`), they are already connected, so adding the edge would make a **cycle** and we skip it.
- Otherwise take the edge and **union** the groups: `parent[rootU] = rootV`.
- Edges are stored as `{weight, u, v}`, so a plain `sort(edges.begin(), edges.end())` sorts them by weight.

If asked about speed-ups: **path compression** (point every node straight at its root while finding) and **union by rank** make union-find almost O(1) per operation. The simple version here is enough for the practical.

## Dry run (same graph as Prim's)
Edges sorted: (0-1,2) (1-2,3) (1-4,5) (0-3,6) (2-4,7) (1-3,8) (3-4,9)
```
0-1 (2): different groups -> TAKE   {0,1}
1-2 (3): different groups -> TAKE   {0,1,2}
1-4 (5): different groups -> TAKE   {0,1,2,4}
0-3 (6): different groups -> TAKE   {0,1,2,3,4}   4 edges = V-1, stop
Total = 16   (same as Prim's)
```
If we had continued: 2-4 (7) has both ends in the same group, so it would be a CYCLE and skipped.

## C++ code
File: [`cpp/06_kruskals.cpp`](../cpp/06_kruskals.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Find the leader (root) of the group that x belongs to
int findParent(vector<int>& parent, int x) {
    if (parent[x] == x) return x;

    return findParent(parent, parent[x]);
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // each edge stored as {weight, u, v} so sort() sorts by weight
    vector<vector<int>> edges;
    cout << "Enter each edge as: u v weight" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }

    sort(edges.begin(), edges.end());

    // every vertex starts as its own group
    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int total = 0;
    int taken = 0;
    cout << "Edges in MST:" << endl;

    for (int i = 0; i < m; i++) {
        if (taken == n - 1) break;

        int w = edges[i][0];
        int u = edges[i][1];
        int v = edges[i][2];

        int rootU = findParent(parent, u);
        int rootV = findParent(parent, v);

        if (rootU != rootV) {
            // different groups -> no cycle, take this edge
            parent[rootU] = rootV;      // join the two groups
            cout << u << " - " << v << " : " << w << endl;
            total = total + w;
            taken++;
        }
        // same group -> this edge would make a cycle, skip it
    }

    cout << "Total cost of MST = " << total << endl;
    return 0;
}
```

## Sample run
```
Enter number of vertices and edges: 5 7
Enter each edge as: u v weight
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9
Edges in MST:
0 - 1 : 2
1 - 2 : 3
1 - 4 : 5
0 - 3 : 6
Total cost of MST = 16
```

## Complexity
- Sorting edges: **O(E log E)**
- Union-find operations: almost O(1) each
- **Total: O(E log E)** (same as O(E log V))

## Viva questions
- **Why sort the edges?** Greedy: we want the cheapest edges first.
- **How do you avoid cycles?** With union-find. If both ends have the same root, skip the edge.
- **Kruskal's vs Prim's?** Kruskal's is edge-based and better for sparse graphs. Prim's is vertex-based and better for dense graphs. Both give the same MST cost.
- **Can Kruskal's work on a disconnected graph?** It gives a minimum spanning **forest**.
