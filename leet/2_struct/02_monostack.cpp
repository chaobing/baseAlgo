#include "../leetcommon.hpp"

vector<int> nextGreaterElement(vector<int> &nums) {
  vector<int> ans(nums.size());
  stack<int> s;
  for (int i = nums.size() - 1; i >= 0; i--) {
    while (!s.empty() && s.top() <= nums[i]) {
      s.pop();
    }
    ans[i] = s.empty() ? -1 : s.top();
    s.push(nums[i]);
  }
  return ans;
}

TEST(fun, nextGreaterElement) {
  vector<int> nums({2, 1, 2, 4, 3});
  vector<int> res({4, 2, 4, -1, -1});
  EXPECT_EQ(res, nextGreaterElement(nums));
}

vector<int> dailyTemperatures(vector<int> &T) {
  stack<int> stk;
  vector<int> res(T.size());
  for (int i = T.size() - 1; i >= 0; i--) {
    while (!stk.empty() && T[i] >= T[stk.top()]) {
      stk.pop();
    }
    res[i] = (stk.empty() ? 0 : stk.top() - i);
    stk.push(i);
  }
  return res;
}

TEST(fun, dailyTemperatures) {
  vector<int> nums({73, 74, 75, 71, 69, 72, 76, 73});
  vector<int> res({1, 1, 4, 2, 1, 1, 0, 0});
  EXPECT_EQ(res, dailyTemperatures(nums));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
