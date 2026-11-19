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
