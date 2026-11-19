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
