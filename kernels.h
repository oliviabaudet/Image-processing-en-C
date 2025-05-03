#ifndef KERNELS_H
#define KERNELS_H

float **sharpen_new();
void sharpen_delete(float **kernel);

float **blur_new(void);
void free_kernel(float **kernel);

#endif //KERNELS_H