#ifndef BMP24_H
#define BMP24_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Constantes pour les offsets des champs de l'en-tête BMP
#define BITMAP_MAGIC 0x00 // offset 0
#define BITMAP_SIZE 0x02 // offset 2
#define BITMAP_OFFSET 0x0A // offset 10
#define BITMAP_WIDTH 0x12 // offset 18
#define BITMAP_HEIGHT 0x16 // offset 22
#define BITMAP_DEPTH 0x1C // offset 28
#define BITMAP_SIZE_RAW 0x22 // offset 34

// Constante pour le type de fichier BMP
#define BMP_TYPE 0x4D42 // 'BM' en hexadécimal

// Constantes pour les tailles des champs de l'en-tête BMP
#define HEADER_SIZE 0x0E // 14 octets
#define INFO_SIZE 0x28 // 40 octets

//Constantes pour les valeurs de profondeur de couleur
#define DEFAULT_DEPTH 0x18 // 24

//Désactivation du padding des structures
//Le compilateur optimise les accès mémoire sur des mots de 32 bits
//Si on ne désactive pas le padding des structures le compilateur va générer du padding entre les types définis dans la structure.
//Il faut donc désactiver le padding pour que les structures soient bien définies.
#pragma pack(1)

typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} t_bmp_header;


typedef struct {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t imagesize;
    int32_t xresolution;
    int32_t yresolution;
    uint32_t ncolors;
    uint32_t importantcolors;
} t_bmp_info;


typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} t_pixel;

typedef struct {
    double_t y;
    double_t u;
    double_t v;
} t_yuv;

typedef struct {
  t_bmp_header header; //En-tête de l’image
  t_bmp_info header_info; //Informations de l’image
  int width; //Largeur de l’image
  int height; //Hauteur de l’image
  int colorDepth; //Profondeur de couleur de l’image
  t_pixel **data; //Données de l’image
} t_bmp24;

// Prototypes de fonction

/**
 * @brief Affiche les informations de l'image BMP
 * @param img Pointeur vers la structure de l'image BMP
 */
void bmp24_dump(t_bmp24 *img);

/**
 * @brief Alloue de la mémoire pour la matrice de pixels
 * @param width Largeur de l'image en pixels
 * @param height Hauteur de l'image en pixels
 * @return Pointeur vers la matrice de pixels allouée
 */
t_pixel ** bmp24_allocateDataPixels (int width, int height);

/**
 * @brief Libère la mémoire allouée pour la matrice de pixels
 * @param pixels Pointeur vers la matrice de pixels à libérer
 * @param height Hauteur de l'image en pixels
 */
void bmp24_freeDataPixels (t_pixel ** pixels, int height);

/**
 * @brief Alloue la mémoire pour une nouvelle structure d'image BMP
 * @param width Largeur de l'image en pixels
 * @param height Hauteur de l'image en pixels
 * @param colorDepth Profondeur de couleur en bits
 * @return Pointeur vers la structure d'image BMP allouée
 */
t_bmp24 * bmp24_allocate (int width, int height, int colorDepth);

/**
 * @brief Libère la mémoire allouée pour une structure d'image BMP
 * @param img Pointeur vers la structure d'image BMP à libérer
 */
void bmp24_free (t_bmp24 * img);

/**
 * @brief Charge une image BMP depuis un fichier
 * @param filename Nom du fichier à charger
 * @return Pointeur vers la structure d'image BMP chargée
 */
t_bmp24 * bmp24_loadImage (const char * filename);

/**
 * @brief Sauvegarde une image BMP dans un fichier
 * @param img Pointeur vers la structure d'image BMP à sauvegarder
 * @param filename Nom du fichier de destination
 */
void bmp24_saveImage (t_bmp24 * img, const char * filename);

/**
* @brief Positionne le curseur de fichier à la position position dans le fichier file,
* puis lit n éléments de taille size dans buffer.
* @param position La position à partir de laquelle il faut lire dans file.
* @param buffer Le buffer pour stocker les données lues.
* @param size La taille de chaque élément à lire.
* @param n Le nombre d'éléments à lire.
* @param file Le descripteur de fichier dans lequel il faut lire.
* @return void
*/
void file_rawRead (uint32_t position, void * buffer, uint32_t size, size_t n, FILE * file);
/**
* @brief Positionne le curseur de fichier à la position position dans le fichier file,
* puis écrit n éléments de taille size depuis le buffer.
* @param position La position à partir de laquelle il faut écrire dans file.
* @param buffer Le buffer contenant les éléments à écrire.
* @param size La taille de chaque élément à écrire.
* @param n Le nombre d'éléments à écrire.
* @param file Le descripteur de fichier dans lequel il faut écrire.
* @return void
*/
void file_rawWrite (uint32_t position, void * buffer, uint32_t size, size_t n, FILE * file);

/**
 * @brief Lit la valeur d'un pixel à une position donnée
 * @param image Pointeur vers la structure d'image BMP
 * @param x Coordonnée X du pixel
 * @param y Coordonnée Y du pixel
 * @param file Pointeur vers le fichier source
 */
void bmp24_readPixelValue (t_bmp24 * image, int x, int y, FILE * file);

/**
 * @brief Lit toutes les données des pixels d'une image
 * @param image Pointeur vers la structure d'image BMP
 * @param file Pointeur vers le fichier source
 */
void bmp24_readPixelData (t_bmp24 * image, FILE * file);

/**
 * @brief Écrit la valeur d'un pixel à une position donnée
 * @param image Pointeur vers la structure d'image BMP
 * @param x Coordonnée X du pixel
 * @param y Coordonnée Y du pixel
 * @param file Pointeur vers le fichier de destination
 */
void bmp24_writePixelValue (t_bmp24 * image, int x, int y, FILE * file);

/**
 * @brief Écrit toutes les données des pixels d'une image
 * @param image Pointeur vers la structure d'image BMP
 * @param file Pointeur vers le fichier de destination
 */
void bmp24_writePixelData (t_bmp24 * image, FILE * file);

/**
 * @brief Applique un effet négatif à l'image
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_negative (t_bmp24 * img);

/**
 * @brief Convertit l'image en niveaux de gris
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_grayscale (t_bmp24 * img);

/**
 * @brief Ajuste la luminosité de l'image
 * @param img Pointeur vers la structure d'image BMP
 * @param value Valeur de l'ajustement de luminosité
 */
void bmp24_brightness (t_bmp24 * img, int value);

/**
 * @brief Applique un flou de type "box blur" à l'image
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_boxBlur(t_bmp24 *img);

/**
 * @brief Applique un flou gaussien à l'image
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_gaussianBlur(t_bmp24 *img);

/**
 * @brief Détecte les contours de l'image
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_outline(t_bmp24 *img);

/**
 * @brief Applique un effet de relief à l'image
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_emboss(t_bmp24 *img);

/**
 * @brief Applique un effet d'accentuation (sharpening) à l'image
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_sharpen(t_bmp24 *img);

/**
 * @brief Égalise l'histogramme de l'image pour améliorer le contraste
 * @param img Pointeur vers la structure d'image BMP
 */
void bmp24_equalize(t_bmp24 * img);

#endif