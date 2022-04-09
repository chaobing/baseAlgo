#include "../leetcommon.hpp"
vector<vector<int>> twoSum(vector<int> &nums, int i, int tar) {
  int l = i, r = nums.size() - 1;
  vector<vector<int>> res;
  while (l < r) {
    int left = nums[l], right = nums[r];
    int sum = left + right;
    if (sum == tar) {
      res.push_back({left, right});
      while (l < r && nums[l] == left)
        l++;
      while (l < r && nums[r] == right)
        r--;
    } else if (sum > tar) {
      while (l < r && nums[r] == right)
        r--;
    } else {
      while (l < r && nums[l] == left)
        l++;
    }
  }
  return res;
}
vector<vector<int>> threeSum(vector<int> &nums) {
  std::sort(nums.begin(), nums.end());
  vector<vector<int>> res;
  for (int i = 0; i < nums.size(); i++) {
    int tar = 0 - nums[i];
    auto two = twoSum(nums, i + 1, tar);
    for (auto &tmp : two) {
      tmp.push_back(nums[i]);
      res.push_back(tmp);
    }
    while (i < nums.size() - 1 && nums[i] == nums[i + 1])
      i++;
  }
  return res;
}
TEST(fun, threeSum) {
  vector<int> data({-1, 0, 1, 2, -1, -4});
  vector<vector<int>> res({{-1, 2, -1}, {0, 1, -1}});
  EXPECT_EQ(res, threeSum(data));
}

vector<vector<int>> nSum(vector<int> &nums, int n, int start, int target) {
  int sz = nums.size();
  vector<vector<int>> res;
  if (n < 2 || sz < n)
    return res;
  if (n == 2) {
    int l = start, r = sz - 1;
    while (l < r) {
      int left = nums[l], right = nums[r];
      int sum = left + right;
      if (sum == target) {
        res.push_back({left, right});
        while (l < r && nums[l] == left)
          l++;
        while (l < r && nums[r] == right)
          r--;
      } else if (sum > target) {
        while (l < r && nums[r] == right)
          r--;
      } else {
        while (l < r && nums[l] == left)
          l++;
      }
    }
  } else {
    for (int i = start; i < sz; i++) {
      auto two = nSum(nums, n - 1, i + 1, target - nums[i]);
      for (auto &tmp : two) {
        tmp.push_back(nums[i]);
        res.push_back(tmp);
      }
      while (i < sz - 1 && nums[i] == nums[i + 1])
        i++;
    }
  }
  return res;
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
