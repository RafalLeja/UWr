#include "md5.h"
#include <cstdint>

__constant__ __device__ uint32_t K_d[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
    0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
    0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

__constant__ __device__ uint32_t S_d[] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

__global__ void md5_iter_gpu(struct md5_state *state, const uint32_t *M) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  uint32_t a = state[idx].a;
  uint32_t b = state[idx].b;
  uint32_t c = state[idx].c;
  uint32_t d = state[idx].d;

  // TODO: Split the M?

  for (int i = 0; i < 64; i++) {
    uint32_t F, g;
    if (i < 16) {
      F = (b & c) | (~b & d);
      g = i;
    } else if (i < 32) {
      F = (d & b) | (~d & c);
      g = (5 * i + 1) % 16;
    } else if (i < 48) {
      F = b ^ c ^ d;
      g = (3 * i + 5) % 16;
    } else {
      F = c ^ (b | ~d);
      g = (7 * i) % 16;
    }

    F = F + a + K_d[i] + M[g];
    a = d;
    d = c;
    c = b;
    b = b + ((F << S_d[i]) | (F >> (32 - S_d[i])));
  }

  state[idx].a += a;
  state[idx].b += b;
  state[idx].c += c;
  state[idx].d += d;
}

__global__ void md5_chunk_gpu(struct md5_state *state,
                              const uint32_t *chunks, const int iters) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  uint32_t a = state[idx].a;
  uint32_t b = state[idx].b;
  uint32_t c = state[idx].c;
  uint32_t d = state[idx].d;
  for (int chunk = 0; chunk < iters; chunk++) {
    for (int i = 0; i < 64; i++) {
      uint32_t F, g;
      if (i < 16) {
        F = (b & c) | (~b & d);
        g = i;
      } else if (i < 32) {
        F = (d & b) | (~d & c);
        g = (5 * i + 1) % 16;
      } else if (i < 48) {
        F = b ^ c ^ d;
        g = (3 * i + 5) % 16;
      } else {
        F = c ^ (b | ~d);
        g = (7 * i) % 16;
      }

      F = F + a + K_d[i] + chunks[g + chunk * 64];
      a = d;
      d = c;
      c = b;
      b = b + ((F << S_d[i]) | (F >> (32 - S_d[i])));
    }
  }
  state[idx].a += a;
  state[idx].b += b;
  state[idx].c += c;
  state[idx].d += d;
}
