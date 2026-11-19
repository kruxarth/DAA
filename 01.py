# P1: Recursive and non-recursive factorial with complexity

def factorial_recursive(n):
    if n <= 1:
        return 1
    return n * factorial_recursive(n - 1)


def factorial_iterative(n):
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


n = int(input("Enter a non-negative integer: "))

if n < 0:
    print("Factorial is not defined for negative integers.")
else:
    print("Recursive factorial:", factorial_recursive(n))
    print("Non-recursive factorial:", factorial_iterative(n))
    print("Recursive time complexity: O(n)")
    print("Recursive auxiliary space complexity: O(n)")
    print("Iterative time complexity: O(n)")
    print("Iterative auxiliary space complexity: O(1)")

print("\n")
