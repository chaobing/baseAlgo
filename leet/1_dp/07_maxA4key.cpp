#include "../leetcommon.hpp"

int maxA(int n) {
  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1] + 1;
    for (int j = 2; j < i; j++) {
      dp[i] = std::max(dp[i], dp[j - 2] * (i - j + 1));
    }
  }
    return dp[n];
}

TEST(fun, maxA) {
  EXPECT_EQ(9, maxA(7));
  EXPECT_EQ(3, maxA(3));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
