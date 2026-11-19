#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    double value, weight, ratio;
};

// Sort so the item with the highest value/weight comes first
bool cmp(Item x, Item y) {
    return x.ratio > y.ratio;
}

int main() {
    int n;
    double cap;
    Item item[100];

    cout << "Enter number of items: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> item[i].value >> item[i].weight;
        item[i].ratio = item[i].value / item[i].weight;
    }
    cout << "Enter knapsack capacity: ";
    cin >> cap;

    sort(item, item + n, cmp);

    double profit = 0;
    for (int i = 0; i < n && cap > 0; i++) {
        if (item[i].weight <= cap) {            // whole item fits
            profit += item[i].value;
            cap -= item[i].weight;
            cout << "Took full item (value " << item[i].value
                 << ", weight " << item[i].weight << ")" << endl;
        } else {                                // take only a part
            double frac = cap / item[i].weight;
            profit += item[i].value * frac;
            cout << "Took " << frac * 100 << "% of item (value "
                 << item[i].value << ", weight " << item[i].weight << ")" << endl;
            cap = 0;
        }
    }

    cout << "Maximum profit = " << profit << endl;
    return 0;
}
