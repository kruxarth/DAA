# P3: Binary search (input array must be sorted)

def binary_search(arr, key):
    low, high = 0, len(arr) - 1

    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == key:
            return mid
        if arr[mid] < key:
            low = mid + 1
        else:
            high = mid - 1

    return -1


arr = list(map(int, input("Enter sorted numbers separated by spaces: ").split()))
key = int(input("Enter element to search: "))
index = binary_search(arr, key)

if index == -1:
    print("Element not found.\n")
else:
    print("Element found at position", index + 1, "\n")
