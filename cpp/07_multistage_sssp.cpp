#include <iostream>
using namespace std;

const int INF = 1e9;

int main() {
    int n, m;
    int c[50][50];       // c[i][j] = cost of edge i -> j
    int cost[50];        // cost[i] = cheapest cost from i to the sink n
    int d[50];           // d[i]    = next vertex on that cheapest path
    int path[50];

    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            c[i][j] = INF;

    cout << "Enter each edge as: u v cost (vertices 1..n, source 1, sink n)" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        c[u][v] = w;
    }

    // Forward approach: work BACKWARDS from the sink
    cost[n] = 0;
    for (int i = n - 1; i >= 1; i--) {
        cost[i] = INF;
        for (int j = i + 1; j <= n; j++) {
            if (c[i][j] != INF && cost[j] != INF && c[i][j] + cost[j] < cost[i]) {
                cost[i] = c[i][j] + cost[j];
                d[i] = j;
            }
        }
    }

    if (cost[1] == INF) {
        cout << "No path from 1 to " << n << endl;
        return 0;
    }

    // Rebuild the path by following d[]
    int len = 0;
    path[len++] = 1;
    while (path[len - 1] != n)
        path[len] = d[path[len - 1]], len++;

    cout << "Minimum cost = " << cost[1] << endl;
    cout << "Path: ";
    for (int i = 0; i < len; i++) {
        cout << path[i];
        if (i < len - 1) cout << " -> ";
    }
    cout << endl;
    return 0;
}
