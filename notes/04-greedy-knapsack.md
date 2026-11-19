# Experiment 4: Greedy Knapsack (Fractional Knapsack)

## What the practical asks
Given items with **value (profit)** and **weight**, and a bag of **capacity W**, fill the bag to get **maximum profit**. In the greedy version you **can take a fraction** of an item (like gold dust).

## What "greedy" means
At each step, take the choice that looks **best right now** and never go back. For fractional knapsack this happens to give the optimal answer.

**Greedy choice:** take items in order of **highest value/weight ratio** (profit per kg).

## Steps
1. Compute `ratio = value / weight` for each item.
2. Sort items by ratio, **highest first**.
3. For each item:
   - if it fits completely, take all of it;
   - otherwise take the fraction `cap / weight` that fills the bag, then stop.

## Dry run
Capacity = 50

| Item | Value | Weight | Ratio |
|---|---|---|---|
| 1 | 60 | 10 | 6 |
| 2 | 100 | 20 | 5 |
| 3 | 120 | 30 | 4 |

```
Take item 1 fully: profit 60,  cap 50-10 = 40
Take item 2 fully: profit 160, cap 40-20 = 20
Item 3 weighs 30 > 20, so take 20/30 = 2/3 of it: profit 160 + 120*(2/3) = 240
Answer = 240
```

## C++ code
File: [`cpp/04_greedy_knapsack.cpp`](../cpp/04_greedy_knapsack.cpp)

```cpp
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
```

## Sample run
```
Enter number of items: 3
Enter value and weight of item 1: 60 10
Enter value and weight of item 2: 100 20
Enter value and weight of item 3: 120 30
Enter knapsack capacity: 50
Took full item (value 60, weight 10)
Took full item (value 100, weight 20)
Took 66.6667% of item (value 120, weight 30)
Maximum profit = 240
```

## Complexity
- Sorting: **O(n log n)**
- Picking items: O(n)
- **Total: O(n log n)**, space O(1) extra.

## Viva questions
- **Fractional vs 0/1 knapsack?** Fractional allows parts of items and greedy gives the optimal answer. 0/1 means take whole or nothing, where greedy can fail, so we use **dynamic programming** (see Experiment 10 notes). Same example in 0/1 gives 220.
- **Why sort by ratio and not by value?** A heavy valuable item might waste space. Ratio = profit per unit of capacity.
- **Greedy method's two properties:** greedy-choice property and optimal substructure.
- **Other greedy algorithms:** Prim's, Kruskal's, Dijkstra's, Huffman coding, job sequencing with deadlines.
