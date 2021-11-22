#include "../leetcommon.hpp"

ListNode *detectCycle(ListNode *head) {
  ListNode *fast = head;
  ListNode *slow = head;
  while (fast != nullptr && fast->next != nullptr) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow)
      break;
  }
  slow = head;
  while (slow != fast) {
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}
TEST(doublePointer, detectCycle) {
  ListNode *head = new ListNode(1);
  ListNode *tmp = head;
  const int LEN = 4;
  int values[LEN] = {2, 3, 4, 5};
  for (int i = 0; i < LEN; i++) {
    tmp->next = new ListNode(values[i]);
    tmp = tmp->next;
  }
  tmp->next = head->next;
  // PRINT_LIST(head);
  EXPECT_EQ(head->next, detectCycle(head));
}

vector<int> twoSum(const vector<int> &A, int tar) {
  int l = 0, r = A.size() - 1;
  while (l < r) {
    int sum = A[l] + A[r];
    if (sum == tar) {
      return {l, r};
    } else if (sum < tar) {
      l++;
    } else if (sum > tar) {
      r--;
    }
  }
  return {-1, -1};
}
TEST(doublePointer, twoSum) {
  vector<int> arr = {2, 7, 11, 15};
  vector<int> res = {0, 1};
  EXPECT_EQ(res, twoSum(arr, 9));
  res = {-1, -1};
  EXPECT_EQ(res, twoSum(arr, 19));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
