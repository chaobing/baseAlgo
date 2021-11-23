#include "../leetcommon.hpp"

static const int NaN = 0xffffffff;

TreeNode *buildBST(vector<int> &data) {
  if (data.empty())
    return nullptr;
  vector<TreeNode *> Q;
  for (int i = 0; i < data.size(); ++i) {
    if (data[i] == NaN) {
      Q.push_back(nullptr);
    } else {
      Q.push_back(new TreeNode(data[i]));
    }
  }
  int idx = 1;
  for (int i = 0; i < Q.size(); i++) {
    if (!Q[i])
      continue;
    if (idx < Q.size()) {
      Q[i]->left = Q[idx++];
    }
    if (idx < Q.size()) {
      Q[i]->right = Q[idx++];
    }
  }
  return Q[0];
}

string to_string(TreeNode *root) {
  if (!root)
    return "";
  queue<TreeNode *> Q;
  Q.push(root);
  ostringstream ss;
  while (!Q.empty()) {
    int sz = Q.size();
    while (sz--) {
      TreeNode *node = Q.front();
      Q.pop();
      if (node) {
        ss << to_string(node->val) + " ";
        Q.push(node->left);
        Q.push(node->right);
      } else {
        ss << "null ";
      }
    }
  }
  return ss.str();
}

int *rval = nullptr;
bool isValidBST(TreeNode *root) {
  if (!root)
    return true;
  if (!isValidBST(root->left))
    return false;
  if (rval && *rval >= root->val)
    return false;
  rval = &(root->val);
  return isValidBST(root->right);
}
TEST(fun, isValidBST) {
  //              5
  //             / \
  //            1   4
  //               /  \
  //              3    6
  vector<int> data({5, 1, 4, NaN, 3, 6});
  TreeNode *root = buildBST(data);
  cout << to_string(root) << endl;
  EXPECT_EQ(false, isValidBST(root));
}
//////////////////////
// from root to leaf
bool hasPathSum(TreeNode *root, int sum) {
  if (!root)
    return false;
  sum -= root->val;
  if (!root->left && !root->right)
    return sum == 0;
  return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}
TEST(fun, hasPathSum) {
  //              1
  //             / \
  //            2   3
  vector<int> data({1, 2, 3});
  TreeNode *root = buildBST(data);
  cout << to_string(root) << endl;
  EXPECT_EQ(false, hasPathSum(root, 5));
}

//////////////////////
// from node to node
int res = 0;
void dfs(TreeNode *root, int sum) {
  if (!root)
    return;
  sum -= root->val;
  if (sum == 0)
    res++;
  dfs(root->left, sum);
  dfs(root->right, sum);
  sum += root->val;
}
int pathSum(TreeNode *root, int sum) {
  if (!root)
    return 0;
  dfs(root, sum);
  pathSum(root->left, sum);
  pathSum(root->right, sum);
  return res;
}
TEST(fun, pathSum) {
  //                10
  //               /  \
  //              5    -3
  //             / \     \
  //            3   2     11
  //           / \    \
  //          3  -2    1
  vector<int> data({10, 5, -3, 3, 2, NaN, 11, 3, -2, NaN, 1});
  TreeNode *root = buildBST(data);
  cout << to_string(root) << endl;
  EXPECT_EQ(3, pathSum(root, 8));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
