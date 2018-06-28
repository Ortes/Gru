#include "kernel_utils.h"

__global__ void d_reduction(float* matrix, int height, int width, float* result)
{
  extern __shared__ float thread_sums[];
  int offset = blockIdx.x * blockDim.x + threadIdx.x;

  float local_sum = 0;
  for (int i = 0; i < height / blockDim.x + 1; ++i) {
    if (offset < height)
      local_sum += matrix[offset];
    offset += blockDim.x;
  }
  __syncthreads();

  if (blockDim.x > 512 && threadIdx.x < 512)
    thread_sums[threadIdx.x] = local_sum = local_sum + thread_sums[threadIdx.x + 512];
  __syncthreads();
  if (blockDim.x > 256 && threadIdx.x < 256)
    thread_sums[threadIdx.x] = local_sum = local_sum + thread_sums[threadIdx.x + 256];
  __syncthreads();
  if (blockDim.x > 128 && threadIdx.x < 128)
    thread_sums[threadIdx.x] = local_sum = local_sum + thread_sums[threadIdx.x + 128];
  __syncthreads();
  if (blockDim.x > 64 && threadIdx.x < 64)
    thread_sums[threadIdx.x] = local_sum = local_sum + thread_sums[threadIdx.x + 64];
  __syncthreads();
  if (blockDim.x > 32 && threadIdx.x < 32)
    thread_sums[threadIdx.x] = local_sum = local_sum + thread_sums[threadIdx.x + 32];
  __syncthreads();
  for (int i = warpSize / 2; i > 0; i /= 2)
    local_sum = __shfl_down_sync(0xFFFFFFFF, local_sum, i);

  if (threadIdx.x == 0)
    result[blockIdx.x] = local_sum;
}

extern "C" void reduction(float* matrix, int height, int width, float* result)
{
  d_reduction<<<width, REDUCTION_THREADS, REDUCTION_THREADS * sizeof(float)>>>(matrix, height, width, result);
}
