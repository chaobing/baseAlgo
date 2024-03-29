#include "../leetcommon.hpp"

vector<vector<int>> res;
bool isInArray(const vector<int> &li, int num) {
  for (auto l : li) {
    if (l == num)
      return true;
  }
  return false;
}
void backtrace(const vector<int> &arr, vector<int> &li) {
  if (li.size() == arr.size()) {
    res.push_back(li);
    return;
  }
  for (int i = 0; i < arr.size(); i++) {
    if (isInArray(li, arr[i]))
      continue;
    li.push_back(arr[i]);
    backtrace(arr, li);
    li.pop_back();
  }
}

vector<vector<int>> permute(const vector<int> &arr) {
  vector<int> li;
  backtrace(arr, li);
  return res;
}
int main(int argc, char *argv[]) {
  vector<int> arr = {1, 2, 5};
  PRINT_ARR("arr", arr)
  vector<vector<int>> mat = {
      {1, 2, 5},
      {0, 1, 2},
  };
  PRINT_MAT("permute", permute(arr))
}
