#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include "common.hpp"


class Util {
private:
    Util() {}
    ~Util() {}

public:
    template <typename T>
    static T Random(T low, T high);
    template <typename T>
    static void Random(T* data, uint64_t size, T low, T high, uint64_t seed);
	template<typename T>
	static string Vector2String(T* data, uint64_t size);

// used to calculate time
public:
    // used to calculate time
    enum TimeType {
        TIME_S,
        TIME_MS,
        TIME_US,
    };
    static void TimeBegin(struct timeval &begin) { gettimeofday(&begin, 0); }
    static unsigned long TimeEnd(const struct timeval &begin, int type = TIME_MS) {
        struct timeval end;
        gettimeofday(&end, 0);
        if(type == TIME_S) {
            return (1000000*(end.tv_sec-begin.tv_sec) + (end.tv_usec-begin.tv_usec)) / 1000000;
        } else if(type == TIME_MS) {
            return (1000000*(end.tv_sec-begin.tv_sec) + (end.tv_usec-begin.tv_usec)) / 1000;
        } else {
            return (1000000*(end.tv_sec-begin.tv_sec) + (end.tv_usec-begin.tv_usec)) / 1;
        }
    }
};


template <typename T>
T Util::Random(T low, T high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(low, high);

    return dis(gen);
}

template <typename T>
void Util::Random(T* data, uint64_t size, T low, T high, uint64_t seed)
{
    std::random_device rd;
    std::mt19937 gen(seed);
    std::uniform_int_distribution<T> dis(low, high);

    for(auto i=0U; i<size; i++) {
        if(seed == 0)
            data[i] = 0;
        else
            data[i] = dis(gen);
    }
}
template<typename T>
string Util::Vector2String(T* data, uint64_t size){
	std::ostringstream ss;
	for(auto i=0U; i<size; i++){
		ss << data[i] << " ";
	}
	ss<<std::dec<<"\n";
	return ss.str();
}


#endif /*__UTIL_HPP__*/
