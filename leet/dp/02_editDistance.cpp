#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

int editDistance(const string &s1, const string &s2) {
  int n1 = s1.size(), n2 = s2.size();
  /* dp[i][j]: editDistance between s1[0-i] and s2[0-j]
   */
  vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
  for (int i = 0; i < n1 + 1; i++) {
    dp[i][0] = i;
  }
  for (int i = 0; i < n2 + 1; i++) {
    dp[0][i] = i;
  }
  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + std::min(std::min(dp[i - 1][j], dp[i - 1][j - 1]),
                                dp[i][j - 1]);
      }
    }
  }
  return dp[n1][n2];
}

TEST(fun, editDistance) {
  string s1 = "horse", s2 = "ros";
  EXPECT_EQ(3, editDistance(s1, s2));
  s1 = "intention", s2 = "execution";
  EXPECT_EQ(5, editDistance(s1, s2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
