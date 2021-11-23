#include "../leetcommon.hpp"

/*
 * dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k-1][1] + p[i]
 * dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - p[i]
 * */
int maxProfit_K1(const vector<int> &A) {
  int dp_i10 = 0, dp_i11 = INT_MIN;
  for (auto p : A) {
    dp_i10 = max(dp_i10, dp_i11 + p);
    dp_i11 = max(dp_i11, 0 - p);
  }
  return dp_i10;
}

TEST(fun, stockProfit_K1) {
  vector<int> A = {7, 1, 5, 3, 6, 4};
  EXPECT_EQ(5, maxProfit_K1(A));
  A = {7, 6, 4, 3, 1};
  EXPECT_EQ(0, maxProfit_K1(A));
}
int maxProfit_inf(const vector<int> &A) {
  int dp_i10 = 0, dp_i11 = INT_MIN;
  for (auto p : A) {
    int tmp = dp_i10;
    dp_i10 = max(dp_i10, dp_i11 + p);
    dp_i11 = max(dp_i11, tmp - p);
  }
  return dp_i10;
}

TEST(fun, stockProfit_inf) {
  vector<int> A = {7, 1, 5, 3, 6, 4};
  EXPECT_EQ(7, maxProfit_inf(A));
  A = {1, 2, 3, 4, 5};
  EXPECT_EQ(4, maxProfit_inf(A));
}

int maxProfit_K2(const vector<int> &A) {
  int dp_i10 = 0, dp_i11 = INT_MIN;
  int dp_i20 = 0, dp_i21 = INT_MIN;
  for (auto p : A) {
    dp_i20 = max(dp_i20, dp_i21 + p);
    dp_i21 = max(dp_i21, dp_i10 - p);
    dp_i10 = max(dp_i10, dp_i11 + p);
    dp_i11 = max(dp_i11, 0 - p);
  }
  return dp_i20;
}

TEST(fun, stockProfit_K2) {
  vector<int> A = {2, 4, 1};
  EXPECT_EQ(2, maxProfit_K2(A));
  A = {3, 2, 6, 5, 0, 3};
  EXPECT_EQ(7, maxProfit_K2(A));
  A = {1, 2, 3, 4, 5};
  EXPECT_EQ(4, maxProfit_K2(A));
  A = {3, 3, 5, 0, 0, 3, 1, 4};
  EXPECT_EQ(6, maxProfit_K2(A));
}

int maxProfit_ColdDown(const vector<int> &A) {
  int dp_i10 = 0, dp_i11 = INT_MIN;
  int dp_pre_0 = 0;
  for (auto p : A) {
    int tmp = dp_i10;
    dp_i10 = max(dp_i10, dp_i11 + p);
    dp_i11 = max(dp_i11, dp_pre_0 - p);
    dp_pre_0 = tmp;
  }
  return dp_i10;
}

TEST(fun, stockProfit_ColdDown) {
  vector<int> A = {1, 2, 3, 0, 2};
  EXPECT_EQ(3, maxProfit_ColdDown(A));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
