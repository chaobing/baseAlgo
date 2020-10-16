#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

class KMP {
public:
  KMP(const string &p) : pat_(p) { buildTable(); };
  ~KMP(){};
  int search(const string &t) {
    int fstate = pat_.size();
    int cur = 0;
    for (int i = 0; i < t.size(); i++) {
      cur = table_[cur][t[i]];
      if (cur == fstate) {
        return i - fstate + 1;
      }
    }
    return -1;
  }

private:
  void buildTable() {
    table_.resize(pat_.size());
    for (auto &st : table_)
      st.resize(256);
    int X = 0;
    for (int i = 0; i < pat_.size(); i++) {
      for (int j = 0; j < 256; j++) {
        table_[i][j] = table_[X][j];
      }
      table_[i][pat_[i]] = i + 1;
      X = table_[X][pat_[i]];
    }
  }

private:
  string pat_;
  vector<vector<int>> table_;
};

TEST(fun, isMatch) {
  string s = "ABCDABD";
  string t = "ABD";
  KMP kmp(t);
  EXPECT_EQ(4, kmp.search(s));
  EXPECT_EQ(-1, kmp.search("ABCD"));
  EXPECT_EQ(1, kmp.search("MABDO"));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
