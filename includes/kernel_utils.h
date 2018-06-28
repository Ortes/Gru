#ifndef KERNEL_UTILS_H_
#define KERNEL_UTILS_H_

#define REDUCTION_THREADS 1024

extern "C" void reduction(float* matrix, int height, int width, float* result);

#endif
