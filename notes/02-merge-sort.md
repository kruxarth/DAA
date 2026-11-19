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
#include <iostream>
using namespace std;

int a[100], temp[100];

// Merge two sorted halves: a[low..mid] and a[mid+1..high]
void merge(int low, int mid, int high) {
    int i = low;       // pointer in left half
    int j = mid + 1;   // pointer in right half
    int k = low;       // pointer in temp

    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else              temp[k++] = a[j++];
    }
    while (i <= mid)  temp[k++] = a[i++];   // leftovers from left
    while (j <= high) temp[k++] = a[j++];   // leftovers from right

    for (int x = low; x <= high; x++)        // copy back
        a[x] = temp[x];
}

void mergeSort(int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(low, mid);         // DIVIDE + CONQUER left
        mergeSort(mid + 1, high);    // DIVIDE + CONQUER right
        merge(low, mid, high);       // COMBINE
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> a[i];

    mergeSort(0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
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
