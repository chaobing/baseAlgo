#pragma once
#include <iostream>
#include <vector>
using std::vector;

class BaseAlgo {
private:
  BaseAlgo(){};
  ~BaseAlgo(){};

public:
  static void swap(int &a, int &b);
  static void bubble(vector<int> &src);
  static void QuickSort(vector<int> &src, int low, int high);
};
