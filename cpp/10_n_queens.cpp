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
