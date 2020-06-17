#include"BaseAlgo.hpp"

void BaseAlgo::swap(int &a,int &b){
     int tmp = a;
     a = b;
     b = tmp;
}

void BaseAlgo::bubble(vector<int> &src) {
	bool swapped = true;
    while(swapped){
     	swapped = false;
		for(auto i = 1; i<src.size(); i++){
			if(src[i] < src[i-1]){
				swap(src[i],src[i-1]);
				swapped = true;
			}
		}  
    }   
}
  
void BaseAlgo::QuickSort(vector<int> &src, int low, int high){
	if(low >= high) return;
	int left=low, right=high, pivotVal=src[low];
	while(left<right){
		while(left<right && src[right] >= pivotVal){
			right--;
		}
		while(left<right && src[left] <= pivotVal){
			left++;
		}
		swap(src[left], src[right]);
	}
	swap(src[low], src[right]);
		
	BaseAlgo::QuickSort(src, low, right-1);
	BaseAlgo::QuickSort(src, right+1, high);
}
