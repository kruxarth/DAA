#include <iostream>
using namespace std;

// Returns index of key, or -1 if not found. Array must be SORTED.
int binarySearch(int a[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == key) return mid;        // found
        else if (a[mid] < key) low = mid + 1; // go right
        else high = mid - 1;                  // go left
    }
    return -1;
}

int main() {
    int n, key, a[100];
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter elements in sorted order: ";
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << "Enter element to search: ";
    cin >> key;

    int pos = binarySearch(a, n, key);
    if (pos == -1) cout << "Element not found" << endl;
    else cout << "Element found at index " << pos
              << " (position " << pos + 1 << ")" << endl;
    return 0;
}
