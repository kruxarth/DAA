# Experiment 3: Binary Search

## What the practical asks
Find an element in a **sorted** array using binary search.

## The idea in plain words
Like searching a word in a dictionary: open the middle, and decide whether to go left or right. Each step throws away **half** the array.

1. `low = 0`, `high = n-1`
2. `mid = (low + high) / 2`
3. If `arr[mid] == target`, it's found.
4. If `arr[mid] < target`, the target is on the right, so `low = mid + 1`.
5. If `arr[mid] > target`, the target is on the left, so `high = mid - 1`.
6. Repeat while `low <= high`. If `low > high`, the target is not present.

**The array must be sorted**, otherwise the left/right decision is meaningless.

## Dry run: search 38 in [3 9 27 38 43 82]
```
low=0 high=5 mid=2  arr[2]=27 < 38  -> low=3
low=3 high=5 mid=4  arr[4]=43 > 38  -> high=3
low=3 high=3 mid=3  arr[3]=38 == 38 -> FOUND at index 3
```

## C++ code
File: [`cpp/03_binary_search.cpp`](../cpp/03_binary_search.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Returns index of target, or -1 if not found. arr must be SORTED.
int binarySearch(vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            low = mid + 1;      // target is on the right side
        }
        else {
            high = mid - 1;     // target is on the left side
        }
    }
    return -1;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements in sorted order: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;
    cout << "Enter element to search: ";
    cin >> target;

    int index = binarySearch(arr, target);

    if (index == -1) {
        cout << "Element not found" << endl;
    }
    else {
        cout << "Element found at index " << index << " (position " << index + 1 << ")" << endl;
    }
    return 0;
}
```

### Recursive version (in case they ask)
```cpp
int binarySearchRec(vector<int>& arr, int low, int high, int target) {
    if (low > high) return -1;          // not found

    int mid = (low + high) / 2;

    if (arr[mid] == target) {
        return mid;
    }
    else if (arr[mid] < target) {
        return binarySearchRec(arr, mid + 1, high, target);
    }
    else {
        return binarySearchRec(arr, low, mid - 1, target);
    }
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
