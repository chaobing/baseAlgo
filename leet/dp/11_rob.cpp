#include <iostream>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

int robBase(const vector<int> &A) {
  int n = A.size();
  // dp[i+1], dp[i+2]
  int dp_i_1 = 0, dp_i_2 = 0;
  int dp_i = 0;
  for (int i = n - 1; i >= 0; i--) {
    dp_i = max(dp_i_1, dp_i_2 + A[i]);
    dp_i_2 = dp_i_1;
    dp_i_1 = dp_i;
  }
  return dp_i;
}

TEST(fun, robBase) {
  vector<int> A = {1, 2, 3, 1};
  EXPECT_EQ(4, robBase(A));
  A = {2, 7, 9, 3, 1};
  EXPECT_EQ(12, robBase(A));
}

int robRange(const vector<int> &A, int start, int end) {
  // dp[i+1], dp[i+2]
  int dp_i_1 = 0, dp_i_2 = 0;
  int dp_i = 0;
  for (int i = end; i >= start; i--) {
    dp_i = max(dp_i_1, dp_i_2 + A[i]);
    dp_i_2 = dp_i_1;
    dp_i_1 = dp_i;
  }
  return dp_i;
}
int robCircle(const vector<int> &A) {
  int n = A.size();
  if (n == 1)
    return A[0];
  return max(robRange(A, 0, n - 2), robRange(A, 1, n - 1));
}

TEST(fun, robCircle) {
  vector<int> A = {1, 2, 3, 1};
  EXPECT_EQ(4, robCircle(A));
  A = {2, 3, 2};
  EXPECT_EQ(3, robCircle(A));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
