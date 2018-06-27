#include "embedded.h"

void embedded_process_batch(int batch_size, float* input, float* output, Embedded* em)
{
  cublasHandle_t handle;
  cublasCreate(&handle);
  float alpha = 1;
  float beta = 0;
  cublasSgemm(handle,
              CUBLAS_OP_N,
              CUBLAS_OP_N,
              vector_size, batch_size, em->dict_size * em->nb_neighbour, &alpha,
              em->w2h, input, vector_size, em->dict_size * em->nb_neighbour,
              &beta, em->ouput, vector_size);
  cublasSgemm(handle,
              CUBLAS_OP_N,
              CUBLAS_OP_N,
              vector_size, batch_size, em->dict_size * em->nb_neighbour, &alpha,
              em->w2h, input, vector_size, em->dict_size * em->nb_neighbour,
              &beta, em->ouput, vector_size);

  cublasDestroy(handle);
}
