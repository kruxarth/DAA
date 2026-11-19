# Experiment 10: 8 Queens (plus 0/1 Knapsack and Flow Shop as backup)

The sheet says "flow shop scheduling **or** knapsack **or** 8 queen". Your Python file does **8 queens**, so that's the main one. A short 0/1 knapsack and a flow shop section are at the bottom in case the examiner asks.

---

## 8 Queens: the problem
Place **8 queens** on an 8×8 chessboard so that **no two attack each other**: no two in the same **row**, **column**, or **diagonal**.

## Technique: Backtracking
Build the solution step by step. If you get stuck, **undo the last choice and try the next option**.

- Put exactly **one queen per row** (so rows never clash).
- `x[row] = col` stores which column the queen in that row is in.
- For row `r`, try columns 0..n−1. If the column is safe, place the queen and go to row `r+1`.
- If no column works, return. The previous row then tries its next column. **That's the backtrack.**

## The safety check
Queen at (row, col) clashes with an earlier queen at (prev, x[prev]) if:
- **same column**: `x[prev] == col`
- **same diagonal**: `|x[prev] − col| == |prev − row|` (equal row and column distance means they're on a diagonal)

## Dry run with 4 queens (smaller and easier to show)
```
Row 0: try col 0   Q . . .
Row 1: col 0,1 unsafe -> col 2   . . Q .
Row 2: col 0..3 all unsafe -> BACKTRACK to row 1
Row 1: try col 3   . . . Q
Row 2: col 1       . Q . .
Row 3: all unsafe -> BACKTRACK ... row 2 has no more -> row 1 has no more
Row 0: try col 1   . Q . .
Row 1: col 3       . . . Q
Row 2: col 0       Q . . .
Row 3: col 2       . . Q .   <- SOLUTION
```
4 queens has **2** solutions. 8 queens has **92**.

## C++ code
File: [`cpp/10_n_queens.cpp`](../cpp/10_n_queens.cpp)

```cpp
#include <iostream>
#include <cstdlib>
using namespace std;

int n;
int x[20];          // x[row] = column of the queen in that row
int solutions = 0;

// Can a queen go at (row, col)? Check all queens placed in earlier rows.
bool place(int row, int col) {
    for (int prev = 0; prev < row; prev++) {
        if (x[prev] == col) return false;                         // same column
        if (abs(x[prev] - col) == abs(prev - row)) return false;  // same diagonal
    }
    return true;
}

void printBoard() {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++)
            cout << (x[r] == c ? "Q " : ". ");
        cout << endl;
    }
}

void nQueens(int row) {
    if (row == n) {                 // all queens placed
        solutions++;
        if (solutions == 1) {
            cout << "First solution:" << endl;
            printBoard();
        }
        return;
    }
    for (int col = 0; col < n; col++) {
        if (place(row, col)) {
            x[row] = col;           // place queen
            nQueens(row + 1);       // go to next row
        }                           // loop continues = BACKTRACK and try next col
    }
}

int main() {
    cout << "Enter number of queens: ";
    cin >> n;
    nQueens(0);
    if (solutions == 0) cout << "No solution" << endl;
    else cout << "Total solutions = " << solutions << endl;
    return 0;
}
```

## Sample run
```
Enter number of queens: 8
First solution:
Q . . . . . . .
. . . . Q . . .
. . . . . . . Q
. . . . . Q . .
. . Q . . . . .
. . . . . . Q .
. Q . . . . . .
. . . Q . . . .
Total solutions = 92
```

## Complexity
- Worst case **O(n!)**: row 0 has n choices, row 1 fewer, and so on. Backtracking prunes most branches early.
- Space: **O(n)** for `x[]` and the recursion depth.

## Viva questions
- **What is backtracking?** Try a choice. If it leads to a dead end, undo it and try the next one. It's DFS on the state-space tree with pruning.
- **What is the state-space tree?** The tree of all partial placements. The root is an empty board, and level k means k queens are placed.
- **Bounding function?** The `place()` check. It kills branches that can't lead to a solution.
- **Why one queen per row?** It removes row clashes automatically and shrinks the search space.
- **Solutions for n = 1, 2, 3, 4, 8?** 1, 0, 0, 2, 92.
- **Other backtracking problems:** sum of subsets, graph coloring, Hamiltonian cycle, sudoku.

---

## Backup A: 0/1 Knapsack (Dynamic Programming)
Each item is taken **whole or not at all**. Greedy fails here, so we use DP.

`dp[i][w]` is the best profit using the first i items with capacity w:
```
if wt[i] > w:  dp[i][w] = dp[i-1][w]                                  (can't take)
else:          dp[i][w] = max(dp[i-1][w], val[i] + dp[i-1][w-wt[i]])  (skip vs take)
```
File: [`cpp/10b_knapsack_01.cpp`](../cpp/10b_knapsack_01.cpp)

```cpp
#include <iostream>
using namespace std;

// 0/1 knapsack with dynamic programming (take an item fully or not at all)
int main() {
    int n, W, val[50], wt[50], dp[50][1001];
    cout << "Enter number of items: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Enter value and weight of item " << i << ": ";
        cin >> val[i] >> wt[i];
    }
    cout << "Enter capacity: ";
    cin >> W;

    // dp[i][w] = best profit using first i items with capacity w
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) dp[i][w] = 0;
            else if (wt[i] > w) dp[i][w] = dp[i - 1][w];            // can't take
            else dp[i][w] = max(dp[i - 1][w],                        // skip it
                                val[i] + dp[i - 1][w - wt[i]]);      // take it
        }
    }
    cout << "Maximum profit = " << dp[n][W] << endl;
    return 0;
}
```

Same items as Experiment 4 (60/10, 100/20, 120/30, capacity 50) gives **220** (items 2 + 3), not 240, because we can't take fractions.
Complexity: **O(n × W)** time and space.

---

## Backup B: Flow Shop Scheduling (Johnson's rule, 2 machines)
**Problem:** n jobs, each must go through **machine 1 then machine 2**. Find the job order that minimizes the total finish time (**makespan**).

**Johnson's rule:**
1. Find the smallest time among all jobs on both machines.
2. If it's on **machine 1**, put that job **as early as possible**. If it's on **machine 2**, put it **as late as possible**.
3. Remove that job and repeat.

Example:

| Job | M1 | M2 |
|---|---|---|
| J1 | 3 | 6 |
| J2 | 5 | 2 |
| J3 | 1 | 2 |
| J4 | 6 | 6 |
| J5 | 7 | 5 |

```
min = 1 (J3, M1) -> first:  J3 _ _ _ _
min = 2 (J2, M2) -> last:   J3 _ _ _ J2
min = 3 (J1, M1) -> early:  J3 J1 _ _ J2
min = 5 (J5, M2) -> late:   J3 J1 _ J5 J2
J4 fills the gap:           J3 J1 J4 J5 J2
```
Makespan for this order = **24**.
Complexity: O(n log n) (it's essentially a sort). It's a greedy method.
