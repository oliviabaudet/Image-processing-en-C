#include <stdlib.h>

float **sharpen_new() {
    int k = 3;
    float **kernel = malloc(k * sizeof(float *));
    for (int i = 0; i < k; i++) {
        kernel[i] = malloc(k * sizeof(float));
    }

    kernel[0][0] =  0;  kernel[0][1] = -1;  kernel[0][2] =  0;
    kernel[1][0] = -1;  kernel[1][1] =  5;  kernel[1][2] = -1;
    kernel[2][0] =  0;  kernel[2][1] = -1;  kernel[2][2] =  0;

    return kernel;
}

void sharpen_delete(float **kernel) {
    for (int i = 0; i < 3; i++) {
        free(kernel[i]);
    }
    free(kernel);
}

float **blur_new(void) {
    int k = 3;
    float **kernel = malloc(k * sizeof(float *));
    if (!kernel) return NULL;
    for (int i = 0; i < k; i++) {
        kernel[i] = malloc(k * sizeof(float));
        if (!kernel[i]) {
            for (int j = 0; j < i; j++) free(kernel[j]);
            free(kernel);
            return NULL;
        }
        for (int j = 0; j < k; j++) {
            kernel[i][j] = 1.0f / 9.0f;
        }
    }
    return kernel;
}

void free_kernel(float **kernel) {
    int size = 3;
    for (int i = 0; i < size; i++) {
        free(kernel[i]);
    }
    free(kernel);
}