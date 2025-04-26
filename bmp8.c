#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>

#include "bmp8.h"

#include <stdlib.h>


t_bmp8* bmp8_loadImage(const char * filename) {
    FILE *file = NULL;

    if (filename == NULL) {
        return NULL;
    }

    file = fopen(filename, "rb");
    if (!file) {
        printf("Error opening file '%s': %s\n", filename, strerror(errno));
        return NULL;
    }
    printf("Loading %s\n", filename);
    t_bmp8* bmp8 = calloc(sizeof(t_bmp8), 1);
    if (bmp8 == NULL) {
        perror("bmp8_loadImage");
        fclose(file);
        return NULL;
    }

    size_t ret = fread(bmp8->header, 1, HEADER_SIZE, file);
    if (ret != HEADER_SIZE) {
        printf("Error reading header from file '%s' expected: %d, got: %zd\n", filename, HEADER_SIZE, ret);
    }

    bmp8->width = *(unsigned int *)&(bmp8->header)[18];
    bmp8->height = *(unsigned int *)&(bmp8->header)[22];
    bmp8->colorDepth = *(unsigned short *)&(bmp8->header)[28];
    bmp8->dataSize = *(unsigned int *)&(bmp8->header)[34];

    if (bmp8->dataSize == 0) {
        // If dataSize is 0 then image is not compressed
        unsigned int compression = *(unsigned int *)&(bmp8->header)[30];
        if (compression == 0) {
            // Not compressed
            bmp8->dataSize = bmp8->width * bmp8->height;
        } else {
            printf("fichier compressé et data size à 0\n");
        }
    }

    ret = fread(bmp8->colorTable, 1, COLOR_TABLE_SIZE, file);
    if (ret != COLOR_TABLE_SIZE) {
        printf("Error reading colorTable from file '%s' expected: %d, got: %zd\n", filename, COLOR_TABLE_SIZE, ret);
    }

    bmp8->data = malloc(bmp8->dataSize);
    if (bmp8->data == NULL) {
        perror("malloc data");
        free(bmp8);
        fclose(file);
        return NULL;
    }

    ret = fread(bmp8->data, 1, bmp8->dataSize, file);
    if (ret != bmp8->dataSize) {
        printf("Error reading data from file '%s' expected: %d, got: %zd\n", filename, bmp8->dataSize, ret);
    }

    fclose(file);
    return bmp8;
}

void bmp8_saveImage(const char * filename, t_bmp8 * img) {
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

    printf("Saving '%s'\n", filename);

    size_t ret = fwrite(img->header, 1, HEADER_SIZE, file);
    if (ret != HEADER_SIZE) {
        printf("Error reading header from file '%s' expected: %d, got: %zd\n", filename, HEADER_SIZE, ret);
    }

    ret = fwrite(img->colorTable, 1, COLOR_TABLE_SIZE, file);
    if (ret != COLOR_TABLE_SIZE) {
        printf("Error reading colorTable from file '%s' expected: %d, got: %zd\n", filename, COLOR_TABLE_SIZE, ret);
    }

    ret = fwrite(img->data, 1, img->dataSize, file);
    if (ret != img->dataSize) {
        printf("Error reading data from file '%s' expected: %d, got: %zd\n", filename, img->dataSize, ret);
    }

    fclose(file);
}

void bmp8_free(t_bmp8 * img) {
    free(img->data);
    free(img);
}

void bmp8_printInfo(t_bmp8 * img) {
    if (img == NULL) {
        printf("img is NULL\n");
        return;
    }
    printf("Image Info:\n");
    printf("\tWidth:\t%d\n", img->width);
    printf("\tHeight:\t%d\n", img->height);
    printf("\tColor Depth:\t%d\n", img->colorDepth);
    printf("\tData Size:\t%d\n", img->dataSize);
}


void bmp8_negative(t_bmp8 * img) {
    if (img == NULL) {
        return;
    }
    for (size_t i = 0; i < img->dataSize; i++) {
        img->data[i] = 255-img->data[i];
    }
}


void bmp8_brightness(t_bmp8 * img, int value) {
    if (img == NULL) {
        return;
    }
    for (size_t i = 0; i < img->dataSize; i++) {
        int somme = img->data[i] + value;
        if (somme > 255) {
            img->data[i] = 255;
        } else if (somme < 0) {
            img->data[i] = 0;
        } else {
            img->data[i] = somme;
        }
    }

}


void bmp8_threshold(t_bmp8 * img, int threshold) {
    if (img == NULL) {
        return;
    }
    for (size_t i = 0; i < img->dataSize; i++) {
        if (img->data[i] >= threshold) {
            img->data[i] = 255;
        } else {
            img->data[i] = 0;
        }
    }
}