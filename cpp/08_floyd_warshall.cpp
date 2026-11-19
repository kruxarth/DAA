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
