#include "../leetcommon.hpp"

int subarraysum(vector<int> &nums, int k) {
  int n = nums.size();
  unordered_map<int, int> sum2cnt;
  sum2cnt[0] = 1;
  int ans = 0, sum0_i = 0;
  for (int i = 0; i < n; ++i) {
    sum0_i += nums[i];
    int sum0_j = sum0_i - k;
    if (sum2cnt.find(sum0_j) != sum2cnt.end()) {
      ans += sum2cnt[sum0_j];
    }
    if (sum2cnt.find(sum0_i) != sum2cnt.end())
      sum2cnt[sum0_i]++;

    else
      sum2cnt[sum0_i] = 1;
  }
  return ans;
}

TEST(fun, subarraysum) {
  vector<int> data({1, 1, 1});
  EXPECT_EQ(2, subarraysum(data, 2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
