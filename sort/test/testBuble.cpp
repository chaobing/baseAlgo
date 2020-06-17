
#include "Util.hpp"
#include "BaseAlgo.hpp"
int main(){
   vector<int> vec(10,0);
   Util::Random(vec.data(), 10, 0, 10, 1);
   string vStr = Util::Vector2String(vec.data(), vec.size());
   cout << "vector random init:\n" << vStr << endl;
   BaseAlgo::bubble(vec);
   vStr = Util::Vector2String(vec.data(), vec.size());
   cout << "vector sorted:\n" << vStr << endl;
   
   return 0;
}
