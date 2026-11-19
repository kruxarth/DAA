#include <bits/stdc++.h>
using namespace std;

// 0/1 knapsack: take an item fully or not at all (dynamic programming)
int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> value(n), weight(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
    }

    int W;
    cout << "Enter capacity: ";
    cin >> W;

    // dp[i][w] = best profit using the first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];

            int take = 0;
            if (weight[i - 1] <= w) {
                take = value[i - 1] + dp[i - 1][w - weight[i - 1]];
            }

            dp[i][w] = max(take, notTake);
        }
    }

    cout << "Maximum profit = " << dp[n][W] << endl;
    return 0;
}
