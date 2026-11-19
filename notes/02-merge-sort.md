# Experiment 2: Merge Sort (Divide and Conquer)

## What the practical asks
Sort an array using **merge sort** and explain the **divide and conquer** approach.

## Divide and conquer in 3 words
1. **Divide**: split the problem into smaller parts.
2. **Conquer**: solve each part (usually with recursion).
3. **Combine**: join the answers.

For merge sort:
1. **Divide**: cut the array in half.
2. **Conquer**: sort each half (recursively).
3. **Combine**: **merge** the two sorted halves into one sorted array.

A single element is already sorted. That's the base case (`low < high` fails).

## How merge works
Two sorted lists `[3 27 38]` and `[9 43 82]`. Keep a pointer on each, pick the smaller front element, move that pointer forward:
```
3 vs 9  -> 3
27 vs 9 -> 9
27 vs 43 -> 27
38 vs 43 -> 38
left done, copy rest of right -> 43 82
Result: 3 9 27 38 43 82
```

## Dry run: [38 27 43 3 9 82]
```
              [38 27 43 3 9 82]
           /                     \
      [38 27 43]               [3 9 82]
      /       \                /      \
   [38 27]   [43]          [3 9]     [82]
   /    \                  /   \
 [38]  [27]              [3]   [9]
   \    /                  \   /
   [27 38]                 [3 9]
      \       /                \      /
      [27 38 43]               [3 9 82]
           \                     /
              [3 9 27 38 43 82]
```

## C++ code
File: [`cpp/02_merge_sort.cpp`](../cpp/02_merge_sort.cpp)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Merge two sorted parts: arr[low..mid] and arr[mid+1..high]
void merge(vector<int>& arr, int low, int high, int mid) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // copy whatever is left in either half
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // put the sorted part back into arr
    for (int i = 0; i < temp.size(); i++) {
        arr[low + i] = temp[i];
    }
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;            // 1 element = already sorted

    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);           // sort left half
    mergeSort(arr, mid + 1, high);      // sort right half
    merge(arr, low, high, mid);         // combine
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
```

## Sample run
```
Enter number of elements: 6
Enter elements: 38 27 43 3 9 82
Sorted array: 3 9 27 38 43 82
```

## Complexity
| Case | Time |
|---|---|
| Best | O(n log n) |
| Average | O(n log n) |
| Worst | O(n log n) |
| **Space** | **O(n)**, for the temp array |

**Recurrence:** `T(n) = 2T(n/2) + n`. There are `log n` levels and each level does `n` work in total, so the answer is **O(n log n)** (Master theorem, case 2).

## Viva questions
- **Why is it O(n log n) always?** It always splits in half, no matter the input.
- **Is merge sort stable?** Yes (equal elements keep their order because we use `<=`).
- **Is it in-place?** No, it needs O(n) extra space.
- **Merge sort vs quick sort?** Merge sort is always O(n log n) but uses extra space. Quick sort is in-place but its worst case is O(n²).
- **Other divide and conquer examples:** quick sort, binary search, Strassen's matrix multiplication, finding max-min.
