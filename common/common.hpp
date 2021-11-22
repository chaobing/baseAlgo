#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <cassert>
#include <cmath>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <bitset>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <algorithm>
#include <future>
#include <iomanip>
#include <limits>
#include <memory>
#include <mutex>
#include <random>
#include <stdexcept>
#include <thread>
#include <utility>

#include <glog/logging.h>

using std::array;
using std::bitset;
using std::cout;
using std::deque;
using std::endl;
using std::fstream;
using std::ifstream;
using std::make_shared;
using std::map;
using std::mutex;
using std::ofstream;
using std::pair;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::thread;
using std::vector;

using std::stof;
using std::stoi;
using std::stoul;
using std::to_string;

using std::dec;
using std::hex;
using std::left;
using std::oct;
using std::setfill;
using std::setw;

#endif /* __COMMON_HPP__ */
