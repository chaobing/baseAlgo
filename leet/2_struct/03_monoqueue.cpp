#include "../leetcommon.hpp"

class MonoQ {
public:
  int max() { return Q.front(); }
  void push(int n) {
    while (!Q.empty() && Q.back() < n)
      Q.pop_back();
    Q.push_back(n);
  }
  void pop(int n) {
    if (!Q.empty() && n == Q.front())
      Q.pop_front();
  }

private:
  deque<int> Q;
};

vector<int> maxSlidingWindow(vector<int> &nums, int k) {
  MonoQ Q;
  vector<int> res;
  for (int i = 0; i < nums.size(); i++) {
    Q.push(nums[i]);
    if (i >= k - 1) {
      res.push_back(Q.max());
      Q.pop(nums[i - k + 1]);
    }
  }
  return res;
}

TEST(fun, maxSlidingWindow) {
  vector<int> nums({1, 3, -1, -3, 5, 3, 6, 7});
  vector<int> res({3, 3, 5, 5, 6, 7});
  EXPECT_EQ(res, maxSlidingWindow(nums, 3));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
