# Experiment 3: Binary Search

## What the practical asks
Find an element in a **sorted** array using binary search.

## The idea in plain words
Like searching a word in a dictionary: open the middle, and decide whether to go left or right. Each step throws away **half** the array.

1. `low = 0`, `high = n-1`
2. `mid = (low + high) / 2`
3. If `a[mid] == key`, it's found.
4. If `a[mid] < key`, the key is on the right, so `low = mid + 1`.
5. If `a[mid] > key`, the key is on the left, so `high = mid - 1`.
6. Repeat while `low <= high`. If `low > high`, the key is not present.

**The array must be sorted**, otherwise the left/right decision is meaningless.

## Dry run: search 38 in [3 9 27 38 43 82]
```
low=0 high=5 mid=2  a[2]=27 < 38  -> low=3
low=3 high=5 mid=4  a[4]=43 > 38  -> high=3
low=3 high=3 mid=3  a[3]=38 == 38 -> FOUND at index 3
```

## C++ code
File: [`cpp/03_binary_search.cpp`](../cpp/03_binary_search.cpp)

```cpp
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
```

### Recursive version (in case they ask)
```cpp
int binarySearchRec(int a[], int low, int high, int key) {
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (a[mid] == key) return mid;
    if (a[mid] < key) return binarySearchRec(a, mid + 1, high, key);
    return binarySearchRec(a, low, mid - 1, key);
}
```

## Sample run
```
Enter number of elements: 6
Enter elements in sorted order: 3 9 27 38 43 82
Enter element to search: 38
Element found at index 3 (position 4)
```

## Complexity
| Case | Time |
|---|---|
| Best | O(1), found at first mid |
| Average / Worst | O(log n) |
| Space | O(1) iterative, O(log n) recursive |

**Recurrence:** `T(n) = T(n/2) + 1`, which gives **O(log n)**.

## Viva questions
- **Precondition?** The array must be sorted.
- **Why O(log n)?** Each step halves the search space: n → n/2 → n/4 → ... → 1, which takes log₂ n steps.
- **Linear vs binary search?** Linear is O(n) and works on unsorted data. Binary is O(log n) but needs sorted data.
- **Overflow-safe mid?** `mid = low + (high - low) / 2` avoids `low + high` overflowing for huge arrays.
- **Which technique?** Divide and conquer (decrease and conquer).
