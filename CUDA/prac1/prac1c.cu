//
// include files
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <helper_cuda.h>

//
// kernel routine
//

__global__ void my_first_kernel(float *x) {
  int tid = threadIdx.x + blockDim.x * blockIdx.x;

  x[tid] = (float)threadIdx.x;
}

//
// globals
//
__managed__ float y[] = {0., 1., 2., 3., 4., 5., 6., 7.};

//
// main code
//

int main(int argc, const char **argv) {
  float *x;
  int nblocks, nthreads, nsize, n;

  // initialise card

  findCudaDevice(argc, argv);

  // set number of blocks, and threads per block

  nblocks = 2;
  nthreads = 8;
  nsize = nblocks * nthreads;

  // allocate memory for array

  checkCudaErrors(cudaMallocManaged(&x, nsize * sizeof(float)));

  // execute kernel

  my_first_kernel<<<nblocks, nthreads>>>(x);
  my_first_kernel<<<nblocks, nthreads>>>(y);
  getLastCudaError("my_first_kernel execution failed\n");

  // synchronize to wait for kernel to finish, and data copied back

  // cudaDeviceSynchronize();
  // Bez sunchronizacji odczytamy 0 zamiast niektórych wartości

  for (n = 0; n < nsize; n++)
    printf(" n,  x  =  %d  %f \n", n, x[n]);

  for (n = 0; n < nsize; n++)
    printf(" n,  y  =  %d  %f \n", n, y[n]);
  // free memory

  checkCudaErrors(cudaFree(x));
  // checkCudaErrors(cudaFree(y));

  // CUDA exit -- needed to flush printf write buffer

  cudaDeviceReset();

  return 0;
}
