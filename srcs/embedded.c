#include <cublas_v2.h>
#include "embedded.h"

void embedded_process_batch(int batch_size, float* d_input, float* d_output, Embedded* em)
{
  cublasHandle_t handle;
  cublasCreate(&handle);
  float alpha = 1;
  float beta = 0;
  cublasSgemm(handle,
              CUBLAS_OP_N,
              CUBLAS_OP_N,
              em->vector_size, batch_size, em->dict_size * em->nb_neighbour, &alpha,
              em->d_w2h, em->vector_size, d_input, em->dict_size * em->nb_neighbour,
              &beta, em->d_output, em->vector_size);
  cublasSgemm(handle,
              CUBLAS_OP_N,
              CUBLAS_OP_N,
              em->dict_size, batch_size, vector_size, &alpha,
              em->d_w2o, em->dict_size, d_input, vector_size,
              &beta, em->d_output, em->dict_size);
  reduce()
  cublasDestroy(handle);
}
