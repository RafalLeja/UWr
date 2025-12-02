/*
 * ZAD 5
 * ilość wątków: 9600000
 * ilość pamięci: N + d_z + rho + alpha + con1 + con2 + r + T =
 * = int + 7 * float = 4 + 7 * 4 = 32B
 * czas = 19ms, 53ms = 0.019s, 0.053s
 *
 * ilość wątków * ilość pamięci przez wątek =
 * 9600000 * 32B = 307,200,000 B = 307,2MB = 0,3072GB
 *
 * wersja 1:
 * 0,3072GB / 0,019s = 16,1684 GB/s
 *
 * wersja 2:
 * 0,3072GB / 0,053s = 5,7962 GB/s
 *
 * Max dla 5060ti to 448 GB/s
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <cuda.h>
#include <curand.h>

#include <helper_cuda.h>

__constant__ int N;
__constant__ float a, b, c;

__global__ void pathcalc(float *d_z, float *d_v) {
  float z, sum;
  int ind;

  ind = threadIdx.x + N * blockIdx.x * blockDim.x;

  sum = 0;
  for (int n = 0; n < N; n++) {
    z = d_z[ind];
    ind += blockDim.x; // shift pointer to next element

    sum += a * z * z + b * z + c;
  }

  d_v[threadIdx.x + blockIdx.x * blockDim.x] = sum / N;
}

int main(int argc, const char **argv) {

  int NPATH = 9600000, h_N = 200;
  float h_a, h_b, h_c;
  float *h_v, *d_v, *d_z;
  double sum1, sum2;

  // initialise card

  findCudaDevice(argc, argv);

  // initialise CUDA timing

  float milli;
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  // allocate memory on host and device

  h_v = (float *)malloc(sizeof(float) * NPATH);

  checkCudaErrors(cudaMalloc((void **)&d_v, sizeof(float) * NPATH));
  checkCudaErrors(cudaMalloc((void **)&d_z, sizeof(float) * h_N * NPATH));

  // define constants and transfer to GPU

  h_a = 1.5f;
  h_b = 2.5f;
  h_c = 3.5f;

  checkCudaErrors(cudaMemcpyToSymbol(N, &h_N, sizeof(h_N)));
  checkCudaErrors(cudaMemcpyToSymbol(a, &h_a, sizeof(h_a)));
  checkCudaErrors(cudaMemcpyToSymbol(b, &h_b, sizeof(h_b)));
  checkCudaErrors(cudaMemcpyToSymbol(c, &h_c, sizeof(h_c)));

  // random number generation

  curandGenerator_t gen;
  checkCudaErrors(curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT));
  checkCudaErrors(curandSetPseudoRandomGeneratorSeed(gen, 1234ULL));

  cudaEventRecord(start);
  checkCudaErrors(curandGenerateNormal(gen, d_z, h_N * NPATH, 0.0f, 1.0f));
  cudaEventRecord(stop);

  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milli, start, stop);

  printf("CURAND normal RNG  execution time (ms): %f,  samples/sec: %e \n",
         milli, h_N * NPATH / (0.001 * milli));

  // execute kernel and time it

  /* ilość pamięci:
   * 9600000
   */
  cudaEventRecord(start);
  pathcalc<<<NPATH / 128, 128>>>(d_z, d_v);
  cudaEventRecord(stop);

  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milli, start, stop);

  getLastCudaError("avg_calc execution failed\n");
  printf("Average calc kernel execution time (ms): %f \n", milli);

  // copy back results

  checkCudaErrors(
      cudaMemcpy(h_v, d_v, sizeof(float) * NPATH, cudaMemcpyDeviceToHost));

  // compute average

  sum1 = 0.0;
  sum2 = 0.0;
  for (int i = 0; i < NPATH; i++) {
    sum1 += h_v[i];
    sum2 += h_v[i] * h_v[i];
  }

  printf("\nAverage value and standard deviation of error  = %13.8f %13.8f\n\n",
         sum1 / NPATH,
         sqrt((sum2 / NPATH - (sum1 / NPATH) * (sum1 / NPATH)) / NPATH));

  // Tidy up library

  checkCudaErrors(curandDestroyGenerator(gen));

  // Release memory and exit cleanly

  free(h_v);
  checkCudaErrors(cudaFree(d_v));
  checkCudaErrors(cudaFree(d_z));

  // CUDA exit -- needed to flush printf write buffer

  cudaDeviceReset();
}
