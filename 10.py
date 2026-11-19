# P10: N-Queens problem using backtracking (8 queens by default)

def solve_n_queens(n):
    solutions = []
    columns = set()
    diag1 = set()  # row - column
    diag2 = set()  # row + column
    placement = [-1] * n

    def backtrack(row):
        if row == n:
            solutions.append(placement.copy())
            return
        for col in range(n):
            if col in columns or (row - col) in diag1 or (row + col) in diag2:
                continue
            placement[row] = col
            columns.add(col)
            diag1.add(row - col)
            diag2.add(row + col)
            backtrack(row + 1)
            columns.remove(col)
            diag1.remove(row - col)
            diag2.remove(row + col)
            placement[row] = -1

    backtrack(0)
    return solutions


n = int(input("Enter number of queens (8 for the 8-Queens problem): "))
solutions = solve_n_queens(n)
if not solutions:
    print("No solution exists.")
else:
    print("Number of solutions:", len(solutions))
    print("One solution (Q marks a queen):")
    for sol in solutions[0]:
        print(" ".join("Q" if j == sol else "." for j in range(n)))
