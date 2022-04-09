#include "../leetcommon.hpp"
string subPalind(const string &str, int l, int r) {
  while (l < str.size() && r >= 0 && str[l] == str[r]) {
    l--;
    r++;
  }
  return str.substr(l + 1, r - l - 1);
}
string longestPalind(const string &str) {
  if (str.empty())
    return "";
  if (str.size() == 1)
    return str;
  string res;
  for (auto i = 0u; i < str.size(); i++) {
    string s1 = subPalind(str, i, i);
    if (s1.size() > res.size())
      res = s1;
    s1 = subPalind(str, i, i + 1);
    if (s1.size() > res.size())
      res = s1;
  }
  return res;
}

TEST(fun, longestPalind) {
  EXPECT_EQ("bab", longestPalind("babad"));
  EXPECT_EQ("bb", longestPalind("cbbd"));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
