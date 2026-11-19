#include <iostream>
using namespace std;

// 0/1 knapsack with dynamic programming (take an item fully or not at all)
int main() {
    int n, W, val[50], wt[50], dp[50][1001];
    cout << "Enter number of items: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Enter value and weight of item " << i << ": ";
        cin >> val[i] >> wt[i];
    }
    cout << "Enter capacity: ";
    cin >> W;

    // dp[i][w] = best profit using first i items with capacity w
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) dp[i][w] = 0;
            else if (wt[i] > w) dp[i][w] = dp[i - 1][w];            // can't take
            else dp[i][w] = max(dp[i - 1][w],                        // skip it
                                val[i] + dp[i - 1][w - wt[i]]);      // take it
        }
    }
    cout << "Maximum profit = " << dp[n][W] << endl;
    return 0;
}
