#ifndef __LEETCOMMOB_HPP__
#define __LEETCOMMOB_HPP__

#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::queue;
using std::set;
using std::string;
using std::vector;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
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
