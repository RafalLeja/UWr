////////////////////////////////////////////////////////////////////////
//
// Practical 4 -- initial code for shared memory reduction for
//                a single block which is a power of two in size
//
////////////////////////////////////////////////////////////////////////

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <helper_cuda.h>

////////////////////////////////////////////////////////////////////////
// CPU routine
////////////////////////////////////////////////////////////////////////

float reduction_gold(float *idata, int len) {
  float sum = 0.0f;
  for (int i = 0; i < len; i++)
    sum += idata[i];

  return sum;
}

////////////////////////////////////////////////////////////////////////
// GPU routine
////////////////////////////////////////////////////////////////////////

__global__ void reduction(float *g_odata, float *g_idata) {
  // dynamically allocated shared memory

  extern __shared__ float temp[];

  int tid = threadIdx.x;

  // first, each thread loads data into shared memory

  temp[tid] = g_idata[tid];

  // next, we perform binary tree reduction

  for (int d = blockDim.x / 2; d > 0; d = d / 2) {
    __syncthreads(); // ensure previous step completed
    if (tid < d)
      temp[tid] += temp[tid + d];
  }

  // finally, first thread puts result into global memory

  if (tid == 0)
    g_odata[0] = temp[0];
}

__global__ void reduction2(float *g_odata, float *g_idata) {
  // dynamically allocated shared memory

  extern __shared__ float temp[];

  int tid = threadIdx.x;

  // first, each thread loads data into shared memory

  temp[tid] = g_idata[tid];

  // next, we perform binary tree reduction
  int m;
  for (m = 1; m < blockDim.x; m = m * 2) {
  }
  m /= 2;
  int overhang = blockDim.x - m;
  if (tid < overhang) {
    // printf("m=%d overhang=%d tid=%d adding %d + %d\n", m, overhang, tid, tid,
    // tid + m);
    temp[tid] += temp[tid + m];
  }
  for (int d = m / 2; d > 0; d = d / 2) {
    __syncthreads(); // ensure previous step completed
    if (tid < d) {
      // printf("m=%d tid=%d adding %d + %d\n", m, tid, tid, tid + d);
      temp[tid] += temp[tid + d];
    }
  }

  // finally, first thread puts result into global memory

  if (tid == 0)
    g_odata[0] = temp[0];
}

__global__ void reduction3(float *g_odata, float *g_idata) {
  // dynamically allocated shared memory

  extern __shared__ float temp[];

  int tid = threadIdx.x;
  int offset = blockIdx.x * blockDim.x;

  // first, each thread loads data into shared memory

  temp[tid] = g_idata[tid + offset];

  // next, we perform binary tree reduction
  int m;
  for (m = 1; m < blockDim.x; m = m * 2) {
  }
  m /= 2;
  int overhang = blockDim.x - m;
  if (tid < overhang) {
    temp[tid] += temp[tid + m];
  }
  for (int d = m / 2; d > 0; d = d / 2) {
    __syncthreads(); // ensure previous step completed
    if (tid < d) {
      // printf("m=%d tid=%d adding %d + %d\n", m, tid, tid, tid + d);
      temp[tid] += temp[tid + d];
    }
  }

  // finally, first thread puts result into global memory

  if (tid == 0)
    atomicAdd(g_odata, temp[0]);
}

__device__ float warpReduceSum(float val) {
  unsigned mask = 0xFFFFFFFF;

  for (int offset = warpSize / 2; offset > 0; offset >>= 1) {
    val += __shfl_down_sync(mask, val, offset);
  }
  return val;
}

__global__ void reduction4(float *g_odata, float *g_idata) {
  // dynamically allocated shared memory

  extern __shared__ float temp[];

  int tid = threadIdx.x;
  int offset = blockIdx.x * blockDim.x;
  int laneid = tid % warpSize;
  int warpid = tid / warpSize;
  int warpCount = blockDim.x / warpSize;

  // first, each thread loads data into shared memory

  temp[tid] = g_idata[tid + offset];

  float warpSum = warpReduceSum(temp[tid]);
  __syncthreads();
  if (laneid == 0) {
    temp[warpid] = warpSum;
    int m;
    for (m = 1; m < warpCount; m = m * 2) {
    }
    m /= 2;
    int overhang = warpCount - m;
    if (warpid < overhang) {
      temp[warpid] += temp[warpid + m];
    }
    for (int d = m / 2; d > 0; d = d / 2) {
      __syncthreads(); // ensure previous step completed
      if (warpid < d) {
        temp[warpid] += temp[warpid + d];
      }
    }
  }
  // finally, first thread puts result into global memory

  if (tid == 0)
    atomicAdd(g_odata, temp[0]);
}
////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////

int main(int argc, const char **argv) {
  int num_blocks, num_threads, num_elements, mem_size, shared_mem_size;

  float *h_data, *d_idata, *d_odata;

  // initialise card

  findCudaDevice(argc, argv);

  num_blocks = 2; // start with only 1 thread block
  num_threads = 192;
  // num_threads = 512;
  num_elements = num_blocks * num_threads;
  mem_size = sizeof(float) * num_elements;

  // allocate host memory to store the input data
  // and initialize to integer values between 0 and 10

  h_data = (float *)malloc(mem_size);

  for (int i = 0; i < num_elements; i++)
    h_data[i] = floorf(10.0f * (rand() / (float)RAND_MAX));

  // compute reference solution

  float sum = reduction_gold(h_data, num_elements);

  // allocate device memory input and output arrays

  checkCudaErrors(cudaMalloc((void **)&d_idata, mem_size));
  checkCudaErrors(cudaMalloc((void **)&d_odata, sizeof(float)));

  // copy host memory to device input array

  checkCudaErrors(
      cudaMemcpy(d_idata, h_data, mem_size, cudaMemcpyHostToDevice));

  // execute the kernel

  shared_mem_size = sizeof(float) * num_threads;
  reduction4<<<num_blocks, num_threads, shared_mem_size>>>(d_odata, d_idata);
  getLastCudaError("reduction kernel execution failed");

  // copy result from device to host

  checkCudaErrors(
      cudaMemcpy(h_data, d_odata, sizeof(float), cudaMemcpyDeviceToHost));

  // check results

  printf("reduction error = %f\n", h_data[0] - sum);

  // cleanup memory

  free(h_data);
  checkCudaErrors(cudaFree(d_idata));
  checkCudaErrors(cudaFree(d_odata));

  // CUDA exit -- needed to flush printf write buffer

  cudaDeviceReset();
}
