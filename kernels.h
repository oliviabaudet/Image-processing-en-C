#ifndef KERNELS_H
#define KERNELS_H

float **sharpen_new();
void sharpen_delete(float **kernel);

float **box_blur_new(void);
void box_blur_delete(float **kernel);

float **gaussian_blur_new(void);
void gaussian_blur_delete(float **kernel);

float **outline_new(void);
void outline_delete(float **kernel);

float **emboss_new(void);
void emboss_delete(float **kernel);



#endif //KERNELS_H