#include "../bmp8.h"

#include <stdio.h>

int main(int argc, char **argv) {
    t_bmp8 *image;

    image = bmp8_loadImage("../images/barbara_gray.bmp");
    if (image == NULL) {
        printf("Error loading image\n");
        return -1;
    }
    bmp8_printInfo(image);
    bmp8_saveImage("../test/test.bmp", image);
    bmp8_free(image);

    return 0;
}
