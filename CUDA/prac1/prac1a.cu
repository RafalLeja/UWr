//
// include files
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// kernel routine
//

__global__ void my_first_kernel(float *x) {
  int tid = threadIdx.x + blockDim.x * blockIdx.x;

  x[tid] = (float)threadIdx.x;
}

__global__ void add_vectors(float *a, float *b, float *c) {
  int tid = threadIdx.x + blockDim.x * blockIdx.x;
  c[tid] = a[tid] + b[tid];
}

//
// main code
//

int main(int argc, char **argv) {
  float *h_x, *d_x;
  float *h_c, *d_a, *d_b, *d_c;
  int nblocks, nthreads, nsize, n;

  // set number of blocks, and threads per block

  // nblocks = 2000;
  nblocks = 2;
  // nthreads = 8000;
  nthreads = 8;
  nsize = nblocks * nthreads;

  // allocate memory for array

  h_x = (float *)malloc(nsize * sizeof(float));
  cudaMalloc((void **)&d_x, nsize * sizeof(float));

  h_c = (float *)malloc(nsize * sizeof(float));
  cudaMalloc((void **)&d_a, nsize * sizeof(float));
  cudaMalloc((void **)&d_b, nsize * sizeof(float));
  cudaMalloc((void **)&d_c, nsize * sizeof(float));
  // execute kernel

  my_first_kernel<<<nblocks, nthreads>>>(d_x);

  my_first_kernel<<<nblocks, nthreads>>>(d_a);
  my_first_kernel<<<nblocks, nthreads>>>(d_b);

  add_vectors<<<nblocks, nthreads>>>(d_a, d_b, d_c);

  // copy back results and print them out

  cudaMemcpy(h_x, d_x, nsize * sizeof(float), cudaMemcpyDeviceToHost);

  cudaMemcpy(h_c, d_c, nsize * sizeof(float), cudaMemcpyDeviceToHost);

  for (n = 0; n < nsize; n++)
    printf(" n,  x  =  %d  %f \n", n, h_x[n]);

  printf("Dodawanie wektorów:\n");

  for (n = 0; n < nsize; n++)
    printf(" n,  c  =  %d  %f \n", n, h_c[n]);
  // free memory

  cudaFree(d_x);
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
  free(h_x);
  free(h_c);

  // CUDA exit -- needed to flush printf write buffer

  cudaDeviceReset();

  return 0;
}
