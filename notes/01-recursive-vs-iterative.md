# Experiment 1: Recursive vs Non-Recursive Algorithms

## What the practical asks
Write the **same problem two ways**, once with recursion and once with a loop, and state the **time and space complexity** of each. We use **factorial** (`n! = 1 × 2 × ... × n`).

## The idea in plain words
- **Recursive**: a function solves a problem by calling **itself** on a smaller version. `5! = 5 × 4!`, and `4! = 4 × 3!`, and so on until `1! = 1`.
- **Non-recursive (iterative)**: just use a `for` loop and multiply.

Every recursive function needs two things:
1. **Base case**: when to stop (`n <= 1` → return 1). Without it you get infinite calls and a **stack overflow**.
2. **Recursive case**: call yourself with a smaller input (`n * fact(n-1)`).

## Dry run: fact(4)
```
fact(4) = 4 * fact(3)
              fact(3) = 3 * fact(2)
                            fact(2) = 2 * fact(1)
                                          fact(1) = 1   <- base case
                            = 2 * 1 = 2
              = 3 * 2 = 6
        = 4 * 6 = 24
```
Each pending call sits on the **call stack** until the base case returns. That's why recursion uses O(n) memory.

## C++ code
File: [`cpp/01_factorial.cpp`](../cpp/01_factorial.cpp)

```cpp
#include <iostream>
using namespace std;

// Recursive: the function calls itself
long long factRec(int n) {
    if (n <= 1) return 1;          // base case: stop here
    return n * factRec(n - 1);     // recursive case
}

// Non-recursive (iterative): uses a loop
long long factLoop(int n) {
    long long ans = 1;
    for (int i = 2; i <= n; i++)
        ans = ans * i;
    return ans;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    if (n < 0) {
        cout << "Factorial is not defined for negative numbers\n";
        return 0;
    }

    cout << "Recursive factorial     = " << factRec(n) << endl;
    cout << "Non-recursive factorial = " << factLoop(n) << endl;
    cout << "Time  : both O(n)" << endl;
    cout << "Space : recursive O(n) (call stack), loop O(1)" << endl;
    return 0;
}
```

## Sample run
```
Enter n: 5
Recursive factorial     = 120
Non-recursive factorial = 120
```

## Complexity
| | Time | Space |
|---|---|---|
| Recursive | O(n) | O(n), for n stack frames |
| Iterative | O(n) | O(1), only one variable |

**Recurrence for the recursive version:** `T(n) = T(n-1) + c`, which solves to `O(n)`.

## Viva questions
- **What is recursion?** A function calling itself on a smaller input until it hits a base case.
- **Which is better here?** Iterative: same time, less memory, no stack-overflow risk.
- **When is recursion better?** When the problem is naturally recursive (trees, merge sort, backtracking); the code is shorter and clearer.
- **What happens without a base case?** Infinite recursion leads to a stack overflow.
- **Why `long long`?** Factorial grows fast. `int` overflows after 12!, `long long` after 20!.
- **Other examples of recursive vs iterative:** Fibonacci, sum of digits, GCD, power(x, n), tower of Hanoi.
