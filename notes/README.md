# DAA Practical Exam Notes

Read these in order. Each note has: what the practical asks, the idea in plain words, a dry run, simple C++ code (tested), a sample run, complexity, and viva questions.

| # | Experiment | Technique | Notes | C++ |
|---|---|---|---|---|
| 1 | Recursive vs non-recursive (factorial) | Recursion | [notes](01-recursive-vs-iterative.md) | [code](../cpp/01_factorial.cpp) |
| 2 | Merge sort | Divide and conquer | [notes](02-merge-sort.md) | [code](../cpp/02_merge_sort.cpp) |
| 3 | Binary search | Divide and conquer | [notes](03-binary-search.md) | [code](../cpp/03_binary_search.cpp) |
| 4 | Greedy (fractional) knapsack | Greedy | [notes](04-greedy-knapsack.md) | [code](../cpp/04_greedy_knapsack.cpp) |
| 5 | MST: Prim's | Greedy | [notes](05-prims-mst.md) | [code](../cpp/05_prims.cpp) |
| 6 | MST: Kruskal's | Greedy + union-find | [notes](06-kruskals-mst.md) | [code](../cpp/06_kruskals.cpp) |
| 7 | Multistage graph, single source | Dynamic programming | [notes](07-multistage-single-source.md) | [code](../cpp/07_multistage_sssp.cpp) |
| 8 | All-pairs shortest path (Floyd-Warshall) | Dynamic programming | [notes](08-all-pairs-floyd.md) | [code](../cpp/08_floyd_warshall.cpp) |
| 9 | Huffman coding | Greedy | [notes](09-huffman-coding.md) | [code](../cpp/09_huffman.cpp) |
| 10 | 8 queens (+ 0/1 knapsack, flow shop) | Backtracking / DP | [notes](10-n-queens.md) | [code](../cpp/10_n_queens.cpp), [0/1 knapsack](../cpp/10b_knapsack_01.cpp) |

## One-page cheat sheet

| Algorithm | Time | Space | Technique |
|---|---|---|---|
| Factorial (recursive) | O(n) | O(n) stack | Recursion |
| Factorial (loop) | O(n) | O(1) | Iteration |
| Merge sort | O(n log n) all cases | O(n) | Divide and conquer |
| Binary search | O(log n), best O(1) | O(1) | Divide and conquer |
| Fractional knapsack | O(n log n) | O(1) | Greedy (sort by value/weight) |
| Prim's (matrix) | O(V²) | O(V) | Greedy |
| Prim's (heap) | O(E log V) | O(V) | Greedy |
| Kruskal's | O(E log E) | O(V) | Greedy + union-find |
| Multistage graph | O(V + E), O(V²) with a matrix | O(V) | DP |
| Floyd-Warshall | O(V³) | O(V²) | DP |
| Huffman | O(n log n) | O(n) | Greedy + min-heap |
| N-queens | O(n!) worst | O(n) | Backtracking |
| 0/1 knapsack | O(n·W) | O(n·W) | DP |

## Techniques in one line each
- **Divide and conquer:** split into independent subproblems, solve them, combine. (merge sort, binary search)
- **Greedy:** make the best local choice and never look back. Fast, but only correct for some problems. (knapsack-fractional, Prim's, Kruskal's, Huffman)
- **Dynamic programming:** subproblems overlap, so save their answers in a table. Uses the **principle of optimality**. (multistage graph, Floyd, 0/1 knapsack)
- **Backtracking:** build the answer step by step and undo when stuck. (N-queens)

**Greedy vs DP:** greedy makes one choice and moves on. DP tries every option for a subproblem and keeps the best. Fractional knapsack works with greedy, 0/1 knapsack needs DP.

## Compile and run
```bash
g++ 05_prims.cpp -o prims
```
```bash
./prims
```

## Exam-day tips
- Write the **header comment** (aim, technique, complexity) at the top. Examiners like it.
- Keep the **sample input** from each note ready to type. Correct output on the textbook example is the fastest way to show it works.
- If asked "why this complexity", say the **recurrence** (merge sort `T(n)=2T(n/2)+n`, binary search `T(n)=T(n/2)+1`).
- Prim's and Kruskal's on the same graph **must give the same total**: a quick self-check.
