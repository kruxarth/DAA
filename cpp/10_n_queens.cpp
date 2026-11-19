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
