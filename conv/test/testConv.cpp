#include "Util.hpp"
#include "conv.hpp"
#include "data_type.hpp"

#define TMIN -128
#define TMAX 127
#define SEED 1

int main() {
  cout << "current CPU num: " << CPU_NUM << endl;
  FMap_t fmap_i(1, 224, 224, 3);
  FMap_t fmap_w(64, 7, 7, 3);
  FMap_t fmap_b(1, 1, 1, 3);
  Pad_t pad(0, 3, 3, 3, 3);
  Stride_t stride(2, 2);
  // size_t imgsize = fmap_i.n * (fmap_i.h + pad.b + pad.t) *
  //                 (fmap_i.w + pad.l + pad.r) * fmap_i.c;
  // vector<char> img(imgsize);
  vector<char> img(fmap_i.size());
  Util::Random<char>(img.data(), img.size(), TMIN, TMAX, SEED);
  vector<char> weights(fmap_w.size());
  Util::Random<char>(weights.data(), weights.size(), TMIN, TMAX, SEED);
  vector<char> bias(fmap_b.size());
  Util::Random<char>(bias.data(), bias.size(), TMIN, TMAX, SEED);
  Conv<char> tconv(&fmap_i, &fmap_w, &fmap_b, &pad, &stride, img.data(),
                   weights.data(), bias.data());
  cout << tconv.param_str() << endl;
  vector<char> out(tconv.ofm_size());

  struct timeval start;
  cout << "============= normal run ==============" << endl;
  Util::TimeBegin(start);
  cout << "start time: " << start.tv_sec << endl;
  tconv.run(0);
  unsigned long latency = Util::TimeEnd(start, Util::TIME_MS);
  cout << "latency is " << latency << " ms" << endl;
  tconv.get_out(out.data());

  cout << "============= thread run ==============" << endl;
  Util::TimeBegin(start);
  cout << "start time: " << start.tv_sec << endl;
  tconv.run(1);
  latency = Util::TimeEnd(start, Util::TIME_MS);
  cout << "latency is " << latency << " ms" << endl;
  vector<char> out2(tconv.ofm_size());
  tconv.get_out(out2.data());
  for (auto i = 0; i < out.size(); i++) {
    if (out[i] != out2[i])
      cout << "[diff] idx: " << i << ", normal: " << out[i]
           << ", thread: " << out2[i] << endl;
  }

  return 0;
}
