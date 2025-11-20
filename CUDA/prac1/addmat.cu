// CUDA przykład (c) Andrzej Łukaszewski 2010
// Dodawanie macierzy na GPU:                   kompilacja: nvcc addmat.cu 
#include <stdio.h>

__global__ void AddMatrixKernel1(float *A, float *B, float *C, int N){
   int adres = threadIdx.x + N * blockIdx.x;
   C[adres] = A[adres] + B[adres];
}

void GPUMatrixAdd(float *A, float *B, float *C, int N) {
   int size = N*N*sizeof(float);
   float  *Ad, *Bd, *Cd;   //  macierze na GPU

   cudaMalloc(&Ad, size);
   cudaMemcpy(Ad, A, size, cudaMemcpyHostToDevice);
   cudaMalloc(&Bd, size);
   cudaMemcpy(Bd, B, size, cudaMemcpyHostToDevice);
   cudaMalloc(&Cd, size);

   // Wywołanie jądra   np.:
   AddMatrixKernel1<<<N,N>>>(Ad,Bd,Cd,N); // N bloków po N wątków

   cudaMemcpy(C, Cd, size, cudaMemcpyDeviceToHost);
   cudaFree(Ad);   cudaFree(Bd);   cudaFree(Cd);
}

int main(){
   float  A[4]={ 1., 1., 1., 1. };
   float  B[4]={ 2., 3., 4., 5. };
   float  C[4];

   printf("A[1]=%f\n", A[1]);  printf("B[1]=%f\n", B[1]);
   GPUMatrixAdd(A,B,C,2);
   printf("C[1]=%f\n", C[1]);
   return 0;
}
