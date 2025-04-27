#include "bmp24.h"
#include <stdio.h>
#include <stdlib.h>

t_pixel ** bmp24_allocateDataPixels (int width, int height) {
  t_pixel ** pixels = malloc(sizeof (t_pixel *) * height);
  if (!pixels) {
    perror("erreur");
    return NULL;
}

for (int i = 0; i < height; i++) {
  pixels[i] = malloc (sizeof (t_pixel) * width);
  if (!pixels[i]) {
    perror("erreur");
    return NULL;
  }
}
return pixels;
}

void bmp24_freeDataPixels (t_pixel ** pixels, int height) {
  if (pixels) {
    for (int i = 0; i < height; i++) {
      free(pixels[i]);
    }
    free(pixels);
  }
}

t_bmp24 * bmp24_allocate (int width, int height, int colorDepth) {
  t_bmp24 * img = (t_bmp24 *) malloc(sizeof(t_bmp24));
  if (!img) {
    perror("erreur");
    return NULL;
  }

  img->width = width;
  img->height = height;
  img->colorDepth = colorDepth;
  img->data = bmp24_allocateDataPixels (width, height);

  if (!img->data) {
      free(img);
      return NULL;
  }
  return img;
}

void bmp24_free (t_bmp24 * img) {
  if (img->data) {
    bmp24_freeDataPixels (img->data, img->height);
    free(img->data);
  }
}


void file_rawRead (uint32_t position, void * buffer, uint32_t size, size_t n, FILE * file) {
fseek(file, position, SEEK_SET);
fread(buffer, size, n, file);
}


void file_rawWrite (uint32_t position, void * buffer, uint32_t size, size_t n, FILE * file) {
fseek(file, position, SEEK_SET);
fwrite(buffer, size, n, file);
}


void bmp24_readPixelValue (t_bmp24 * img, int x, int y, FILE * file) {
    fread(&img->data[y][x].blue, 1, 1, file);
    fread(&img->data[y][x].green, 1, 1, file);
    fread(&img->data[y][x].red, 1, 1, file);
}

void bmp24_readPixelData (t_bmp24 * img, FILE * file) {
    fseek(file, img->header.offset, SEEK_SET);
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            bmp24_readPixelValue(img, x, y, file);
        }
    }
}


void bmp24_writePixelValue (t_bmp24 * img, int x, int y, FILE * file) {
    fwrite(&img->data[y][x].blue, 1, 1, file);
    fwrite(&img->data[y][x].green, 1, 1, file);
    fwrite(&img->data[y][x].red, 1, 1, file);
}

void bmp24_writePixelData (t_bmp24 * img, FILE * file) {
    fseek(file, img->header.offset, SEEK_SET);
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            bmp24_writePixelValue(img, x, y, file);
        }
    }
}

void bmp24_negative (t_bmp24 * img) {
    for (int i = 0; i < img->height; i++) {
      for (int j = 0; j < img->width; j++) {
        img->data[i][j].red = 255 - img->data[i][j].red;
        img->data[i][j].green = 255 - img->data[i][j].green;
        img->data[i][j].blue = 255 - img->data[i][j].blue;
      }
    }
}

void bmp24_grayscale (t_bmp24 * img) {
  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
        uint8_t gray = (img->data[i][j].red + img->data[i][j].green + img->data[i][j].blue) / 3;
        img->data[i][j].red = img->data[i][j].green = img->data[i][j].blue = gray;
    }
  }
}