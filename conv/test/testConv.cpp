#include "Util.hpp"

int main(){
    struct timeval start;
    Util::TimeBegin(start);
    cout << "start time: " << start.tv_sec << endl;
    int i = (1 << 30);
    while (i >= 0) {
      i--;
    }
    unsigned long latency = Util::TimeEnd(start, Util::TIME_US);
    cout << "latency is " << latency << endl;
    return 0;
}
