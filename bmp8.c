//Librairies
#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

//Fichier
#include "bmp8.h"

//Chargement de l'image
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

    bmp8->width = *(unsigned int *)&(bmp8->header)[18]; //Largeur
    bmp8->height = *(unsigned int *)&(bmp8->header)[22]; //Hauteur
    bmp8->colorDepth = *(unsigned short *)&(bmp8->header)[28]; //Profondeur de couleur
    bmp8->dataSize = *(unsigned int *)&(bmp8->header)[34]; //Taille des données

    if (bmp8->dataSize == 0) {
        // Si dataSize est à 0, l'image n'est pas compressée
        unsigned int compression = *(unsigned int *)&(bmp8->header)[30];
        if (compression == 0) {
            //Non compressé
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

//Sauvegarde de l'image
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

//Libère la mémoire allouée
void bmp8_free(t_bmp8 * img) {
    free(img->data);
    free(img);
}

// Affiche les informations de l'image
void bmp8_printInfo(t_bmp8 * img) {
    if (img == NULL) {
        printf("img is NULL\n");
        return;
    }
    printf("Image Info:\n");
    printf("\tWidth:\t%d\n", img->width); //Largeur
    printf("\tHeight:\t%d\n", img->height); //Hauteur
    printf("\tColor Depth:\t%d\n", img->colorDepth); //Profondeur de couleur
    printf("\tData Size:\t%d\n", img->dataSize); //Taille des données
}

//Implémentation des filtres

//Inverse les couleurs de l'image
void bmp8_negative(t_bmp8 * img) {
    if (img == NULL) {
        return;
    }
    for (size_t i = 0; i < img->dataSize; i++) {
        img->data[i] = 255-img->data[i];
    }
}

//Modifie la luminosité
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

//Met l'image en noir et blanc pour un certain seuil
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

//Applique un filtre sur une image en niveaux de gris
void bmp8_applyFilter(t_bmp8 * img, float ** kernel, int kernelSize) {
    if (img == NULL) {
        printf("img is NULL\n");
        return;
    }
    if (kernel == NULL) {
        printf("kernel is NULL\n");
        return;
    }
    unsigned char *img_result = malloc(img->dataSize);
    if (img_result == NULL) {
        perror("malloc data");
        return;
    }

    int n = kernelSize/2;
    for (int y = 1; y < img->height - 2; y++) {
        for (int x = 1; x < img->width - 2; x++) {
            float pixel = 0;
            for (int ky = -n; ky <= n; ky++) {
                int posy = y + ky;
                for (int kx = -n; kx <= n; kx++) {
                    int posx = x + kx;
                    float current = img->data[posx + posy * img->width];
                    float coeff = kernel[ky + n][kx + n];
                    pixel += coeff * current;
                }
            }
            img_result[x + y * img->width] = (unsigned char)pixel;
        }
    }

    free(img->data);
    img->data = img_result;
}

unsigned int * bmp8_computeHistogram(t_bmp8 * img) {
    if (img == NULL) {
        printf("img is NULL\n");
        return NULL;
    }
    unsigned int *hist = calloc(256, sizeof(unsigned int));
    for (size_t i = 0; i < img->dataSize; i++) {
        hist[img->data[i]]++;
    }
    return hist;
}

unsigned int * bmp8_computeCDF(unsigned int * hist) {
    if (hist == NULL) {
        printf("hist is NULL\n");
        return NULL;
    }
    unsigned int cdf_min = 0;
    for (int i = 0; i < 256; i++) {
        if (hist[i] < cdf_min) {
            cdf_min = hist[i];
        }
    }
    unsigned int *cdf = calloc(256, sizeof(unsigned int));
    for (int i = 0; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
        if (cdf[i] < cdf_min) {
            cdf_min = cdf[i];
        }
    }
    for (int i = 0; i < 256; i++) {
        cdf[i] = cdf[i] - cdf_min;
        cdf[i] = cdf[i] * 255 / (cdf[255] - cdf_min);
    }
    return cdf;
}

void bmp8_equalize(t_bmp8 * img) {
    if (img == NULL) {
        printf("img is NULL\n");
        return;
    }
    unsigned int *hist = bmp8_computeHistogram(img);
    unsigned int *hist_eq = bmp8_computeCDF(hist);
    for (size_t i = 0; i < img->dataSize -1; i++) {
        img->data[i] = hist_eq[img->data[i]];
    }
    free(hist);
    free(hist_eq);
}