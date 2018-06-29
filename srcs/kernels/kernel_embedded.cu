#include "kernel_utils.h"
#include "constant.h"

__global__ void d_exp_reduction(float* matrix, float* exp_matrix, int height, int width, float* result)
{
  extern __shared__ float thread_sums[];

  int offset;
  if (!(height % 32))
    offset = blockIdx.x * height + threadIdx.x;
  else
    offset = blockIdx.x * ALIGN32(height) + threadIdx.x;

  float local_sum = 0;
  for (int i = 0; i < height / blockDim.x + 1 && offset < height; ++i, offset += blockDim.x)
    local_sum += exp_matrix[offset] = EXP_FUNC(matrix[offset]);

  thread_sums[threadIdx.x] = local_sum;
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

__global__ void d_exp(float* array, int size)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  if (index < size)
    array[index] = exp(array[index]);
}

__global__ void d_softmax(float* matrix, int height, int width, float* exp_sum)
{
  int size = ALIGN32(height) * width;
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  if (index < size)
    matrix[index] /= exp_sum[index / ALIGN32(height)];
}
__global__ void d_w2o_update(float* weights, int height, int width, int batch_size, float* exp_vec, float* ouput, float* expected)
{
  int size = ALIGN32(height) * width;
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  if (index < size)
    ;
}


// cpu call wrappers

extern "C" void m_exp_reduction(float* matrix, float* exp_matrix, int height, int width, float* result)
{
  d_exp_reduction<<<width, REDUCTION_THREADS, REDUCTION_THREADS * sizeof(float)>>>(matrix, exp_matrix, height, width, result);
}

extern "C" void v_exp(float* array, int size)
{
  d_exp<<<size / EXP_THREADS + 1, EXP_THREADS>>>(array, size);
}

extern "C" void m_softmax(float* matrix, int height, int width, float* exp_sum)
{
  d_softmax<<<(ALIGN32(height) * width) / SOFTMAX_THREADS + 1, SOFTMAX_THREADS>>>(matrix, height, width, exp_sum);
}

extern "C" void w2o_update(float* weights, int height, int width, int batch_size, float* exp_vec, float* ouput, float* expected)
{
  d_w2o_update<<<(ALIGN32(height) * width) / UPDATE_L1_THREADS + 1, UPDATE_L1_THREADS>>>(weights, height, width, batch_size, exp_vec, ouput, expected);
}
