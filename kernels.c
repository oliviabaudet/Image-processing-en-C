#include <stdlib.h>

float **new_kernel(int size) {
    float **kernel = malloc(size * sizeof(float *));
    if (!kernel) return NULL;

    for (int i = 0; i < size; i++) {
        kernel[i] = malloc(size * sizeof(float));
        if (!kernel[i]) {
            for (int j = 0; j < i; j++) free(kernel[j]);
            free(kernel);
            return NULL;
        }
    }
    return kernel;
}

void free_kernel(float **kernel, int size) {
    for (int i = 0; i < size; i++) {
        free(kernel[i]);
    }
    free(kernel);
}

float **sharpen_new() {
    float **kernel = new_kernel(3);

    kernel[0][0] =  0;  kernel[0][1] = -1;  kernel[0][2] =  0;
    kernel[1][0] = -1;  kernel[1][1] =  5;  kernel[1][2] = -1;
    kernel[2][0] =  0;  kernel[2][1] = -1;  kernel[2][2] =  0;

    return kernel;
}

void sharpen_delete(float **kernel) {
    free_kernel(kernel, 3);
}

float **box_blur_new(void) {
    int k = 3;
    float **kernel = new_kernel(k);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            kernel[i][j] = 1.0f / 9.0f;
        }
    }
    return kernel;
}

void box_blur_delete(float **kernel) {
    free_kernel(kernel, 3);
}

float **gaussian_blur_new(void) {
    float **kernel = new_kernel(3);

    kernel[0][0] = 1.0f / 16.0f;  kernel[0][1] = 2.0f / 16.0f;  kernel[0][2] = 1.0f / 16.0f;
    kernel[1][0] = 2.0f / 16.0f;  kernel[1][1] = 4.0f / 16.0f;  kernel[1][2] = 2.0f / 16.0f;
    kernel[2][0] = 1.0f / 16.0f;  kernel[2][1] = 2.0f / 16.0f;  kernel[2][2] = 1.0f / 16.0f;

    return kernel;
}

void gaussian_blur_delete(float **kernel) {
    free_kernel(kernel, 3);
}

float **outline_new(void) {
    float **kernel = new_kernel(3);

    kernel[0][0] = -1.0f;  kernel[0][1] = -1.0f;  kernel[0][2] = -1.0f;
    kernel[1][0] = -1.0f;  kernel[1][1] =  8.0f;  kernel[1][2] = -1.0f;
    kernel[2][0] = -1.0f;  kernel[2][1] = -1.0f;  kernel[2][2] = -1.0f;

    return kernel;
}

void outline_delete(float **kernel) {
    free_kernel(kernel, 3);
}

float **emboss_new(void) {
    float **kernel = new_kernel(3);

    kernel[0][0] = -2.0f; kernel[0][1] = -1.0f; kernel[0][2] =  0.0f;
    kernel[1][0] = -1.0f; kernel[1][1] =  1.0f; kernel[1][2] =  1.0f;
    kernel[2][0] =  0.0f; kernel[2][1] =  1.0f; kernel[2][2] =  2.0f;

    return kernel;
}

void emboss_delete(float **kernel) {
    free_kernel(kernel, 3);
}