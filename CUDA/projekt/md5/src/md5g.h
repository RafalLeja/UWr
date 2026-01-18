#include <cuda_runtime.h>
#include <stdint.h>

__global__ void md5_iter_gpu(struct md5_state *state, const uint32_t *M);

// extern __constant__ __device__ uint32_t K_g[];

// extern __constant__ __device__ uint32_t S_g[];
