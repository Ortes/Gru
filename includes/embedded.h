#ifndef DATA_H_
#define DATA_H_

typedef struct Embedded_s {
  int nb_words;
  int nb_layers;
  int* layers_size;
  float** weigths;
} Embedded;

void embedded_process_batch(float* input, Embedded* nn);

#endif
