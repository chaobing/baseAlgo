#ifndef __LEETCOMMOB_HPP__
#define __LEETCOMMOB_HPP__

#include <deque>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::max;
using std::ostringstream;
using std::pair;
using std::queue;
using std::set;
using std::stack;
using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#define PRINT_LIST(li)                                                         \
  do {                                                                         \
    while (li) {                                                               \
      cout << li->val << " ";                                                  \
      li = li->next;                                                           \
    }                                                                          \
  } while (0);

#define PRINT_ARR(prefix, arr)                                                 \
  do {                                                                         \
    cout << prefix << ": " << endl;                                            \
    for (auto a : arr)                                                         \
      cout << a << " ";                                                        \
    cout << endl;                                                              \
  } while (0);

#define PRINT_MAT(prefix, mat)                                                 \
  do {                                                                         \
    cout << prefix << ": " << endl;                                            \
    for (auto arr : mat) {                                                     \
      for (auto a : arr) {                                                     \
        cout << a << " ";                                                      \
      }                                                                        \
      cout << endl;                                                            \
    }                                                                          \
  } while (0);

#endif
