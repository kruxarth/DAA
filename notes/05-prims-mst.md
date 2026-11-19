# Experiment 5: Minimum Spanning Tree using Prim's Algorithm

## Key terms
- **Spanning tree**: a subgraph that connects **all V vertices** with exactly **V−1 edges** and **no cycle**.
- **Minimum spanning tree (MST)**: the spanning tree with the **smallest total edge weight**.
- Real use: connecting cities with the least cable or road.

## Prim's idea in plain words
Grow **one tree** from a start vertex. At every step, add the **cheapest edge that connects the tree to a new vertex**. Repeat until all vertices are in.

It's greedy: always the cheapest edge going **out of the tree**.

## Arrays used in the code
- `key[v]`: cheapest edge weight currently known that connects `v` to the tree (starts at ∞, start vertex 0)
- `parent[v]`: the tree vertex at the other end of that edge
- `inMST[v]`: whether `v` is already in the tree

Loop n times: pick the vertex with the smallest `key` not yet in the tree, add it, update its neighbours' keys.

## Dry run
```
        2       3
   (0)-----(1)-----(2)
    |      / \      |
   6|    8/   \5    |7
    |    /     \    |
   (3)---------(4)--+
          9
```
Matrix (0 = no edge):
```
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0
```
```
Start at 0.             Tree {0}
Cheapest out: 0-1 (2)   Tree {0,1}
Cheapest out: 1-2 (3)   Tree {0,1,2}
Cheapest out: 1-4 (5)   Tree {0,1,2,4}
Cheapest out: 0-3 (6)   Tree {0,1,2,3,4}  done
Total = 2+3+5+6 = 16
```

## C++ code
File: [`cpp/05_prims.cpp`](../cpp/05_prims.cpp)

```cpp
#include <iostream>
using namespace std;

const int INF = 1e9;

int main() {
    int n, g[20][20];
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter adjacency matrix (0 = no edge):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    int key[20];      // cheapest edge that connects vertex to the tree
    int parent[20];   // which tree vertex that edge comes from
    bool inMST[20];   // already in the tree?

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        inMST[i] = false;
        parent[i] = -1;
    }
    key[0] = 0;       // start from vertex 0

    for (int count = 0; count < n; count++) {
        // 1. pick the vertex NOT in tree with smallest key
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;

        inMST[u] = true;

        // 2. update keys of its neighbours
        for (int v = 0; v < n; v++)
            if (g[u][v] != 0 && !inMST[v] && g[u][v] < key[v]) {
                key[v] = g[u][v];
                parent[v] = u;
            }
    }

    int total = 0;
    cout << "Edges in MST:" << endl;
    for (int v = 1; v < n; v++) {
        cout << parent[v] << " - " << v << " : " << g[parent[v]][v] << endl;
        total += g[parent[v]][v];
    }
    cout << "Total cost of MST = " << total << endl;
    return 0;
}
```

## Sample run
```
Enter number of vertices: 5
Enter adjacency matrix (0 = no edge):
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0
Edges in MST:
0 - 1 : 2
1 - 2 : 3
0 - 3 : 6
1 - 4 : 5
Total cost of MST = 16
```

## Complexity
| Version | Time |
|---|---|
| Adjacency matrix (this code) | **O(V²)** |
| Min-heap + adjacency list | O(E log V) |

Space: O(V) for key/parent/inMST.

## Viva questions
- **Number of edges in an MST?** V − 1.
- **Prim's vs Kruskal's?** Prim's grows one tree vertex by vertex and is good for **dense** graphs. Kruskal's picks the globally cheapest edges and joins forests, which is good for **sparse** graphs.
- **Is the MST unique?** It is unique if all edge weights are distinct. Otherwise several MSTs can exist, but they all have the same total cost.
- **Does Prim's work on disconnected graphs?** No, an MST needs a connected graph.
- **Why greedy works:** the cut property. The cheapest edge crossing any cut is always in some MST.
