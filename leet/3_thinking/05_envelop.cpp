#include "../leetcommon.hpp"

int LIS(const vector<int> &arr) {
  size_t sz = arr.size();
  if (sz < 2)
    return sz;
  vector<int> top(sz);
  int piles = 0;
  for (int i = 0; i < arr.size(); i++) {
    int p = arr[i];
    int l = 0, r = piles;
    while (l < r) {
      int m = l + (r - l) / 2;
      if (top[m] >= p)
        r = m;
      else
        l = m + 1;
    }
    if (l == piles)
      piles++;
    top[l] = p;
  }
  return piles;
}
int maxEnvelops(vector<vector<int>> &nums) {
  std::sort(nums.begin(), nums.end(),
            [](const vector<int> &a, const vector<int> &b) {
              return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
            });
  vector<int> width;
  for (auto &it : nums)
    width.push_back(it[1]);
  return LIS(width);
}

TEST(fun, maxEnvelops) {
  vector<vector<int>> data({{5, 4}, {6, 4}, {6, 7}, {2, 3}});
  EXPECT_EQ(3, maxEnvelops(data));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
