#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#include <gtest/gtest.h>

#define PRINT_ARR(prefix, arr)                                                 \
  do {                                                                         \
    cout << prefix << ": " << endl;                                            \
    for (auto a : arr)                                                         \
      cout << a << " ";                                                        \
    cout << endl;                                                              \
  } while (0);

string minWinSubStr(const string &s, const string &t) {
  unordered_map<char, int> needs;
  unordered_map<char, int> wnd;
  for (auto c : t) {
    needs[c]++;
  }
  int l = 0, r = 0;
  int valid = 0;
  int minL = s.size() + 1, start = 0;
  while (r < s.size()) {
    char ch0 = s[r];
    r++;
    if (needs.count(ch0)) {
      wnd[ch0]++;
      if (wnd[ch0] == needs[ch0])
        valid++;
    }
    while (valid == needs.size()) {
      if (r - l < minL) {
        start = l;
        minL = r - l;
      }
      char ch1 = s[l];
      l++;
      if (needs.count(ch1)) {
        if (needs[ch1] == wnd[ch1]) {
          valid--;
        }
        wnd[ch1]--;
      }
    }
  }
  return minL == s.size() + 1 ? "" : s.substr(start, minL);
}
TEST(sliding_window, minWinSubStr) {
  string S = "ADOBECODEBANC";
  string T = "ABC";
  EXPECT_EQ("BANC", minWinSubStr(S, T));
}

bool permuteInStr(const string &t, const string &s) {
  unordered_map<char, int> needs;
  unordered_map<char, int> wnd;
  for (auto c : t) {
    needs[c]++;
  }
  int l = 0, r = 0;
  int valid = 0;
  while (r < s.size()) {
    char ch0 = s[r];
    r++;
    if (needs.count(ch0)) {
      wnd[ch0]++;
      if (wnd[ch0] == needs[ch0])
        valid++;
    }
    while (r - l >= t.size()) {
      if (valid == needs.size()) {
        return true;
      }
      char ch1 = s[l];
      l++;
      if (needs.count(ch1)) {
        if (needs[ch1] == wnd[ch1]) {
          valid--;
        }
        wnd[ch1]--;
      }
    }
  }
  return false;
}
TEST(sliding_window, permuteInStr) {
  string s1 = "ba";
  string s2 = "eidbaooo";
  EXPECT_EQ(true, permuteInStr(s1, s2));
  EXPECT_EQ(false, permuteInStr("da", s2));
}

vector<int> findAllAnagramInStr(const string &s, const string &p) {
  unordered_map<char, int> needs, wnd;
  vector<int> res;
  for (auto c : p) {
    needs[c]++;
  }
  int l = 0, r = 0;
  int valid = 0;
  while (r < s.size()) {
    char ch0 = s[r];
    r++;
    if (needs.count(ch0)) {
      wnd[ch0]++;
      if (wnd[ch0] == needs[ch0])
        valid++;
    }
    while (r - l >= p.size()) {
      if (valid == needs.size()) {
        res.push_back(l);
      }
      char ch1 = s[l];
      l++;
      if (needs.count(ch1)) {
        if (needs[ch1] == wnd[ch1]) {
          valid--;
        }
        wnd[ch1]--;
      }
    }
  }
  return res;
}
TEST(sliding_window, findAllAnagramInStr) {
  string s1 = "bacebabacd";
  string s2 = "abc";
  vector<int> res = {0, 6};
  EXPECT_EQ(res, findAllAnagramInStr(s1, s2));
}

int lengthOfLongestSubstring(const string &s) {
  unordered_map<char, int> wnd;
  int l = 0, r = 0;
  int maxL = 0;
  while (r < s.size()) {
    char ch0 = s[r];
    r++;
    wnd[ch0]++;
    while (wnd[ch0] > 1) {
      char ch1 = s[l];
      l++;
      wnd[ch1]--;
    }
    maxL = std::max(maxL, r - l);
  }
  return maxL;
}
TEST(sliding_window, lengthOfLongestSubstring) {
  string s1 = "bacebabacd";
  EXPECT_EQ(4, lengthOfLongestSubstring(s1));
}
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
