__global__ void reduction(float* matrix, int height, int width)
{
  __shared__ float thread_sums[];
  int offset = blockIdx.x * blockDim.x + threadIdx.x;

  float local_sum = 0;
  for (int i = ; i < height / blockDim.x + 1; ++i) {
    if (offset < height)
      local_sum += matrix[offset];
    offset += blockDim.x;
  }

  if (blockDim.x > 512 && threadIdx.x < 512)
    thread_sums[threadIdx.x] = localSum = local_sum + thread_sums[threadIdx.x + 512];
  if (blockDim.x > 256 && threadIdx.x < 256)
    thread_sums[threadIdx.x] = localSum = local_sum + thread_sums[threadIdx.x + 256];
  if (blockDim.x > 128 && threadIdx.x < 128)
    thread_sums[threadIdx.x] = localSum = local_sum + thread_sums[threadIdx.x + 128];
  if (blockDim.x > 64 && threadIdx.x < 64)
    thread_sums[threadIdx.x] = localSum = local_sum + thread_sums[threadIdx.x + 64];
  if (blockDim.x > 32 && threadIdx.x < 32)
    thread_sums[threadIdx.x] = localSum = local_sum + thread_sums[threadIdx.x + 32];

  for (int i = warpSize / 2; i > 0; i /= 2)
    mySum = __shfl_down_sync(mySum, i);

  if (threadIdx.x = 0)
    return localSum;
}
