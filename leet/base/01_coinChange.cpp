#include "../leetcommon.hpp"

int coinChange(const vector<int> &coin, int n) {
  /*  dp[i]: num of combine  sum  == i
   *  dp[i] = 0, n=0;  -1, n<0; min(dp[i-coins[j]]) + 1
   */
  vector<int> dp(n + 1, n + 1);
  dp[0] = 0;
  for (int i = 0; i <= n; i++) {
    for (auto c : coin) {
      if (i - c < 0)
        continue;
      else {
        dp[i] = std::min(dp[i], (dp[i - c] + 1));
      }
    }
  }
  return dp[n] == n + 1 ? -1 : dp[n];
}

TEST(fun, coinChange) {
  vector<int> coins = {1, 2, 5};
  EXPECT_EQ(3, coinChange(coins, 11));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
