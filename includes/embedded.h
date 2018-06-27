#ifndef EMBEDDED_H_
#define EMBEDDED_H_

typedef struct Embedded_s {
  int nb_neighbour;
  int vector_size;
  float* d_w2h;
  float* d_w2o;
  float* h_layer;
  float* output;
} Embedded;

void embedded_process_batch(float* input, Embedded* em);

#endif
