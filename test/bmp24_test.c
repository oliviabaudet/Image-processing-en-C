#include "../bmp24.h"

#include <stdio.h>


int main(int argc, char **argv) {
    t_bmp24 *image = bmp24_loadImage("../images/flowers_color.bmp");
    if (image == NULL) {
        printf("Error loading image\n");
        return -1;
    }

    bmp24_dump(image);

    // bmp24_brightness(image, 50);

    // bmp24_boxBlur(image);
    // bmp24_gaussianBlur(image);
    // bmp24_outline(image);
    // bmp24_emboss(image);
    // bmp24_sharpen(image);

    // bmp24_equalize(image);

    bmp24_saveImage(image, "../test/flowers_test.bmp");

    bmp24_free(image);

    return 0;
}
