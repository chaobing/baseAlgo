#include "conv.hpp"

template <typename DType>
Conv<DType>::Conv(const FMap_t *fmap_i, const FMap_t *fmap_w,
                  const FMap_t *fmap_b, const Pad_t *pad,
                  const Stride_t *stride, DType *din, DType *weights,
                  DType *bias) {
  fmap_i_ = *fmap_i;
  fmap_w_ = *fmap_w;
  fmap_b_ = *fmap_b;
  pad_ = *pad;
  stride_ = *stride;
  infer_ofm_shape();
  thread_num_ = CPU_NUM;
  thread_workload_ = ceil((float)fmap_o_.size() / thread_num_);
  data_in_ptr_ = din;
  weights_ptr_ = weights;
  bias_ptr_ = bias;
}

template <typename DType> void Conv<DType>::infer_ofm_shape() {
  kernel_.h = fmap_w_.h;
  kernel_.w = fmap_w_.w;
  int dst_h = 0;
  int dst_w = 0;
  if (pad_.mode == PadAttr::PadMode_FLOOR) {
    dst_h = std::floor(1.0 *
                       (fmap_i_.h + pad_.t + pad_.b -
                        ((kernel_.h - 1) * dilation_.h + 1) + stride_.h) /
                       stride_.h);
    dst_w = std::floor(1.0 *
                       (fmap_i_.w + pad_.l + pad_.r -
                        ((kernel_.w - 1) * dilation_.w + 1) + stride_.w) /
                       stride_.w);
  } else {
    cout << "not supported pad mode" << endl;
    abort();
  }

  fmap_o_.n = fmap_i_.n;
  fmap_o_.h = dst_h;
  fmap_o_.w = dst_w;
  fmap_o_.c = fmap_w_.c;
  psum_.resize(fmap_o_.size());
  data_out_.resize(fmap_o_.size());
}

template <typename DType> string Conv<DType>::param_str() {
  string ret;
  ret += fmap_i_.to_string("fmap_i");
  ret += fmap_w_.to_string("fmap_w");
  ret += fmap_b_.to_string("fmap_b");
  ret += fmap_o_.to_string("fmap_o");
  ret += pad_.to_string("pad");
  ret += kernel_.to_string("kernel");
  ret += stride_.to_string("stride");
  ret += dilation_.to_string("dilation");
  ret += "ops: " + std::to_string(get_workload()) + "\n";
  ret += "thread_num: " + std::to_string(thread_num_) + "\n";
  ret += "thread_workload_: " + std::to_string(thread_workload_) + "\n";
  return ret;
}
template <typename DType> uint64_t Conv<DType>::get_workload() {
  uint64_t ops = 0;
  ops = 2 * fmap_i_.c * kernel_.h * kernel_.w * fmap_o_.c;
  ops *= fmap_o_.h * fmap_o_.w;
  return ops;
}

template <typename DType> void Conv<DType>::run(int mode) {
  cout << "[INFO]: start to do conv" << endl;
  conv(mode);
  cout << "[INFO]: start to add bias" << endl;
  bias();
  cout << "[INFO]: start to do round" << endl;
  round();
}

template <typename DType> void Conv<DType>::get_out(DType *output) {
  output = data_out_.data();
}

template <typename DType> void Conv<DType>::conv(int mode) {
  if (mode == 1)
    conv_normal_thread();
  else
    conv_normal();
}
template <typename DType> void Conv<DType>::conv_normal() {
  for (auto n = 0; n < fmap_o_.n; n++) {
    for (auto h = 0; h < fmap_o_.h; h++) {
      for (auto w = 0; w < fmap_o_.w; w++) {
        for (auto c = 0; c < fmap_o_.c; c++) {
          conv_one(n, h, w, c);
        }
      }
    }
  }
}
template <typename DType>
void Conv<DType>::conv_one(int idx_dn, int idx_dh, int idx_dw, int idx_dc) {
  auto rlt_addr = idx_dn * fmap_o_.nsize() + idx_dh * fmap_o_.hsize() +
                  idx_dw * fmap_o_.wsize() + idx_dc;
  assert(rlt_addr < psum_.size() && "psum addr over flow");
  psum_[rlt_addr] = 0;
  auto idx_src_h = idx_dh * stride_.h;
  auto idx_src_w = idx_dw * stride_.w;
  for (auto h = 0; h < kernel_.h; h++) {
    for (auto w = 0; w < kernel_.w; w++) {
      for (auto c = 0; c < fmap_i_.c; c++) {
        auto input_addr = idx_dn * fmap_i_.size() +
                          (idx_dh + h) * fmap_i_.hsize() +
                          (idx_dw + w) * fmap_i_.wsize() + c;
        assert(input_addr < fmap_i_.size() && "img addr over flow");
        auto weight_addr = idx_dc * fmap_w_.nsize() + h * fmap_w_.hsize() +
                           w * fmap_w_.wsize() + c;
        assert(weight_addr < fmap_w_.size() && "weight_addr addr over flow");
        psum_[rlt_addr] += data_in_ptr_[input_addr] * weights_ptr_[weight_addr];
      }
    }
  }
}
template <typename DType> void Conv<DType>::conv_normal_thread() {
  vector<std::future<int>> thd_fut(thread_num_);
  for (auto i = 0U; i < thread_num_; i++) {
    thd_fut[i] = std::async(
        std::launch::async,
        [this](decltype(i) i) {
          auto base_pos = i * thread_workload_;
          auto fmap_size = fmap_o_.size();
          for (auto j = 0U; j < thread_workload_; j++) {
            int pos = base_pos + j;
            if (pos >= fmap_size)
              break;
            auto fmap = fmap_o_.pos2idx(pos);
            conv_one(fmap.n, fmap.h, fmap.w, fmap.c);
          }
          return 0;
        },
        i);
  }
  for (auto i = 0U; i < thread_num_; i++) {
    thd_fut[i].wait();
  }
}
template <typename DType> void Conv<DType>::bias() {
  for (auto i = 0; i < fmap_o_.size(); i++) {
    auto bias_addr = i % fmap_o_.c;
    psum_[i] += bias_ptr_[i];
  }
}
template <typename DType> void Conv<DType>::round() {
  for (auto i = 0; i < fmap_o_.size(); i++) {
    float tmp = psum_[i];
    data_out_[i] = static_cast<DType>(std::round(tmp));
  }
}

template class Conv<char>;
