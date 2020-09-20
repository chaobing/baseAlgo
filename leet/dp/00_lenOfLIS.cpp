#include <iostream>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

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

TEST(fun, coinChange) {
  vector<int> nums = {10, 9, 5, 2, 3, 7, 101, 18};
  EXPECT_EQ(4, lenOfLIS(nums));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
