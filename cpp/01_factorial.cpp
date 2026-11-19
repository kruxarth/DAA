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
