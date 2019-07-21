#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cassert>
#include <cmath>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <array>
#include <queue>
#include <deque>
#include <vector>
#include <map>
#include <bitset>
#include <unordered_map>

#include <iomanip>
#include <thread>
#include <mutex>
#include <memory>
#include <utility>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <limits>

#include <glog/logging.h>

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::pair;
using std::map;
using std::string;
using std::array;
using std::deque;
using std::vector;
using std::bitset;
using std::thread;
using std::mutex;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;

using std::stoi;
using std::stoul;
using std::stof;
using std::to_string;

using std::oct;
using std::dec;
using std::hex;
using std::left;
using std::setw;
using std::setfill;

#endif /* __COMMON_HPP__ */
