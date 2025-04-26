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
    bmp8_saveImage("../test/origin.bmp", image);
    //bmp8_negative(image);
    //bmp8_saveImage("../test/negatif.bmp", image);
    //bmp8_brightness(image, 50);
    //bmp8_saveImage("../test/brightness.bmp", image);
    bmp8_threshold(image, 128);
    bmp8_saveImage("../test/threshold.bmp", image);
    bmp8_free(image);

    return 0;
}
