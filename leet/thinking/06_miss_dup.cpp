#include "../leetcommon.hpp"

////////////////////////////////////////////////////////////////////////
// You have a set of integers s, which originally contains all the numbers from
// 1 to n. Unfortunately, due to some error, one of the numbers in s got
// duplicated to another number in the set, which results in repetition of one
// number and loss of another number.
vector<int> findErrorNums(vector<int> &nums) {
  int n = nums.size();
  int dup = -1;
  for (int i = 0; i < n; ++i) {
    int idx = abs(nums[i]) - 1;
    if (nums[idx] < 0)
      dup = abs(nums[i]);
    else
      nums[idx] *= -1;
  }
  int miss = -1;
  for (int i = 0; i < n; ++i) {
    if (nums[i] > 0)
      miss = i + 1;
  }
  vector<int> res({dup, miss});
  return res;
}

TEST(fun, findErrorNums) {
  vector<int> data({1, 2, 2, 4});
  vector<int> res({2, 3});
  EXPECT_EQ(res, findErrorNums(data));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
