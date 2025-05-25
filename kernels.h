#ifndef KERNELS_H
#define KERNELS_H

/**
 * @brief Crée un nouveau noyau de filtre d'accentuation (sharpen)
 * @return Pointeur vers un tableau 2D contenant le noyau d'accentuation
 */
float **sharpen_new();

/**
 * @brief Libère la mémoire allouée pour un noyau d'accentuation
 * @param kernel Pointeur vers le noyau à libérer
 */
void sharpen_delete(float **kernel);

/**
 * @brief Crée un nouveau noyau de flou uniforme (box blur)
 * @return Pointeur vers un tableau 2D contenant le noyau de flou uniforme
 */
float **box_blur_new(void);

/**
 * @brief Libère la mémoire allouée pour un noyau de flou uniforme
 * @param kernel Pointeur vers le noyau à libérer
 */
void box_blur_delete(float **kernel);

/**
 * @brief Crée un nouveau noyau de flou gaussien
 * @return Pointeur vers un tableau 2D contenant le noyau de flou gaussien
 */
float **gaussian_blur_new(void);

/**
 * @brief Libère la mémoire allouée pour un noyau de flou gaussien
 * @param kernel Pointeur vers le noyau à libérer
 */
void gaussian_blur_delete(float **kernel);

/**
 * @brief Crée un nouveau noyau de détection de contours
 * @return Pointeur vers un tableau 2D contenant le noyau de détection de contours
 */
float **outline_new(void);

/**
 * @brief Libère la mémoire allouée pour un noyau de détection de contours
 * @param kernel Pointeur vers le noyau à libérer
 */
void outline_delete(float **kernel);

/**
 * @brief Crée un nouveau noyau d'effet relief (emboss)
 * @return Pointeur vers un tableau 2D contenant le noyau d'effet relief
 */
float **emboss_new(void);

/**
 * @brief Libère la mémoire allouée pour un noyau d'effet relief
 * @param kernel Pointeur vers le noyau à libérer
 */
void emboss_delete(float **kernel);



#endif //KERNELS_H