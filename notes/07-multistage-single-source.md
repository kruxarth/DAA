# Experiment 7: Single-Source Shortest Path in a Multistage Graph

## What is a multistage graph?
A directed graph where vertices are divided into **stages** (k ≥ 2). Edges only go from **stage i to stage i+1**. There's one **source** (stage 1) and one **sink** (last stage).

```
Stage:   1        2          3          4        5
              -> 2 ->     -> 6 ->     -> 9 ->
         1   -> 3 ->     -> 7 ->     -> 10 ->    12
              -> 4 ->     -> 8 ->     -> 11 ->
              -> 5 ->
```
**Goal:** the minimum-cost path from source (1) to sink (12).

## Technique: Dynamic Programming
Trying all paths is exponential. Instead, notice:

> The cheapest way from vertex i to the sink = min over every edge i→j of ( cost(i,j) + cheapest way from j to the sink )

```
cost(i) = min { c(i,j) + cost(j) }     for every edge i -> j
cost(sink) = 0
```
Compute this **backwards** from the sink to the source (n−1 down to 1), so `cost(j)` is always ready when needed. Store `nextNode[i] = j`, the best next vertex, to rebuild the path.

This is called the **forward approach** (the formula looks forward to the next stage), even though we fill the table from the end.

## Dry run (standard textbook graph, 12 vertices)
Edges: 1-2:9 1-3:7 1-4:3 1-5:2 2-6:4 2-7:2 2-8:1 3-6:2 3-7:7 4-8:11 5-7:11 5-8:8 6-9:6 6-10:5 7-9:4 7-10:3 8-10:5 8-11:6 9-12:4 10-12:2 11-12:5
```
cost(12) = 0
cost(11) = 5            next=12
cost(10) = 2            next=12
cost(9)  = 4            next=12
cost(8)  = min(5+2, 6+5)      = 7   next=10
cost(7)  = min(4+4, 3+2)      = 5   next=10
cost(6)  = min(6+4, 5+2)      = 7   next=10
cost(5)  = min(11+5, 8+7)     = 15  next=8
cost(4)  = 11+7               = 18  next=8
cost(3)  = min(2+7, 7+5)      = 9   next=6
cost(2)  = min(4+7, 2+5, 1+7) = 7   next=7
cost(1)  = min(9+7, 7+9, 3+18, 2+15) = 16   next=2
Path: 1 -> next[1]=2 -> next[2]=7 -> next[7]=10 -> next[10]=12
```
(1→3→6→10→12 also costs 16, so a tie is fine to mention.)

## C++ code
File: [`cpp/07_multistage_sssp.cpp`](../cpp/07_multistage_sssp.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // edge[i][j] = cost of edge i -> j  (vertices are 1..n)
    vector<vector<int>> edge(n + 1, vector<int>(n + 1, INF));

    cout << "Enter each edge as: u v cost (vertices 1..n, source 1, sink n)" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u][v] = w;
    }

    vector<int> cost(n + 1, INF);     // cost[i] = cheapest cost from i to sink n
    vector<int> nextNode(n + 1, -1);  // nextNode[i] = next vertex on that path

    cost[n] = 0;

    // go backwards from the sink to the source
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++) {
            if (edge[i][j] == INF || cost[j] == INF) continue;

            int newCost = edge[i][j] + cost[j];
            if (newCost < cost[i]) {
                cost[i] = newCost;
                nextNode[i] = j;
            }
        }
    }

    if (cost[1] == INF) {
        cout << "No path from 1 to " << n << endl;
        return 0;
    }

    // follow nextNode from the source to build the path
    vector<int> path;
    int node = 1;
    path.push_back(node);
    while (node != n) {
        node = nextNode[node];
        path.push_back(node);
    }

    cout << "Minimum cost = " << cost[1] << endl;
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
    return 0;
}
```

## Sample run
```
Enter number of vertices and edges: 12 21
Enter each edge as: u v cost (vertices 1..n, source 1, sink n)
1 2 9
1 3 7
1 4 3
1 5 2
2 6 4
2 7 2
2 8 1
3 6 2
3 7 7
4 8 11
5 7 11
5 8 8
6 9 6
6 10 5
7 9 4
7 10 3
8 10 5
8 11 6
9 12 4
10 12 2
11 12 5
Minimum cost = 16
Path: 1 -> 2 -> 7 -> 10 -> 12
```

## Complexity
- With an adjacency **matrix** (this code): **O(V²)**
- With an adjacency list: **O(V + E)**, since each edge is looked at once.
- Space: O(V²) for the matrix.

## Backward approach (in case they ask)
Same idea from the other side: `bcost(j) = min { bcost(i) + c(i,j) }` over edges i→j, with `bcost(source) = 0`, computed from vertex 2 up to n. The answer is `bcost(n)`.

## Viva questions
- **Why DP and not greedy?** Greedy (taking the cheapest edge each step) fails here: from 1 the cheapest edge is 1→5 (2), but the best path goes through 2 or 3.
- **Principle of optimality:** every sub-path of an optimal path is also optimal. DP relies on this.
- **Why number vertices stage by stage?** So every edge goes from a lower number to a higher one, and one backward loop computes everything in the right order.
- **Can Dijkstra solve it?** Yes, but the DP is simpler and faster for a DAG / multistage graph.
