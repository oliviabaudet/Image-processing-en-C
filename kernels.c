
#include <stdlib.h>

float **sharpen_new() {
    float **kernel = malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++) {
        kernel[i] = malloc(3 * sizeof(float));
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
