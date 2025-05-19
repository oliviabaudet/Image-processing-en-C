#include "../bmp8.h"
#include "../kernels.h"

#include <stdio.h>


int main(int argc, char **argv) {
    t_bmp8 *image;

    image = bmp8_loadImage("../images/barbara_gray.bmp");
    if (image == NULL) {
        printf("Error loading image\n");
        return -1;
    }
    // bmp8_printInfo(image);
    // bmp8_saveImage("../test/origin.bmp", image);
    //bmp8_negative(image);
    //bmp8_saveImage("../test/negatif.bmp", image);
    //bmp8_brightness(image, 50);
    //bmp8_saveImage("../test/brightness.bmp", image);
    // bmp8_threshold(image, 128);
    // bmp8_saveImage("../test/threshold.bmp", image);

    //    float **sharpen = sharpen_new();
    //    bmp8_applyFilter(image, sharpen, 3);
    //    sharpen_delete(sharpen);

    // float **blur = box_blur_new();
    // bmp8_applyFilter(image, blur, 3);
    // box_blur_delete(blur);

    // float **blur = gaussian_blur_new();
    // bmp8_applyFilter(image, blur, 3);
    // gaussian_blur_delete(blur);

    // float **outline = outline_new();
    // bmp8_applyFilter(image, outline, 3);
    // outline_delete(outline);

    // float **emboss = emboss_new();
    // bmp8_applyFilter(image, emboss, 3);
    // emboss_delete(emboss);

    bmp8_equalize(image);

    bmp8_saveImage("../test/filter.bmp", image);

    bmp8_free(image);

    return 0;
}

//Commande pour dépot intermédiaire
//git push submit main