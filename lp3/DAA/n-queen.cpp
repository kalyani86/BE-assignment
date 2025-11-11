#include <iostream>
#include <vector>
using namespace std;

// Function to check if a queen can be placed at (row, col)
bool isSafe(int row, int col, vector<vector<int>> &board, int n) {
    // Check vertical column
    for (int i = 0; i < n; i++)
        if (board[i][col] == 1 && i != row)
            return false;

    // Check upper-left and lower-right diagonals
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1 && (abs(i - row) == abs(j - col)))
                return false;
        }
    }

    // Check same row
    for (int j = 0; j < n; j++)
        if (board[row][j] == 1 && j != col)
            return false; 

    return true;
}

// Recursive function to place remaining queens
void solve(int row, vector<vector<int>> &board,
           vector<vector<vector<int>>> &answers, int n, int firstRow) {
    if (row == n) {
        answers.push_back(board);
        return;
    }

    // Skip the row where the first queen is already placed
    if (row == firstRow) {
        solve(row + 1, board, answers, n, firstRow);
        return;
    }

    // Try placing queens in this row
    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, board, n)) {
            board[row][col] = 1;
            solve(row + 1, board, answers, n, firstRow);
            board[row][col] = 0; // backtrack
        }
    }
}

// Function to display one solution
void disp(vector<vector<int>> &temp) {
    cout << "------------------------------------------\n";
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp[i].size(); j++) {
            cout << (temp[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << "------------------------------------------\n";
}

// Function to handle N-Queens with fixed queen
void nQueenWithFixed(int n, int firstRow, int firstCol) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<vector<int>>> answers;

    // Place the first queen manually
    board[firstRow][firstCol] = 1;

    // Start solving from row 0
    solve(0, board, answers, n, firstRow);

    // Display results
    if (answers.empty())
        cout << "No solution possible with first queen at (" << firstRow << ", " << firstCol << ").\n";
    else {
        cout << "\nSolutions with first queen at (" << firstRow << ", " << firstCol << "):\n";
        for (auto &ans : answers) disp(ans);
    }
}

int main() {
    int n, firstRow, firstCol;

    cout << "Enter the value of n: ";
    cin >> n;

    if (n <= 3) {
        cout << "Solution not possible for n ≤ 3\n";
        return 0;
    }

    cout << "Enter the row (0 to " << n - 1 << ") for the first queen: ";
    cin >> firstRow;
    cout << "Enter the column (0 to " << n - 1 << ") for the first queen: ";
    cin >> firstCol;

    if (firstRow < 0 || firstRow >= n || firstCol < 0 || firstCol >= n) {
        cout << "Invalid position!\n";
        return 0;
    }

    nQueenWithFixed(n, firstRow, firstCol);
    return 0;
}