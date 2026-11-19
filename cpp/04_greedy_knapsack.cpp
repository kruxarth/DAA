#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    vector<double> value(n), weight(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
    }

    double capacity;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // store {ratio, index} for every item
    vector<pair<double, int>> items;
    for (int i = 0; i < n; i++) {
        double ratio = value[i] / weight[i];
        items.push_back({ratio, i});
    }

    // highest ratio first
    sort(items.begin(), items.end());
    reverse(items.begin(), items.end());

    double profit = 0;
    for (int k = 0; k < n; k++) {
        if (capacity == 0) break;

        int i = items[k].second;

        if (weight[i] <= capacity) {
            // whole item fits
            profit = profit + value[i];
            capacity = capacity - weight[i];
            cout << "Took full item (value " << value[i] << ", weight " << weight[i] << ")" << endl;
        }
        else {
            // take only the part that fits
            double fraction = capacity / weight[i];
            profit = profit + value[i] * fraction;
            capacity = 0;
            cout << "Took " << fraction * 100 << "% of item (value " << value[i] << ", weight " << weight[i] << ")" << endl;
        }
    }

    cout << "Maximum profit = " << profit << endl;
    return 0;
}
