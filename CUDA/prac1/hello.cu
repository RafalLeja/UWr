#include <cuda_runtime.h>
#include <stdio.h>

__global__ void helloworld_GPU(void) {
  int tid = threadIdx.x + blockDim.x * blockIdx.x;
  printf("Hello world! tid = %d\n", tid);
}

int main(void) {

  helloworld_GPU<<<2, 2>>>();
  cudaDeviceSynchronize();
  //   cudaDeviceReset();

  return 0;
}
