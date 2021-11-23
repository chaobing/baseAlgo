#include "../leetcommon.hpp"
bool isDig(char ch) { return ch >= '0' && ch <= '9'; }
bool isSign(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    return true;
  else
    return false;
}
int calculate(string s) {
  stack<int> stk;
  int num = 0;
  char sign = '+';
  int i = 0;
  while (i < s.size()) {
    char ch = s[i];
    if (isDig(ch)) {
      num = num * 10 + (ch - '0');
    }
    if ((ch != ' ' && !isDig(ch)) || i == (s.size() - 1)) {
      if (sign == '+')
        stk.push(num);
      else if (sign == '-')
        stk.push(-num);
      else if (sign == '*') {
        int pre = stk.top();
        stk.pop();
        stk.push(pre * num);
      } else if (sign == '/') {
        int pre = stk.top();
        stk.pop();
        stk.push(pre / num);
      }
      num = 0;
      sign = ch;
    }
    i++;
  }
  int res = 0;
  while (!stk.empty()) {
    res += stk.top();
    stk.pop();
  }
  return res;
}
TEST(fun, calculate) {
  string in = " 3+5 / 2 ";
  EXPECT_EQ(5, calculate(in));
}

int calculate2(string &s) {
  stack<int> stk;
  int num = 0;
  char sign = '+';
  while (s.size() > 0) {
    char ch = s[0];
    s.erase(s.begin());
    if (isDig(ch)) {
      num = num * 10 + (ch - '0');
    }
    if (ch == '(')
      num = calculate2(s);
    if ((ch != ' ' && !isDig(ch)) || s.size() == 0) {
      if (sign == '+')
        stk.push(num);
      else if (sign == '-')
        stk.push(-num);
      else if (sign == '*') {
        int pre = stk.top();
        stk.pop();
        stk.push(pre * num);
      } else if (sign == '/') {
        int pre = stk.top();
        stk.pop();
        stk.push(pre / num);
      }
      num = 0;
      sign = ch;
    }
    if (ch == ')')
      break;
  }
  int res = 0;
  while (!stk.empty()) {
    res += stk.top();
    stk.pop();
  }
  return res;
}
TEST(fun, calculate2) {
  string in = "(1+(4+5+2)-3)+(6+8)";
  EXPECT_EQ(23, calculate2(in));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
