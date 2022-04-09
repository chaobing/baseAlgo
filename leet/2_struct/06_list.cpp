#include "../leetcommon.hpp"

ListNode *buildList(vector<int> &data) {
  if (data.empty())
    return nullptr;
  vector<ListNode *> Q;
  for (int i = 0; i < data.size(); i++) {
    Q.push_back(new ListNode(data[i]));
    if (i > 0)
      Q[i - 1]->next = Q[i];
  }
  return Q[0];
}

string to_string(ListNode *a) {
  if (!a)
    return "null";
  string str;
  while (a) {
    str += "->" + std::to_string(a->val);
    a = a->next;
  }
  str += "\n";
  return str;
}
bool isSame(ListNode *a, ListNode *b) {
  if (!a && !b)
    return true;
  if (!a && b)
    return false;
  if (a && !b)
    return false;
  if (a->val != b->val)
    return false;
  return isSame(a->next, b->next);
}

///////////////////////////////////////////
// reverse whole list
ListNode *reverseList(ListNode *head) {
  if (!head || !head->next)
    return head;
  ListNode *pre = nullptr, *cur = head, *nxt = nullptr;
  while (cur) {
    nxt = cur->next;
    cur->next = pre;
    pre = cur;
    cur = nxt;
  }
  return pre;
}
TEST(fun, reverseList) {
  vector<int> nums({1, 2, 3, 4, 5, 6});
  ListNode *ori = buildList(nums);
  cout << "ori " << to_string(ori);
  vector<int> res({6, 5, 4, 3, 2, 1});
  ListNode *golden = buildList(res);
  cout << "golden " << to_string(golden);
  EXPECT_EQ(true, isSame(golden, reverseList(ori)));
}

///////////////////////////////////////////
// reverse from m->n
ListNode *successor = nullptr;
ListNode *reverseN(ListNode *head, int n) {
  if (n == 1) {
    successor = head->next;
    return head;
  }
  ListNode *last = reverseN(head->next, n - 1);
  head->next->next = head;
  head->next = successor;
  return last;
}
ListNode *reverseBetween(ListNode *head, int m, int n) {
  if (m == 1)
    return reverseN(head, n);
  head->next = reverseBetween(head->next, m - 1, n - 1);
  return head;
}
TEST(fun, reverseBetween) {
  vector<int> nums({1, 2, 3, 4, 5});
  ListNode *ori = buildList(nums);
  cout << "ori " << to_string(ori);
  vector<int> res({1, 4, 3, 2, 5});
  ListNode *golden = buildList(res);
  cout << "golden " << to_string(golden);
  EXPECT_EQ(true, isSame(golden, reverseBetween(ori, 2, 4)));
}

///////////////////////////////////////////
// reverse each k-group
ListNode *reverse(ListNode *a, ListNode *b) {
  ListNode *pre = nullptr, *cur = a, *nxt = nullptr;
  while (cur != b) {
    nxt = cur->next;
    cur->next = pre;
    pre = cur;
    cur = nxt;
  }
  return pre;
}
ListNode *reverseKGroup(ListNode *head, int k) {
  if (!head)
    return head;
  ListNode *a = head, *b = head;
  for (int i = 0; i < k; ++i) {
    if (!b)
      return head;
    b = b->next;
  }
  ListNode *nHead = reverse(a, b);
  a->next = reverseKGroup(b, k);
  return nHead;
}
TEST(fun, reverseKGroup) {
  vector<int> nums({1, 2, 3, 4, 5});
  ListNode *ori = buildList(nums);
  cout << "ori " << to_string(ori);
  vector<int> res({2, 1, 4, 3, 5});
  ListNode *golden = buildList(res);
  cout << "golden " << to_string(golden);
  EXPECT_EQ(true, isSame(golden, reverseKGroup(ori, 2)));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
