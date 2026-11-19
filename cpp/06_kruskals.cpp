#include <iostream>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

bool cmp(Edge a, Edge b) {
    return a.w < b.w;           // smallest weight first
}

int parent[100];

// Find the "leader" (root) of the group that x belongs to
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

int main() {
    int n, m;
    Edge e[100];

    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    cout << "Enter each edge as: u v weight" << endl;
    for (int i = 0; i < m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;

    sort(e, e + m, cmp);

    for (int i = 0; i < n; i++) parent[i] = i;   // every vertex is its own group

    int total = 0, taken = 0;
    cout << "Edges in MST:" << endl;
    for (int i = 0; i < m && taken < n - 1; i++) {
        int a = find(e[i].u);
        int b = find(e[i].v);
        if (a != b) {                 // different groups -> no cycle
            parent[a] = b;            // join the groups (union)
            cout << e[i].u << " - " << e[i].v << " : " << e[i].w << endl;
            total += e[i].w;
            taken++;
        }                             // same group -> would make a cycle, skip
    }
    cout << "Total cost of MST = " << total << endl;
    return 0;
}
