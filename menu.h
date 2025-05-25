#ifndef MENU_H
#define MENU_H
#include "bmp8.h"

/**
 * @brief Affiche et gère le menu des filtres pour une image BMP 8 bits
 * @param image Pointeur vers l'image BMP 8 bits à traiter
 * @return int Code de retour (0 en cas de succès)
 */
int menu_filtre_bmp8(t_bmp8 *image);

/**
 * @brief Affiche et gère le menu des filtres pour une image BMP 24 bits
 * @param image Pointeur vers l'image BMP 24 bits à traiter
 * @return int Code de retour (0 en cas de succès)
 */
int menu_filtre_bmp24(t_bmp24 *image);

/**
 * @brief Affiche et gère le menu principal pour les images BMP 8 bits
 * @return int Code de retour (0 en cas de succès)
 */
int menu_bmp8();

/**
 * @brief Affiche et gère le menu principal pour les images BMP 24 bits
 * @return int Code de retour (0 en cas de succès)
 */
int menu_bmp24();

/**
 * @brief Affiche et gère le menu principal du programme
 * @return int Code de retour (0 en cas de succès)
 */
int menu_principal(void);
#endif //MENU_H