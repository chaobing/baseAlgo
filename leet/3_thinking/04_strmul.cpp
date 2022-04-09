#include "../leetcommon.hpp"

string strmul(const string &n1, const string &n2) {
  if (n1.empty() || n2.empty())
    return "";
  if (n1.compare("0") == 0 || n2.compare("0") == 0)
    return "0";
  if (n1.compare("1") == 0)
    return n2;
  if (n2.compare("1") == 0)
    return n1;
  size_t l1 = n1.size(), l2 = n2.size();
  vector<int> res(l1 + l2, 0);
  for (int i = l1 - 1; i >= 0; i--) {
    for (int j = l2 - 1; j >= 0; j--) {
      // cout << "[" << i << ", " << j << "]" << endl;
      int p2 = i + j + 1;
      int p1 = i + j;
      int cur = (n1[i] - '0') * (n2[j] - '0');
      cur += res[p2];
      res[p2] = cur % 10;
      res[p1] += cur / 10;
    }
  }
  size_t i = 0;
  while (i < res.size() && res[i] == 0)
    i++;
  string str;
  for (; i < res.size(); i++)
    str.push_back('0' + res[i]);
  return str;
}

TEST(fun, strmul) {
  string n1 = "123", n2 = "456";
  EXPECT_EQ("56088", strmul(n1, n2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
