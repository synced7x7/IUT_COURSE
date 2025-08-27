/* The 8 Queens problem follows one simple rule: No two queens can attack each other.
	This means that in a valid solution:
	1. No two queens can be in the same row (we place exactly one queen per row)
	2. No two queens can be in the same column
	3. No two queens can be on the same diagonal (both left and right diagonals) */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int N = 8;

bool isSafe(vector<int>& board, int row, int col) {
    // Check if a queen can be placed at board[row][col]
    
    // Check this column in all previous rows
    for (int i = 0; i < row; i++) {
        if (board[i] == col) {
            return false;
        }
    }
    
    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i] == j) {
            return false;
        }
    }
    
    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i] == j) {
            return false;
        }
    }
    
    return true;
}

bool solveNQueens(vector<int>& board, int row) {
    if (row == N) {
        return true; // All queens placed successfully
    }
    
    // Find all valid positions in current row
    vector<int> validCols;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            validCols.push_back(col);
        }
    }
    
    // If no valid location found, backtrack
    if (validCols.empty()) {
        return false;
    }
    
    // Shuffle the valid columns to try them in random order
    random_shuffle(validCols.begin(), validCols.end());
    
    // Try each valid column
    for (int col : validCols) {
        board[row] = col;
        if (solveNQueens(board, row + 1)) {
            return true;
        }
        // If placing queen here doesn't lead to solution, backtrack
        board[row] = -1;
    }
    
    return false;
}

void printSolution(vector<int>& board) {
    cout << "Solution found:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0)); // Seed for random number generation
    
    vector<int> board(N, -1);
    
    if (solveNQueens(board, 0)) {
        printSolution(board);
    } else {
        cout << "No solution found!" << endl;
    }
    
    return 0;
}