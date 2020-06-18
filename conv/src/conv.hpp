#pragma once

#include "Util.hpp"
#include "common.hpp"
#include "data_type.hpp"

template <typename DType> class Conv {
public:
  Conv(const FMap_t *fmap_i, const FMap_t *fmap_w, const FMap_t *fmap_b,
       const Pad_t *pad, const Stride_t *stride, DType *din, DType *weights,
       DType *bias);
  string param_str();
  void run(int mode);
  int ofm_size() const { return fmap_o_.size(); }
  void get_out(DType *output);
  uint64_t get_workload();

private:
  void infer_ofm_shape();

  void conv(int mode);
  void bias();
  void round();
  void conv_normal();
  void conv_normal_thread();

  void conv_one(int idx_dn, int idx_dh, int idx_dw, int idx_dc);

private:
  uint32_t thread_num_;
  uint32_t thread_workload_;

private:
  FMap_t fmap_i_;
  FMap_t fmap_w_;
  FMap_t fmap_b_;
  FMap_t fmap_o_;

  Pad_t pad_;
  Stride_t kernel_{1, 1};
  Stride_t stride_{1, 1};
  Stride_t dilation_{1, 1};
  bool has_bias_{true};

  DType *data_in_ptr_{nullptr};
  DType *weights_ptr_{nullptr};
  DType *bias_ptr_{nullptr};
  vector<DType> data_out_;
  vector<int32_t> psum_;
};
