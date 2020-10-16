#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

int lenOfLCMSS(const string &s1, const string &s2) {
  int n1 = s1.size(), n2 = s2.size();
  vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp[n1][n2];
}

TEST(fun, lenOfLCMSS) {
  string s1 = "abcde";
  string s2 = "ace";
  EXPECT_EQ(3, lenOfLCMSS(s1, s2));
}
int longestPalindromeSubseq(const string &s) {
  int n = s.size();
  vector<vector<int>> dp(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    dp[i][i] = 1;
  }
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i + 1; j < n; j++) {
      if (s[i] == s[j]) {
        dp[i][j] = dp[i + 1][j - 1] + 2;
      } else {
        dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp[0][n - 1];
}
TEST(fun, longestPalindromeSubseq) {
  string s1 = "bbbab";
  string s2 = "cbbd";
  EXPECT_EQ(4, longestPalindromeSubseq(s1));
  EXPECT_EQ(2, longestPalindromeSubseq(s2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
