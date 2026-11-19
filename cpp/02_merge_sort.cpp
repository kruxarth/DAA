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
