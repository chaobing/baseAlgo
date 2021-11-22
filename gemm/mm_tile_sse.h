#include <stdio.h>

#include <emmintrin.h> // SSE3
#include <mmintrin.h>
#include <pmmintrin.h> // SSE2
#include <xmmintrin.h> // SSE

typedef union {
  __m128 v;
  float d[4];
} v2df_t;

void AddDot4x4(int k, float *a, int lda, float *b, int ldb, float *c, int ldc) {
  float *a_0p_pntr, *a_1p_pntr, *a_2p_pntr, *a_3p_pntr;

  a_0p_pntr = &A(0, 0);
  a_1p_pntr = &A(1, 0);
  a_2p_pntr = &A(2, 0);
  a_3p_pntr = &A(3, 0);

  v2df_t c_p0_sum;
  v2df_t c_p1_sum;
  v2df_t c_p2_sum;
  v2df_t c_p3_sum;
  v2df_t a_0p_reg, a_1p_reg, a_2p_reg, a_3p_reg, b_reg;

  c_p0_sum.v = _mm_setzero_ps();
  c_p1_sum.v = _mm_setzero_ps();
  c_p2_sum.v = _mm_setzero_ps();
  c_p3_sum.v = _mm_setzero_ps();
  a_0p_reg.v = _mm_setzero_ps();
  a_1p_reg.v = _mm_setzero_ps();
  a_2p_reg.v = _mm_setzero_ps();
  a_3p_reg.v = _mm_setzero_ps();

  for (int p = 0; p < k; ++p) {
    b_reg.v = _mm_load_ps((float *)&B(p, 0));

    a_0p_reg.v = _mm_set_ps1(*a_0p_pntr++);
    a_1p_reg.v = _mm_set_ps1(*a_1p_pntr++);
    a_2p_reg.v = _mm_set_ps1(*a_2p_pntr++);
    a_3p_reg.v = _mm_set_ps1(*a_3p_pntr++);

    c_p0_sum.v += b_reg.v * a_0p_reg.v;
    c_p1_sum.v += b_reg.v * a_1p_reg.v;
    c_p2_sum.v += b_reg.v * a_2p_reg.v;
    c_p3_sum.v += b_reg.v * a_3p_reg.v;
  }

  C(0, 0) += c_p0_sum.d[0];
  C(0, 1) += c_p0_sum.d[1];
  C(0, 2) += c_p0_sum.d[2];
  C(0, 3) += c_p0_sum.d[3];

  C(1, 0) += c_p1_sum.d[0];
  C(1, 1) += c_p1_sum.d[1];
  C(1, 2) += c_p1_sum.d[2];
  C(1, 3) += c_p1_sum.d[3];

  C(2, 0) += c_p2_sum.d[0];
  C(2, 1) += c_p2_sum.d[1];
  C(2, 2) += c_p2_sum.d[2];
  C(2, 3) += c_p2_sum.d[3];

  C(3, 0) += c_p3_sum.d[0];
  C(3, 1) += c_p3_sum.d[1];
  C(3, 2) += c_p3_sum.d[2];
  C(3, 3) += c_p3_sum.d[3];
}

void mm_tile_sse(int m, int n, int k, float *a, int lda, float *b, int ldb,
                 float *c, int ldc) {
  int i, j;

  for (j = 0; j < n; j += 4) {
    for (i = 0; i < m; i += 4) {
      AddDot4x4(k, &A(i, 0), lda, &B(0, j), ldb, &C(i, j), ldc);
    }
  }
}
