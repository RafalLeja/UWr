#include <cuda_runtime.h>
#include <cufft.h>
#include <stdio.h>

#define N 32

int main() {
  cufftComplex h_input[N];
  cufftComplex h_output[N];

  for (int i = 0; i < N; i++) {
    h_input[i].x = (float)i; // real
    h_input[i].y = 0.0f;     // imaginary
  }

  cufftComplex *d_data;
  cudaMalloc((void **)&d_data, sizeof(cufftComplex) * N);

  cudaMemcpy(d_data, h_input, sizeof(cufftComplex) * N, cudaMemcpyHostToDevice);

  cufftHandle plan;
  if (cufftPlan1d(&plan, N, CUFFT_C2C, 1) != CUFFT_SUCCESS) {
    fprintf(stderr, "cuFFT plan creation failed\n");
    return -1;
  }

  if (cufftExecC2C(plan, d_data, d_data, CUFFT_FORWARD) != CUFFT_SUCCESS) {
    fprintf(stderr, "cuFFT execution failed\n");
    return -1;
  }

  cudaMemcpy(h_output, d_data, sizeof(cufftComplex) * N,
             cudaMemcpyDeviceToHost);

  printf("FFT output:\n");
  for (int i = 0; i < N; i++) {
    printf("(%f, %f)\n", h_output[i].x, h_output[i].y);
  }

  cufftDestroy(plan);
  cudaFree(d_data);

  return 0;
}
