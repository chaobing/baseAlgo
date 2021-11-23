#include "../leetcommon.hpp"

int lenOfLIS(const vector<int> &nums) {
  /*  dp[i]: len of LIS in nums[0-i]
   */
  vector<int> dp(nums.size(), 1);
  for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        dp[i] = std::max(dp[i], dp[j] + 1);
      }
    }
  }
  int len = 0;
  for (int i = 0; i < dp.size(); i++) {
    len = std::max(len, dp[i]);
  }
  return len;
}
int lenOfLIS2(const vector<int> &nums) {
  vector<int> top(nums.size());
  int piles = 0;
  for (int i = 0; i < nums.size(); ++i) {
    int p = nums[i];
    int l = 0, r = piles;
    while (l < r) {
      int m = (l + r) >> 1;
      if (p < top[m])
        l = m + 1;
      else
        r = m;
    }
    if (l == piles)
      piles++;
    top[l] = p;
  }
  return piles;
}

TEST(fun, lenOfLIS) {
  vector<int> nums = {10, 9, 5, 2, 3, 7, 101, 18};
  EXPECT_EQ(4, lenOfLIS(nums));
}
TEST(fun, lenOfLIS2) {
  vector<int> nums = {10, 9, 5, 2, 3, 7, 101, 18};
  EXPECT_EQ(4, lenOfLIS2(nums));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
