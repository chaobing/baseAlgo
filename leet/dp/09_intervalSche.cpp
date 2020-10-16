#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

/*min val to erase in A make it has no overlap*/
int eraseOverlapIntervals(vector<vector<int>> &A) {
  std::sort(A.begin(), A.end(), [](const vector<int> &a, const vector<int> &b) {
    if (a[0] == b[0])
      return a[1] < b[1];
    return a[0] < b[0];
  });
  int cnt = 1;
  int x_end = A[0][1];
  for (auto &inter : A) {
    int start = inter[0];
    if (start >= x_end) {
      cnt++;
      x_end = inter[1];
    }
  }
  return A.size() - cnt;
}

TEST(fun, maxA) {
  vector<vector<int>> inters = {
      {1, 2},
      {2, 3},
      {3, 4},
      {1, 3},
  };
  EXPECT_EQ(1, eraseOverlapIntervals(inters));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
