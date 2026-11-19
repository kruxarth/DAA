# Experiment 10: 8 Queens (plus 0/1 Knapsack and Flow Shop as backup)

The sheet says "flow shop scheduling **or** knapsack **or** 8 queen". Your Python file does **8 queens**, so that's the main one. A short 0/1 knapsack and a flow shop section are at the bottom in case the examiner asks.

---

## 8 Queens: the problem
Place **8 queens** on an 8×8 chessboard so that **no two attack each other**: no two in the same **row**, **column**, or **diagonal**.

## Technique: Backtracking
Build the solution step by step. If you get stuck, **undo the last choice and try the next option**.

- Put exactly **one queen per row** (so rows never clash).
- The board is a `vector<string>`, every cell starts as `'.'`, and a queen is `'Q'`.
- For row `row`, try every column. If it's safe, put `'Q'`, solve the next row, then put `'.'` back. **Putting `'.'` back is the backtrack.**
- If no column works, the function just returns, and the previous row tries its next column.

## The safety check
Rows below are still empty, so `isSafe` only looks **upwards** from (row, col) in 3 directions:
- **straight up**: same column
- **up-left**: `row-1, col-1`, then `row-2, col-2`, ...
- **up-right**: `row-1, col+1`, then `row-2, col+2`, ...

If any of these cells has a `'Q'`, the spot is not safe. No need to check the same row, because we place only one queen per row.

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
#include <bits/stdc++.h>
using namespace std;

int solutions = 0;

// Can a queen go at (row, col)? Only rows above are filled, so check upwards.
bool isSafe(vector<string>& board, int row, int col, int n) {

    // same column, above
    for (int r = row - 1; r >= 0; r--) {
        if (board[r][col] == 'Q') return false;
    }

    // upper-left diagonal
    int r = row - 1;
    int c = col - 1;
    while (r >= 0 && c >= 0) {
        if (board[r][c] == 'Q') return false;
        r--;
        c--;
    }

    // upper-right diagonal
    r = row - 1;
    c = col + 1;
    while (r >= 0 && c < n) {
        if (board[r][c] == 'Q') return false;
        r--;
        c++;
    }

    return true;
}

void printBoard(vector<string>& board, int n) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout << board[r][c] << " ";
        }
        cout << endl;
    }
}

void solve(vector<string>& board, int row, int n) {
    if (row == n) {
        // all queens placed
        solutions++;
        if (solutions == 1) {
            cout << "First solution:" << endl;
            printBoard(board, n);
        }
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';          // place queen
            solve(board, row + 1, n);       // go to next row
            board[row][col] = '.';          // BACKTRACK: remove queen
        }
    }
}

int main() {
    int n;
    cout << "Enter number of queens: ";
    cin >> n;

    vector<string> board(n, string(n, '.'));
    solve(board, 0, n);

    if (solutions == 0) {
        cout << "No solution" << endl;
    }
    else {
        cout << "Total solutions = " << solutions << endl;
    }
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
- Space: **O(n²)** for the board, plus O(n) recursion depth.

## Viva questions
- **What is backtracking?** Try a choice. If it leads to a dead end, undo it and try the next one. It's DFS on the state-space tree with pruning.
- **What is the state-space tree?** The tree of all partial placements. The root is an empty board, and level k means k queens are placed.
- **Bounding function?** The `isSafe()` check. It kills branches that can't lead to a solution.
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
#include <bits/stdc++.h>
using namespace std;

// 0/1 knapsack: take an item fully or not at all (dynamic programming)
int main() {
    int n;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> value(n), weight(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
    }

    int W;
    cout << "Enter capacity: ";
    cin >> W;

    // dp[i][w] = best profit using the first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            int notTake = dp[i - 1][w];

            int take = 0;
            if (weight[i - 1] <= w) {
                take = value[i - 1] + dp[i - 1][w - weight[i - 1]];
            }

            dp[i][w] = max(take, notTake);
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
