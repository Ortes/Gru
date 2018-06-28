#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include "embedded.h"
#include "kernel_embedded.h"
#include "kernel_utils.h"

static int init = 0;
static float* d_h_layer;
static float* d_o_layer;
static float* d_reduction_vector;

void init_embedded_training(int batch_size, Embedded* em)
{
  cudaMalloc((void**)&d_h_layer, batch_size * em->vector_size * sizeof(float));
  cudaMalloc((void**)&d_o_layer, batch_size * em->dict_size * sizeof(float));
  cudaMalloc((void**)&d_reduction_vector, batch_size * sizeof(float));
  init = 1;
}

void embedded_process_batch(int batch_size, float* d_input, float* d_expected, Embedded* em)
{
  if (!init)
    init_embedded_training(batch_size, em);
  cublasHandle_t handle;
  cublasCreate(&handle);
  float alpha = 1;
  float beta = 0;
  cublasSgemm(handle,
              CUBLAS_OP_N,
              CUBLAS_OP_N,
              em->vector_size, batch_size, em->dict_size * em->nb_neighbour, &alpha,
              em->d_w2h, em->vector_size, d_input, em->dict_size * em->nb_neighbour,
              &beta, d_h_layer, em->vector_size);
  cublasSgemm(handle,
              CUBLAS_OP_N,
              CUBLAS_OP_N,
              em->dict_size, batch_size, em->vector_size, &alpha,
              em->d_w2o, em->dict_size, d_input, em->vector_size,
              &beta, d_o_layer, em->dict_size);
  m_exp_reduction(d_o_layer, em->dict_size, batch_size, d_reduction_vector);
  cublasDestroy(handle);
}
