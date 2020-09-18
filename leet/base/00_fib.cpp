#include <iostream>
using namespace std;
#include <gtest/gtest.h>

int fib(int n) {
  if (n == 1 || n == 2)
    return 1;
  int dp_0 = 1, dp_1 = 1;
  for (int i = 3; i <= n; i++) {
    int sum = dp_0 + dp_1;
    dp_0 = dp_1;
    dp_1 = sum;
  }
  return dp_1;
}

TEST(fun, fib) {
  EXPECT_EQ(1, fib(1));
  EXPECT_EQ(1, fib(2));
  EXPECT_EQ(2, fib(3));
  EXPECT_EQ(55, fib(10));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
