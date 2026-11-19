#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix (0 = no edge):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    vector<int> key(n, INT_MAX);     // cheapest edge connecting vertex to the tree
    vector<int> parent(n, -1);       // tree vertex at the other end of that edge
    vector<bool> inMST(n, false);    // already in the tree?

    key[0] = 0;                      // start from vertex 0

    for (int count = 0; count < n; count++) {

        // 1. pick the vertex not in the tree with the smallest key
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (inMST[v] == false) {
                if (u == -1 || key[v] < key[u]) {
                    u = v;
                }
            }
        }

        inMST[u] = true;

        // 2. update keys of u's neighbours
        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && inMST[v] == false && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;
    cout << "Edges in MST:" << endl;
    for (int v = 1; v < n; v++) {
        int u = parent[v];
        cout << u << " - " << v << " : " << graph[u][v] << endl;
        total = total + graph[u][v];
    }
    cout << "Total cost of MST = " << total << endl;
    return 0;
}
