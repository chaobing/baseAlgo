#include "../leetcommon.hpp"

vector<string> res;
string track;
void backtrace(int l, int r);
vector<string> generateParenthesis(int n) {
  backtrace(n, n);
  return res;
}
void backtrace(int l, int r) {
  if (l < 0 || r < 0)
    return;
  if (l > r)
    return;
  if (l == 0 && r == 0) {
    res.push_back(track);
    return;
  }
  track.push_back('(');
  backtrace(l - 1, r);
  track.pop_back();
  track.push_back(')');
  backtrace(l, r - 1);
  track.pop_back();
}

TEST(fun, generateParenthesis) {
  vector<string> res({"((()))", "(()())", "(())()", "()(())", "()()()"});
  EXPECT_EQ(res, generateParenthesis(3));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
