#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

bool isMatchRaw(const string &txt, const string &pat) {
  if (pat.size() == 0)
    return txt.size() == 0;
  bool first_match = (txt.size() > 0) && ((txt[0] == pat[0]) || pat[0] == '.');
  if (pat.size() >= 2 && pat[1] == '*') {
    return ((first_match && isMatchRaw(txt.substr(1), pat)) ||
            (isMatchRaw(txt, pat.substr(2))));
  } else {
    return first_match && isMatchRaw(txt.substr(1), pat.substr(1));
  }
}
unordered_map<string, bool> memo;
string s;
string p;
bool dp(int i, int j) {
  string key = to_string(i) + "_" + to_string(j);
  if (memo.count(key))
    return memo[key];
  if (j == p.size())
    return i == s.size();
  bool first_match = (i < s.size()) && (s[i] == p[j] || p[j] == '.');
  bool res;
  if (j <= p.size() - 2 && p[j + 1] == '*') {
    res = (first_match && dp(i + 1, j)) || dp(i, j + 2);
  } else {
    res = first_match && dp(i + 1, j + 1);
  }
  memo[key] = res;
  return res;
};
bool isMatch(const string &txt, const string &pat) {
  s = txt;
  p = pat;
  return dp(0, 0);
}

TEST(fun, isMatch) {
  string s = "aa";
  string t = "a*";
  EXPECT_EQ(true, isMatch(s, t));
  s = "aab";
  t = "c*a*b";
  EXPECT_EQ(true, isMatch(s, t));
  s = "ab";
  t = ".*";
  EXPECT_EQ(true, isMatch(s, t));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
