#include "bmp24.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        return;
    }
    if (img == NULL) {
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
    if (img->data) {
        bmp24_freeDataPixels(img->data, img->height);
        free(img);
    }
}


void file_rawRead(uint32_t position, void *buffer, uint32_t size, size_t n, FILE *file) {
    fseek(file, (long)position, SEEK_SET);
    fread(buffer, size, n, file);
}


void file_rawWrite(uint32_t position, void *buffer, uint32_t size, size_t n, FILE *file) {
    fseek(file, (long)position, SEEK_SET);
    fwrite(buffer, size, n, file);
}


void bmp24_readPixelValue(t_bmp24 *img, int x, int y, FILE *file) {
    fread(&img->data[y][x].blue, 1, 1, file);
    fread(&img->data[y][x].green, 1, 1, file);
    fread(&img->data[y][x].red, 1, 1, file);
}

void bmp24_readPixelData(t_bmp24 *img, FILE *file) {
    fseek(file, img->header.offset, SEEK_SET);
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            bmp24_readPixelValue(img, x, y, file);
        }
    }
}


void bmp24_writePixelValue(t_bmp24 *img, int x, int y, FILE *file) {
    fwrite(&img->data[y][x].blue, 1, 1, file);
    fwrite(&img->data[y][x].green, 1, 1, file);
    fwrite(&img->data[y][x].red, 1, 1, file);
}

void bmp24_writePixelData(t_bmp24 *img, FILE *file) {
    fseek(file, img->header.offset, SEEK_SET);
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            bmp24_writePixelValue(img, x, y, file);
        }
    }
}

void bmp24_negative(t_bmp24 *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->data[i][j].red = 255 - img->data[i][j].red;
            img->data[i][j].green = 255 - img->data[i][j].green;
            img->data[i][j].blue = 255 - img->data[i][j].blue;
        }
    }
}

void bmp24_grayscale(t_bmp24 *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            uint8_t gray = (img->data[i][j].red + img->data[i][j].green + img->data[i][j].blue) / 3;
            img->data[i][j].red = img->data[i][j].green = img->data[i][j].blue = gray;
        }
    }
}