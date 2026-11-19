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
