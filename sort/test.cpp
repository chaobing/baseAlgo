#include "BaseAlgo.hpp"
#include <gtest/gtest.h>
#include <algorithm>

TEST(fun, testsort) {
  vector<int> data({1, 3, 7, 6, 9, 2, 7, 8});
  vector<int> golden(data);
  std::sort(golden.begin(), golden.end());

  vector<int> bs_data(data);
  BaseAlgo::bubble(bs_data);
  EXPECT_EQ(golden, bs_data);

  vector<int> qs_data = data;
  BaseAlgo::QuickSort(qs_data, 0, qs_data.size() - 1);
  EXPECT_EQ(golden, qs_data);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
