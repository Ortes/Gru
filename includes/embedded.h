#ifndef EMBEDDED_H_
#define EMBEDDED_H_

typedef struct Embedded_s {
  int nb_neighbour;
  int vector_size;
  int dict_size; // nb word in dict
  float* d_w2h; // nb_neighbour * dict_size x vector_size
  float* d_w2o; // (vector_size + 1 (bias)) x dict_size
} Embedded;

void embedded_process_batch(int batch_size, float* d_input, float* d_expected, Embedded* em);

#endif
