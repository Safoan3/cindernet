#include "../header/declaration.h"
#include <cstddef>
#include <cstdlib>
#include <stdio.h>

__global__ void Cmatmul(float *d1, float *d2, float *result, int c1, int c2,
                        int innerdimention) {
  float sum = 0;
  for (int f = 0; f < innerdimention; f++) {
    sum = sum + (d2[threadIdx.y + (f * c2)] * d1[(threadIdx.x * c1) + f]);
  }
  result[threadIdx.x * c2 + threadIdx.y] = sum;
}

void Cuda::matMul(matrix *m1, matrix *m2, matrix *store) {
  float *d_array1 = m1->data;
  float *d_array2 = m2->data;

  float *g_array1;
  float *g_array2;

  float *gpu_result_store;

  cudaMalloc(&g_array1, m1->l * (sizeof(float)));
  cudaMalloc(&g_array2, m2->l * (sizeof(float)));
  cudaMalloc(&gpu_result_store, store->l * sizeof(float));

  // d array is now gpu memory changed my pointer address to another fkloat
  // adress

  cudaMemcpy(g_array1, d_array1, m1->l * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(g_array2, d_array2, m2->l * sizeof(float), cudaMemcpyHostToDevice);

  dim3 block(m1->r, m2->c);
  Cmatmul<<<1, block>>>(g_array1, g_array2, gpu_result_store, m1->c, m2->c,
                        m2->r);

  cudaDeviceSynchronize(); // ← WAIT for GPU!

  cudaMemcpy(store->data, gpu_result_store, store->l * sizeof(float),
             cudaMemcpyDeviceToHost);

  cudaFree(g_array1);
  cudaFree(g_array2);
  cudaFree(gpu_result_store);
}
