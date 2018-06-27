#ifndef EMBEDDED_H_
#define EMBEDDED_H_

typedef struct Embedded_s {
  int nb_neighbour;
  int vector_size;
  float* w2h;
  float* w2o;
} Embedded;

void embedded_process_batch(float* input, Embedded* nn);

#endif
