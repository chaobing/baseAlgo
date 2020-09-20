#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

string kn2str(int k, int n) {
  return std::to_string(k) + "_" + std::to_string(n);
}
unordered_map<string, int> memo;
/*dp[k][n]: k egg, n floor, least times*/
int eggDrop(int k, int n) {
  if (k == 1)
    return n;
  if (n == 0)
    return 0;
  if (memo.count(kn2str(k, n)))
    return memo[kn2str(k, n)];
  int res = 0x7fffffff;
  for (int i = 1; i <= n; i++) {
    /*broken, not broken*/
    res = std::min(res, std::max(eggDrop(k - 1, i - 1), eggDrop(k, n - i)) + 1);
  }
  memo[kn2str(k, n)] = res;
  // cout << kn2str(k, n) << " : " << res << endl;
  return res;
}

TEST(fun, eggDrop) {
  int K = 2, N = 100;
  EXPECT_EQ(14, eggDrop(K, N));
  K = 1, N = 7;
  EXPECT_EQ(7, eggDrop(K, N));
}
/*dp[k][m]: k egg, m times, max floor*/
int eggDrop2(int k, int n) {
  int m = 0;
  vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
  while (dp[k][m] < n) {
    m++;
    for (int j = 1; j < k; j++) {
      /*broken, not broken*/
      dp[j][m] = dp[j - 1][m - 1] + dp[j][m - 1] + 1;
    }
  }
  return m;
}
  TEST(fun, eggDrop2) {
    int K = 2, N = 100;
    EXPECT_EQ(14, eggDrop(K, N));
    K = 1, N = 7;
    EXPECT_EQ(7, eggDrop(K, N));
  }

  int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
