#include "../leetcommon.hpp"

vector<vector<string>> res;
bool isValid(const vector<string> &board, int r, int c) {
  int n = board.size();
  // col
  for (int i = 0; i < n; i++) {
    if (board[i][c] == 'Q')
      return false;
  }
  // right-up
  for (int i = r - 1, j = c + 1; i >= 0 && j < n; i--, j++) {
    if (board[i][j] == 'Q')
      return false;
  }
  // left-up
  for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) {
    if (board[i][j] == 'Q')
      return false;
  }
  return true;
}

void backtrace(vector<string> &board, int r) {
  if (r == board.size()) {
    res.push_back(board);
    return;
  }
  int n = board[r].size();
  for (int c = 0; c < n; c++) {
    if (!isValid(board, r, c))
      continue;
    board[r][c] = 'Q';
    backtrace(board, r + 1);
    board[r][c] = 'X';
  }
}

vector<vector<string>> solveNQueue(int n) {
  vector<string> board(n, string(n, 'X'));
  backtrace(board, 0);
  return res;
};

int main(int argc, char *argv[]) { PRINT_MAT("mat", solveNQueue(8)) return 0; }
