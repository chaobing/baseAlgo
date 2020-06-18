#pragma once

#include "common.hpp"

struct FMapAttr;
using fmap_coord_t = FMapAttr;

typedef struct FMapAttr{
  int n;
  int h;
  int w;
  int c;
  FMapAttr() : n(0), h(0), w(0), c(0) {}
  FMapAttr(int nval, int hval, int wval, int cval)
      : n(nval), h(hval), w(wval), c(cval) {}

  int size() const { return n * h * w * c; }
  int nsize() const { return h * w * c; }
  int hsize() const { return w * c; }
  int wsize() const { return c; }
  int csize() const { return 1; }

  inline int idx2pos(const fmap_coord_t &coord) const {
    int pos = 0;
    pos += coord.n * nsize();
    pos += coord.h * hsize();
    pos += coord.w * wsize();
    pos += coord.c * csize();
    return pos;
  }
  inline fmap_coord_t pos2idx(int pos) const {
    fmap_coord_t coord;
    coord.n = pos / nsize();
    coord.h = (pos % nsize()) / hsize();
    coord.w = ((pos % nsize()) % hsize()) / wsize();
    coord.c = (((pos % nsize()) % hsize()) % wsize()) / csize();
    return coord;
  }

  string to_string(const string &prefix = "fmap") const {
    string ret = prefix + ": [";
    ret += "n: " + std::to_string(n);
    ret += ", h: " + std::to_string(h);
    ret += ", w: " + std::to_string(w);
    ret += ", c: " + std::to_string(c);
    ret += "]\n";
    return ret;
  }
} FMap_t;

typedef struct StrideAttr {
  int h;
  int w;
  StrideAttr() : h(1), w(1) {}
  StrideAttr(int hval, int wval) : h(hval), w(wval) {}
  string to_string(const string &prefix = "stride") {
    string ret = prefix + ": [";
    ret += "h: " + std::to_string(h);
    ret += ", w: " + std::to_string(w);
    ret += "]\n";
    return ret;
  }
} Stride_t;

typedef struct PadAttr {
  enum {
    PadMode_FLOOR,
    PadMode_CEIL,
    PadMode_SAME,
    PadMode_VALID,
  };
  int mode;
  int l;
  int r;
  int b;
  int t;
  PadAttr() : mode(PadMode_FLOOR), l(0), r(0), b(0), t(0) {}
  PadAttr(int mval, int lval, int tval, int rval, int bval)
      : mode(mval), l(lval), t(tval), r(rval), b(bval) {}
  string to_string(const string &prefix = "pad") {
    string ret = prefix + ": [";
    ret += "mode: " + std::to_string(mode);
    ret += ", left: " + std::to_string(l);
    ret += ", top: " + std::to_string(t);
    ret += ", right: " + std::to_string(r);
    ret += ", bottom: " + std::to_string(b);
    ret += "]\n";
    return ret;
  }
} Pad_t;
