#include "../leetcommon.hpp"

using ELEM = pair<int, int>; // num-freq;
class MinHeap {
public:
  MinHeap() {}
  ~MinHeap() {}
  ELEM top() { return data_[0]; }
  int size() { return data_.size(); }
  void push(ELEM e) {
    data_.push_back(e);
    swimUp(data_.size() - 1);
  }
  void pop() {
    if (data_.empty())
      return;
    swap(data_[0], data_.back());
    data_.pop_back();
    sinkDown(0);
  }

private:
  void swimUp(int i) {
    int pi = (i - 1) >> 1;
    while (i && data_[i].second < data_[pi].second) {
      swap(data_[i], data_[pi]);
      i = pi;
      pi = (i - 1) >> 1;
    }
  }
  void sinkDown(int i) {
    int ci = i * 2 + 1;
    while (ci < data_.size()) {
      if (ci + 1 < data_.size() && data_[ci + 1].second < data_[ci].second)
        ci++;
      if (data_[i].second > data_[ci].second) {
        swap(data_[i], data_[ci]);
        i = ci;
        ci = i * 2 + 1;
      } else {
        break;
      }
    }
  }
  vector<ELEM> data_;
};

vector<int> topKFrequent(vector<int> &nums, int k) {
  unordered_map<int, int> freq;
  for (auto n : nums) {
    freq[n]++;
  }
  MinHeap Q;
  for (auto &it : freq) {
    Q.push({it.first, it.second});
    if (Q.size() > k) {
      Q.pop();
    }
  }
  vector<int> res;
  while (Q.size()) {
    res.push_back(Q.top().first);
    Q.pop();
  }
  return res;
}

TEST(fun, topKFrequent) {
  vector<int> nums({1, 1, 1, 2, 2, 3});
  vector<int> res({2, 1});
  EXPECT_EQ(res, topKFrequent(nums, 2));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
