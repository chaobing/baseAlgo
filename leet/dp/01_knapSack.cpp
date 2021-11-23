#include "../leetcommon.hpp"

int knapsack(int N, int W, const vector<int> &wt, const vector<int> &val) {
  /*  dp[i][j]: num i, weight j, max value
   */
  vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= W; j++) {
      if (j - wt[i - 1] < 0)
        dp[i][j] = dp[i - 1][j]; // could not include
      else {
        dp[i][j] = std::max(dp[i - 1][j],                           /*no*/
                            dp[i - 1][j - wt[i - 1]] + val[i - 1]); /*yes*/
      }
    }
  }
  return dp[N][W];
}

TEST(fun, knapsack) {
  int N = 3, W = 4;
  vector<int> wt = {2, 1, 3};
  vector<int> val = {4, 2, 3};

  EXPECT_EQ(6, knapsack(N, W, wt, val));
}

bool canPartion(const vector<int> &nums) {
  int sum = 0;
  for (auto n : nums) {
    sum += n;
  }
  if (sum % 2 != 0)
    return false;
  sum /= 2;
  int N = nums.size();
  int W = sum;
  vector<vector<bool>> dp(N + 1, vector<bool>(W + 1, false));
  for (int i = 0; i <= N; i++) {
    dp[i][0] = true;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= W; j++) {
      if (j - nums[i - 1] < 0)
        dp[i][j] = dp[i - 1][j]; // could not include
      else {
        dp[i][j] = (dp[i - 1][j] || dp[i - 1][j - nums[i - 1]]); /*yes*/
      }
    }
  }
  return dp[N][W];
}
TEST(fun, canPartion) {
  vector<int> a1 = {1, 5, 11, 5};
  vector<int> a2 = {1, 2, 3, 5};

  EXPECT_EQ(true, canPartion(a1));
  EXPECT_EQ(false, canPartion(a2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
