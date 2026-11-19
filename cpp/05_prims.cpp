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
