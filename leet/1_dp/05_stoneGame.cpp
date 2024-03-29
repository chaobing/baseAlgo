#include "../leetcommon.hpp"

struct Loop {
public:
  int fir;
  int sec;
  Loop() : fir(0), sec(0) {}
  Loop(int f, int s) : fir(f), sec(s) {}
};
int stoneGame(const vector<int> &piles) {
  int n = piles.size();
  vector<vector<Loop>> dp(n, vector<Loop>(n));
  for (int i = 0; i < n; i++) {
    dp[i][i].fir = piles[i];
    dp[i][i].sec = 0;
  }
  for (int l = 2; l <= n; l++) {
    for (int i = 0; i <= n - l; i++) {
      int j = i + l - 1;
      int left = piles[i] + dp[i + 1][j].sec;
      int right = piles[j] + dp[i][j - 1].sec;
      if (left > right) {
        dp[i][j].fir = left;
        dp[i][j].sec = dp[i + 1][j].fir;
      } else {
        dp[i][j].fir = right;
        dp[i][j].sec = dp[i][j - 1].fir;
      }
    }
  }
  Loop res = dp[0][n - 1];
  cout << "fir, sec: " << res.fir << ", " << res.sec << endl;
  return res.fir - res.sec;
}

TEST(fun, stoneGame) {
  vector<int> piles = {3, 9, 1, 2};
  EXPECT_EQ(7, stoneGame(piles));
  piles = {1, 100, 3};
  EXPECT_EQ(-96, stoneGame(piles));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
