#include "../leetcommon.hpp"

int countPrimes(int n) {
  if (n < 2)
    return 0;
  vector<bool> isP(n, true);
  isP[0] = false;
  isP[1] = false;
  for (int i = 2; i * i < n; ++i) {
    if (isP[i]) {
      for (int j = i * i; j < n; j += i)
        isP[j] = false;
    }
  }
  int res = 0;
  for (auto p : isP) {
    res += p ? 1 : 0;
  }
  return res;
}
TEST(fun, countPrimes) {
  // 2, 3, 5, 7
  EXPECT_EQ(4, countPrimes(10));
}

double myPow2(double x, uint32_t n) {
  if (n == 0)
    return 1;
  if (n == 1)
    return x;
  double half = myPow2(x, n >> 1);
  half *= half;
  if (n & 1)
    half *= x;
  return half;
}

double myPow(double x, int n) {
  if (n == 0)
    return 1;
  uint32_t an = abs(n);
  if (n < 0)
    return 1 / myPow2(x, an);
  return myPow2(x, an);
}

TEST(fun, myPow) {
  // 2, 3, 5, 7
  EXPECT_EQ(true, isSame(1024, myPow(2, 10)));
  EXPECT_EQ(true, isSame(9.2610, myPow(2.10000, 3)));
  EXPECT_EQ(true, isSame(0.25, myPow(2, -2)));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
