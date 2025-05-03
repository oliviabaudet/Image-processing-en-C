#pragma once

#define HEADER_SIZE 54
#define COLOR_TABLE_SIZE 1024

typedef struct {
    unsigned char header[HEADER_SIZE];
    unsigned char colorTable[COLOR_TABLE_SIZE];
    unsigned char * data;

    unsigned int width;
    unsigned int height;
    unsigned int colorDepth;
    unsigned int dataSize;
} t_bmp8;

t_bmp8 * bmp8_loadImage(const char * filename);
void bmp8_saveImage(const char * filename, t_bmp8 * img);
void bmp8_free(t_bmp8 * img);
void bmp8_printInfo(t_bmp8 * img);

void bmp8_negative(t_bmp8 * img);
void bmp8_brightness(t_bmp8 * img, int value);
void bmp8_threshold(t_bmp8 * img, int threshold);

void bmp8_applyFilter(t_bmp8 * img, float ** kernel, int kernelSize);