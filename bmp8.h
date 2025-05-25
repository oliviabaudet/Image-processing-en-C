#pragma once

//Définition des constantes
#define BMP8_HEADER_SIZE 54
#define COLOR_TABLE_SIZE 1024

/**
 * @brief Structure représentant une image BMP 8-bits
 * 
 * Cette structure contient toutes les informations nécessaires pour manipuler
 * une image au format BMP avec une profondeur de couleur de 8 bits.
 * 
 * @details L'image est stockée avec :
 *  - Un en-tête (header) contenant les informations du fichier
 *  - Une table de couleurs pour la palette
 *  - Les données de l'image
 */
typedef struct {
    /** @brief En-tête du fichier BMP (54 octets) */
    unsigned char header[BMP8_HEADER_SIZE];
    
    /** @brief Table des couleurs (256 * 4 octets = 1024 octets) */
    unsigned char colorTable[COLOR_TABLE_SIZE];
    
    /** @brief Largeur de l'image en pixels */
    unsigned int width;
    
    /** @brief Hauteur de l'image en pixels */
    unsigned int height;
    
    /** @brief Profondeur de couleur (8 bits) */
    unsigned short colorDepth;
    
    /** @brief Taille des données de l'image en octets */
    unsigned int dataSize;
    
    /** @brief Pointeur vers les données de l'image */
    unsigned char *data;
} t_bmp8;

//Prototype des fonctions
/**
 * @brief Charge une image BMP 8-bits depuis un fichier
 * @param filename Le chemin du fichier à charger
 * @return Pointeur vers la structure t_bmp8 contenant l'image chargée, NULL en cas d'erreur
 */
t_bmp8* bmp8_loadImage(const char * filename);

/**
 * @brief Sauvegarde une image BMP 8-bits dans un fichier
 * @param filename Le chemin du fichier où sauvegarder l'image
 * @param img Pointeur vers la structure contenant l'image à sauvegarder
 */
void bmp8_saveImage(const char * filename, t_bmp8 * img);

/**
 * @brief Libère la mémoire allouée pour une image
 * @param img Pointeur vers la structure de l'image à libérer
 */
void bmp8_free(t_bmp8 * img);

/**
 * @brief Affiche les informations de l'image (dimensions, profondeur de couleur, taille)
 * @param img Pointeur vers la structure de l'image
 */
void bmp8_printInfo(t_bmp8 * img);

/**
 * @brief Applique un filtre négatif à l'image
 * @param img Pointeur vers la structure de l'image à modifier
 */
void bmp8_negative(t_bmp8 * img);

/**
 * @brief Modifie la luminosité de l'image
 * @param img Pointeur vers la structure de l'image à modifier
 * @param value Valeur de modification de la luminosité (-255 à +255)
 */
void bmp8_brightness(t_bmp8 * img, int value);

/**
 * @brief Applique un seuillage à l'image pour la binariser
 * @param img Pointeur vers la structure de l'image à modifier
 * @param threshold Valeur de seuil (0-255)
 */
void bmp8_threshold(t_bmp8 * img, int threshold);

/**
 * @brief Applique un filtre de convolution à l'image
 * @param img Pointeur vers la structure de l'image à modifier
 * @param kernel Matrice de convolution à appliquer
 * @param kernelSize Taille de la matrice de convolution (doit être impaire)
 */
void bmp8_applyFilter(t_bmp8 * img, float ** kernel, int kernelSize);

/**
 * @brief Calcule l'histogramme de l'image
 * @param img Pointeur vers la structure de l'image
 * @return Tableau de 256 entiers représentant l'histogramme, NULL en cas d'erreur
 */
unsigned int * bmp8_computeHistogram(t_bmp8 * img);

/**
 * @brief Calcule la fonction de distribution cumulative (CDF) à partir d'un histogramme
 * @param hist Pointeur vers l'histogramme source
 * @return Tableau de 256 entiers représentant la CDF, NULL en cas d'erreur
 */
unsigned int * bmp8_computeCDF(unsigned int * hist);

/**
 * @brief Égalise l'histogramme de l'image pour améliorer le contraste
 * @param img Pointeur vers la structure de l'image à modifier
 */
void bmp8_equalize(t_bmp8 * img);