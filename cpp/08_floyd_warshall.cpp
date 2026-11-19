#include <iostream>
using namespace std;

const int INF = 999;    // 999 means "no direct edge"

int main() {
    int n, d[20][20];
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter cost matrix (999 = no edge):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> d[i][j];

    // Try every vertex k as a "middle stop" between i and j
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    cout << "All-pairs shortest distances:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] >= INF) cout << "INF\t";
            else cout << d[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}
