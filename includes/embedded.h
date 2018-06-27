#ifndef EMBEDDED_H_
#define EMBEDDED_H_

typedef struct Embedded_s {
  int nb_neighbour;
  int vector_size;
  int dict_size;
  float* d_w2h;
  float* d_w2o;
  float* d_h_layer;
  float* d_output;
} Embedded;

void embedded_process_batch(int batch_size, float* d_input, float* d_output, Embedded* em);

#endif
