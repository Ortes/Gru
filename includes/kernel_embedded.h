#ifndef KERNEL_EMBEDDED_H_
#define KERNEL_EMBEDDED_H_

void m_exp_reduction(float* matrix, float* exp_matrix, int height, int width, float* result);
void v_exp(float* array, int size);
void m_softmax(float* matrix, int height, int width, float* exp_sum);
void w2o_update(float* weights, int height, int width, int batch_size, float* exp_vec, float* ouput, float* expected);

#endif
