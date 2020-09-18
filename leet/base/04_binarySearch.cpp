#include <iostream>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

#define PRINT_ARR(prefix, arr)                                                 \
  do {                                                                         \
    cout << prefix << ": " << endl;                                            \
    for (auto a : arr)                                                         \
      cout << a << " ";                                                        \
    cout << endl;                                                              \
  } while (0);
/*
 * mode: 0: find; 1: left_bound; 2: right_bound
 */
int binarySearch(const vector<int> &A, int tar, int mode) {
  int l = 0, r = A.size() - 1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (tar == A[m]) {
      if (mode == 0)
        return m;
      else if (mode == 1)
        r = m - 1;
      else if (mode == 2)
        l = m + 1;
    } else if (tar > A[m]) {
      l = m + 1;
    } else if (tar < A[m]) {
      r = m - 1;
    }
  }
  if (mode == 0) {
    return -1;
  } else if (mode == 1) {
    if (l >= A.size() || A[l] != tar)
      return -1;
    return l;
  } else if (mode == 2) {
    if (r < 0 || A[r] != tar)
      return -1;
    return r;
  }
}
TEST(binarySearch, binarySearch) {
  vector<int> coins = {1, 2, 2, 2, 4, 5};
  EXPECT_EQ(2, binarySearch(coins, 2, 0));
}
TEST(left_bound, binarySearch) {
  vector<int> coins = {1, 2, 2, 2, 4, 5};
  EXPECT_EQ(1, binarySearch(coins, 2, 1));
}
TEST(right_bound, binarySearch) {
  vector<int> coins = {1, 2, 2, 2, 4, 5};
  EXPECT_EQ(3, binarySearch(coins, 2, 2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
