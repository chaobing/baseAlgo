#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

string plusOne(const string &ori, int i) {
  string ret = ori;
  if (ret[i] == '9')
    ret[i] = '0';
  else
    ret[i] += 1;
  return ret;
}
string minusOne(const string &ori, int i) {
  string ret = ori;
  if (ret[i] == '0')
    ret[i] = '9';
  else
    ret[i] -= 1;
  return ret;
}
int openLock(const vector<string> &deadends, const string &target) {
  set<string> deads;
  for (auto s : deadends)
    deads.insert(s);
  set<string> visited;
  queue<string> Q;
  visited.insert("0000");
  Q.push("0000");
  int step = 0;
  while (!Q.empty()) {
    int sz = Q.size();
    for (int i = 0; i < sz; i++) {
      string cur = Q.front();
      Q.pop();
      if (deads.count(cur))
        continue;
      if (cur == target)
        return step;
      for (int j = 0; j < 4; j++) {
        string up = plusOne(cur, j);
        if (!visited.count(up)) {
          Q.push(up);
          visited.insert(up);
        }
        string down = minusOne(cur, j);
        if (!visited.count(down)) {
          Q.push(down);
          visited.insert(down);
        }
      }
    }
    step++;
  }
  return -1;
}
TEST(bfs, openLock) {
  vector<string> deadends = {"8888"};
  string target = "0008";
  EXPECT_EQ(1, openLock(deadends, target));

  deadends = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
  target = "8888";
  EXPECT_EQ(-1, openLock(deadends, target));

  deadends = {"0201", "0101", "0102", "1212", "2002"};
  target = "0202";
  EXPECT_EQ(6, openLock(deadends, target));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
