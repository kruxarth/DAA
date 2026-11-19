# Experiment 8: All-Pairs Shortest Paths (Floyd-Warshall)

## What the practical asks
Find the shortest distance between **every pair** of vertices (i, j), not just from one source. Floyd-Warshall works on any weighted directed graph, including a multistage graph.

## The idea in plain words
Start with the direct edge costs. Then for every vertex **k**, ask:

> Is going **i → k → j** cheaper than the best **i → j** I know so far?

If yes, update it. After trying every k as a "middle stop", all distances are shortest.

```
dist[i][j] = min( dist[i][j],  dist[i][k] + dist[k][j] )
```
The **k loop must be outermost**. That's the most common viva trick question.

This is **dynamic programming**: `Dᵏ[i][j]` is the shortest path from i to j using only vertices 0..k as middle stops. Each Dᵏ is built from Dᵏ⁻¹.

## Dry run
Graph (999 = no edge):
```
     0    1    2    3
0 [  0    3  999    7 ]
1 [  8    0    2  999 ]
2 [  5  999    0    1 ]
3 [  2  999  999    0 ]
```
- **k = 0** (go through 0): 1→0→3 = 8+7 = 15 < ∞, update. 2→0→1 = 5+3 = 8, update. 3→0→1 = 2+3 = 5, update...
- **k = 1, 2, 3**: keep improving.

Final:
```
0  3  5  6
5  0  2  3
3  6  0  1
2  5  7  0
```
For example 0→3 went from 7 (direct) to 6 (0→1→2→3 = 3+2+1).

## C++ code
File: [`cpp/08_floyd_warshall.cpp`](../cpp/08_floyd_warshall.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 999;    // 999 means "no direct edge"

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter cost matrix (999 = no edge):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    // try every vertex k as a middle stop between i and j
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int viaK = dist[i][k] + dist[k][j];
                if (viaK < dist[i][j]) {
                    dist[i][j] = viaK;
                }
            }
        }
    }

    cout << "All-pairs shortest distances:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] >= INF) {
                cout << "INF\t";
            }
            else {
                cout << dist[i][j] << "\t";
            }
        }
        cout << endl;
    }
    return 0;
}
```

## Sample run
```
Enter number of vertices: 4
Enter cost matrix (999 = no edge):
0 3 999 7
8 0 2 999
5 999 0 1
2 999 999 0
All-pairs shortest distances:
0	3	5	6
5	0	2	3
3	6	0	1
2	5	7	0
```
Note: 999 works as "infinity" only if real path costs stay below 999. For bigger weights, use a bigger number like 99999.

## Complexity
- Time: **O(V³)**, three nested loops.
- Space: **O(V²)**, the matrix.

## Viva questions
- **Why is k the outer loop?** Dᵏ needs all of Dᵏ⁻¹ to be finished first. With k inside, you'd use incomplete results.
- **Negative edges?** Allowed. **Negative cycles?** Not allowed. You can detect one if any `dist[i][i] < 0` after the run.
- **Floyd vs running Dijkstra from every vertex?** Floyd is O(V³) and simpler. V × Dijkstra is O(V·E log V), which is better for sparse graphs, but Dijkstra can't handle negative edges.
- **Which technique?** Dynamic programming.
