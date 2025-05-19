#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "bmp24.h"
#include "kernels.h"

void bmp24_dump(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    printf("Header type : 0x%x\n", img->header.type);
    printf("Header size : %d\n", img->header.size);
    printf("Header offset : %d\n", img->header.offset);
    printf("Size : %d\n", img->header_info.size);
    printf("info Width : %d\n", img->header_info.width);
    printf("info Height : %d\n", img->header_info.height);
    printf("Color depth : %d\n", img->colorDepth);
}

t_bmp24 * bmp24_loadImage (const char * filename) {
    FILE *file = NULL;

    if (filename == NULL) {
        return NULL;
    }
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file '%s': %s\n", filename, strerror(errno));
        return NULL;
    }
    printf("Loading %s\n", filename);

    int width, height, colorDepth;

    file_rawRead(BITMAP_WIDTH, &width, sizeof(width), 1, file);
    file_rawRead(BITMAP_HEIGHT, &height, sizeof(height), 1, file);
    file_rawRead(BITMAP_DEPTH, &colorDepth, sizeof(colorDepth), 1, file);
    printf("%d, %d, %d\n", width, height, colorDepth);
    t_bmp24* bmp24 = bmp24_allocate(width, height, colorDepth);

    file_rawRead(BITMAP_MAGIC, &(bmp24->header), sizeof(bmp24->header), 1, file);
    file_rawRead(sizeof(bmp24->header), &(bmp24->header_info), sizeof(bmp24->header_info), 1, file);
    bmp24_readPixelData(bmp24, file);

    fclose(file);
    return bmp24;
}

void bmp24_saveImage (t_bmp24 * img, const char * filename) {
    FILE *file = NULL;

    if (filename == NULL) {
        printf("NULL filename passed\n");
        return;
    }
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }

    file = fopen(filename, "wb");
    if (!file) {
        printf("Error opening file '%s': %s\n", filename, strerror(errno));
        return;
    }

    file_rawWrite(BITMAP_MAGIC,  &(img->header), sizeof(img->header), 1, file);
    file_rawWrite(sizeof(img->header), &(img->header_info), sizeof(img->header_info), 1, file);
    bmp24_writePixelData(img, file);
    fclose(file);
}


t_pixel **bmp24_allocateDataPixels(int width, int height) {
    t_pixel **pixels = malloc(sizeof(t_pixel *) * height);
    if (!pixels) {
        perror("erreur");
        return NULL;
    }

    for (int i = 0; i < height; i++) {
        pixels[i] = malloc(sizeof(t_pixel) * width);
        if (!pixels[i]) {
            perror("erreur");
            return NULL;
        }
    }
    return pixels;
}

void bmp24_freeDataPixels(t_pixel **pixels, int height) {
    if (pixels) {
        for (int i = 0; i < height; i++) {
            free(pixels[i]);
        }
        free(pixels);
    }
}

t_bmp24 *bmp24_allocate(int width, int height, int colorDepth) {
    t_bmp24 *img = (t_bmp24 *) malloc(sizeof(t_bmp24));
    if (!img) {
        perror("erreur");
        return NULL;
    }

    img->width = width;
    img->height = height;
    img->colorDepth = colorDepth;
    img->data = bmp24_allocateDataPixels(width, height);

    if (!img->data) {
        free(img);
        return NULL;
    }
    return img;
}

void bmp24_free(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    if (img->data) {
        bmp24_freeDataPixels(img->data, img->height);
        free(img);
    }
}


void file_rawRead(uint32_t position, void *buffer, uint32_t size, size_t n, FILE *file) {
    if (file == NULL) {
        printf("NULL file passed\n");
        return;
    }
    fseek(file, (long)position, SEEK_SET);
    fread(buffer, size, n, file);
}


void file_rawWrite(uint32_t position, void *buffer, uint32_t size, size_t n, FILE *file) {
    if (file == NULL) {
        printf("NULL file passed\n");
        return;
    }
    fseek(file, (long)position, SEEK_SET);
    fwrite(buffer, size, n, file);
}


void bmp24_readPixelValue(t_bmp24 *img, int x, int y, FILE *file) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    if (file == NULL) {
        printf("NULL file passed\n");
        return;
    }

    fread(&img->data[y][x].blue, 1, 1, file);
    fread(&img->data[y][x].green, 1, 1, file);
    fread(&img->data[y][x].red, 1, 1, file);
}

void bmp24_readPixelData(t_bmp24 *img, FILE *file) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    if (file == NULL) {
        printf("NULL file passed\n");
        return;
    }

    fseek(file, img->header.offset, SEEK_SET);
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            bmp24_readPixelValue(img, x, y, file);
        }
    }
}


void bmp24_writePixelValue(t_bmp24 *img, int x, int y, FILE *file) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    if (file == NULL) {
        printf("NULL file passed\n");
        return;
    }

    fwrite(&img->data[y][x].blue, 1, 1, file);
    fwrite(&img->data[y][x].green, 1, 1, file);
    fwrite(&img->data[y][x].red, 1, 1, file);
}

void bmp24_writePixelData(t_bmp24 *img, FILE *file) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    if (file == NULL) {
        printf("NULL file passed\n");
        return;
    }

    fseek(file, img->header.offset, SEEK_SET);
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            bmp24_writePixelValue(img, x, y, file);
        }
    }
}

void bmp24_negative(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->data[i][j].red = 255 - img->data[i][j].red;
            img->data[i][j].green = 255 - img->data[i][j].green;
            img->data[i][j].blue = 255 - img->data[i][j].blue;
        }
    }
}

void bmp24_grayscale(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            uint8_t gray = (img->data[i][j].red + img->data[i][j].green + img->data[i][j].blue) / 3;
            img->data[i][j].red = img->data[i][j].green = img->data[i][j].blue = gray;
        }
    }
}

void bmp24_brightness (t_bmp24 * img, int value) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return;
    }
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            int new_value = img->data[i][j].red + value;
            img->data[i][j].red = (new_value > 255) ? 255 : new_value;
            new_value = img->data[i][j].green + value;
            img->data[i][j].green = (new_value > 255) ? 255 : new_value;
            new_value = img->data[i][j].blue + value;
            img->data[i][j].blue = (new_value > 255) ? 255 : new_value;
        }
    }
}

t_pixel bmp24_convolution (t_bmp24 * img, int x, int y, float ** kernel, int kernelSize) {
    t_pixel pixel = { 0, 0, 0};

    if (img == NULL || img->data == NULL) {
        printf("NULL image passed\n");
        return pixel;
    }
    if (kernel == NULL) {
        printf("NULL kernel passed\n");
        return pixel;
    }

    int n = kernelSize / 2;
    float red = 0, green = 0, bleu = 0;

    for (int ky = -n; ky <= n; ky++) {
        int posy = y + ky;
        if (posy < 0 || posy >= img->height) continue;

        for (int kx = -n; kx <= n; kx++) {
            int posx = x + kx;
            if (posx < 0 || posx >= img->width) continue;

            float coeff = kernel[ky + n][kx + n];

            red   += coeff * (float)(img->data[posy][posx].red);
            green += coeff * (float)(img->data[posy][posx].green);
            bleu  += coeff * (float)(img->data[posy][posx].blue);
        }
    }

    // Limiter les valeurs entre 0 et 255
    pixel.red   = (unsigned char)fmaxf(0, fminf(255, roundf(red)));
    pixel.green = (unsigned char)fmaxf(0, fminf(255, roundf(green)));
    pixel.blue  = (unsigned char)fmaxf(0, fminf(255, roundf(bleu)));

    return pixel;
}

void bmp24_apply_convolution(t_bmp24 * img, float ** kernel, int kernelSize) {
    // Créer une copie temporaire des données
    t_pixel **temp = bmp24_allocateDataPixels(img->width, img->height);

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            t_pixel pixel = bmp24_convolution(img, i, j, kernel, kernelSize);
            temp[i][j].red = pixel.red;
            temp[i][j].green = pixel.green;
            temp[i][j].blue = pixel.blue;
        }
    }
    // Copie du résultat dans l'image originale
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->data[i][j] = temp[i][j];
        }
    }
    bmp24_freeDataPixels(temp, img->height);
}

void bmp24_boxBlur(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return ;
    }
    float **kernel = box_blur_new();
    bmp24_apply_convolution(img, kernel, 3);
    box_blur_delete(kernel);
}

void bmp24_gaussianBlur(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return ;
    }
    float **kernel = gaussian_blur_new();
    bmp24_apply_convolution(img, kernel, 3);
    gaussian_blur_delete(kernel);
}

void bmp24_outline(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return ;
    }
    float **kernel = outline_new();
    bmp24_apply_convolution(img, kernel, 3);
    outline_delete(kernel);
}

void bmp24_emboss(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return ;
    }
    float **kernel = emboss_new();
    bmp24_apply_convolution(img, kernel, 3);
    emboss_delete(kernel);
}

void bmp24_sharpen(t_bmp24 *img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return ;
    }
    float **kernel = sharpen_new();
    bmp24_apply_convolution(img, kernel, 3);
    sharpen_delete(kernel);
}

void bmp24_equalize(t_bmp24 * img) {
    if (img == NULL) {
        printf("NULL image passed\n");
        return ;
    }
    t_yuv **yuv = (t_yuv**)malloc(sizeof(t_yuv *) * img->height);
    if (!yuv) {
        perror("erreur");
        return ;
    }
    for (int i = 0; i < img->height; i++) {
        yuv[i] = (t_yuv*)malloc(sizeof(t_yuv) * img->width);
        if (!yuv[i]) {
            perror("erreur");
            return ;
        }
    }

    // Conversion RGB => YUV
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            yuv[i][j].y = 0.299*img->data[i][j].red + 0.587*img->data[i][j].green + 0.114*img->data[i][j].blue;
            yuv[i][j].u = -0.14713*img->data[i][j].red - 0.28886*img->data[i][j].green + 0.436*img->data[i][j].blue;
            yuv[i][j].v = 0.615*img->data[i][j].red - 0.51499*img->data[i][j].green - 0.10001*img->data[i][j].blue;
        }
    }

    // Calculer l’histogramme de la composante Y.
    int histogram[256] = {0};
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            int y_index = (int)round(yuv[i][j].y);
            if (y_index >= 0 && y_index < 256) {
                histogram[y_index]++;
            }
        }
    }
    // Calculer l’histogramme cumulé et normaliser la CDF.
    double_t cdf[256] = {0};
    // Calcul histogramme Cumulé
    double cdf_min = 0;
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + histogram[i];
        if (cdf[i] < cdf_min) {
            cdf_min = cdf[i];
        }
    }
    // Normaliser la CDF
    int hist_eq[256] = {0};
    int nb_pixel = img->height * img->width;
    for (int i = 0; i < 256; i++) {
        hist_eq[i] = round(((cdf[i]-cdf_min)/(nb_pixel-cdf_min)) * 255);
    }

    //Appliquer l’égalisation d’histogramme à la composante Y
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            yuv[i][j].y = hist_eq[(int)round(yuv[i][j].y)];
        }
    }

    // Conversion YUV => RGB
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            double_t red = yuv[i][j].y + 1.13983*yuv[i][j].v;
            double_t green = yuv[i][j].y - 0.39465*yuv[i][j].u - 0.58060*yuv[i][j].v;
            double_t blue = yuv[i][j].y + 2.03211*yuv[i][j].u;
            img->data[i][j].red = (uint8_t)fmax(0, fmin(255, round(red)));
            img->data[i][j].green = (uint8_t)fmax(0, fmin(255, round(green)));
            img->data[i][j].blue = (uint8_t)fmax(0, fmin(255, round(blue)));
        }
    }

    for (int i = 0; i < img->height; i++) {
        free(yuv[i]);
    }
    free(yuv);
    yuv = NULL;
}