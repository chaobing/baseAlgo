#include "../leetcommon.hpp"

/////////////////////////////////////////////////////////////////////////////
// Given n non-negative integers representing an elevation map where the width
// of each bar is 1, compute how much water it can trap after raining.
int trap(vector<int> &heights) {
  int n = heights.size();
  int l = 0, r = n - 1;
  int lm = heights[l], rm = heights[r];
  int res = 0;
  while (l < r) {
    lm = max(lm, heights[l]);
    rm = max(rm, heights[r]);
    if (lm < rm) {
      res += lm - heights[l];
      l++;
    } else {
      res += rm - heights[r];
      r--;
    }
  }
  return res;
}
TEST(fun, trap) {
  vector<int> data({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
  EXPECT_EQ(6, trap(data));
}

/////////////////////////////////////////////////////////////////////////////
// Given an array of integers heights representing the histogram's bar height
// where the width of each bar is 1, return the area of the largest rectangle in
// the histogram.
int largestRectangleArea(vector<int> &heights) {
  heights.push_back(0);
  stack<int> stk;
  int res = 0;
  for (int i = 0; i < heights.size(); i++) {
    while (!stk.empty() && heights[stk.top()] > heights[i]) {
      int ti = stk.top();
      stk.pop();
      res = max(res, heights[ti] * (stk.empty() ? i : (i - stk.top() - 1)));
    }
    stk.push(i);
  }
  heights.pop_back();
  return res;
}
TEST(fun, largestRectangleArea) {
  vector<int> data({2, 1, 5, 6, 2, 3});
  EXPECT_EQ(10, largestRectangleArea(data));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
