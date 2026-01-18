#include <cuda_runtime.h>
#include <stdint.h>

struct md5_state {
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
};

struct md5_state md5_iter(struct md5_state state, uint32_t *M);

struct md5_state md5_passwd(char *pass, int pass_len);

__global__ void md5_iter_gpu(struct md5_state *state, const uint32_t *M);

__global__ void md5_chunk_gpu(struct md5_state *state,
                              const uint32_t *chunks, const int iters);

struct md5_state md5_init();

void md5_padding(uint64_t file_size, char *pad, int *pad_len);

extern const uint32_t K[];

extern const uint32_t S[];
