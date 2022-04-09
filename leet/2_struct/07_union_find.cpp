#include "../leetcommon.hpp"

///////////////////////////////////////////////////////////////////////////
// You are given an array of variable pairs equations and an array of real
// numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
// equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
// single variable.
// You are also given some queries, where queries[j] = [Cj, Dj] represents the
// jth query where you must find the answer for Cj / Dj = ?.
// Return the answers to all queries. If a single answer cannot be determined,
// return -1.0.
struct UFNode {
  double val;
  UFNode *par;
  UFNode(double v) : val(v), par(this) {}
};
unordered_map<string, UFNode *> dict;

UFNode *findP(UFNode *x) {
  while (x != x->par)
    x = x->par;
  return x;
}

void unionPQ(UFNode *p, UFNode *q, double v) {
  UFNode *ra = findP(p);
  UFNode *rb = findP(q);
  double s = v * q->val / p->val;
  for (auto &it : dict) {
    if (findP(it.second) == ra) {
      (it.second->val) *= s;
    }
  }
  ra->par = rb;
}

vector<double> calcEquation(vector<vector<string>> &equations,
                            vector<double> &values,
                            vector<vector<string>> &queries) {
  for (int i = 0; i < equations.size(); ++i) {
    string a = equations[i][0], b = equations[i][1];
    double v = values[i];
    if (dict.find(a) == dict.end())
      dict[a] = new UFNode(v);
    if (dict.find(b) == dict.end())
      dict[b] = new UFNode(1.0);
    unionPQ(dict[a], dict[b], v);
  }
  vector<double> res;
  for (auto &que : queries) {
    string a = que[0], b = que[1];
    if (dict.find(a) == dict.end() || dict.find(b) == dict.end())
      res.push_back(-1);
    else if (findP(dict[a]) != findP(dict[b]))
      res.push_back(-1);
    else
      res.push_back(dict[a]->val / dict[b]->val);
  }
  return res;
}

TEST(fun, calcEquation) {
  vector<vector<string>> equations({{"a", "b"}, {"b", "c"}, {"bc", "cd"}});
  vector<double> values({1.5, 2.5, 5.0});
  vector<vector<string>> queries({{"a", "c"},
                                  {"c", "b"},
                                  {"a", "cd"},
                                  {"bc", "cd"},
                                  {"cd", "bc"},
                                  {"x", "a"}});
  vector<double> res = calcEquation(equations, values, queries);
  vector<double> golden(
      {3.75000, 0.40000, -1.00000, 5.00000, 0.20000, -1.00000});
  for (int i = 0; i < res.size(); ++i) {
    EXPECT_EQ(true, isSame(res[i], golden[i]));
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
