#include <stdio.h>

#include "bmp8.h"
#include "menu.h"



int menu_filtre() {
    char chemin[128];
    t_bmp8 *image = NULL;
    int quitter = 1;
    while (quitter) {
        printf("Veuillez choisir un filtre : \n");
        printf("1. Négatif\n");
        printf("2. Luminosité\n");
        printf("3. Binarisation\n");
        printf("4. Flou\n");
        printf("5. Flou gaussien\n");
        printf("6. Netteté\n");
        printf("7. Contours\n");
        printf("8. Relief");
        printf("9. Retourner au menu précédent\n");
        int selection = -1;
        printf("Votre choix: ");
        scanf("%d", &selection );
        switch (selection) {
            case 1:
                printf("Chemin du fichier : \n");
                scanf("%s", chemin);
                bmp8_negative(image);
                printf("Filtre appliqué avec succès !");
                break;
            case 2:
                printf("Chemin du fichier : \n");
                scanf("%s", chemin);
                int value = 50;
                bmp8_brightness(image, value);
                printf("Filtre appliqué avec succès !");
                break;
            case 3:
                printf("Chemin du fichier : \n");
                scanf("%s", chemin);
                bmp8_threshold(image, 128);
                printf("Filtre appliqué avec succès !");
                break;
            case 4:
                printf("Filtre appliqué avec succès !");
                break;
            case 5:
                printf("Filtre appliqué avec succès !");
                break;
            case 6:
                printf("Filtre appliqué avec succès !");
                break;
            case 7:
                printf("Filtre appliqué avec succès !");
                break;
            case 8:
                quitter = 0;
                break;
            default:
                printf("Erreur\n");
        }
    }
    return 0;
}

int menu_principal() {
    char chemin[128];
    t_bmp8 *image = NULL;
    int exit = 1;
    while (exit) {
        printf("Veuillez choisir une option :\n");
        printf("1. Ouvrir une image\n");
        printf("2. Sauvegarder une image\n");
        printf("3. Appliquer un filtre\n");
        printf("4. Afficher les informations de l'image\n");
        printf("5. Quitter\n");
        int choix = -1;
        printf("Votre choix : ");
        scanf("%d", &choix );
        switch (choix) {
            case 1:
                printf("Chemin du fichier : \n");
                scanf("%s", chemin);
                image = bmp8_loadImage(chemin);
                if (image == NULL) {
                    printf("Error loading image\n");
                    return -1;
                }
                printf("Image chargée avec succès !");
                break;
            case 2:
                printf("Chemin du fichier : \n");
                scanf("%s", chemin);
                bmp8_saveImage(chemin, image);
                break;
            case 3:
                menu_filtre();
                break;
            case 4:
                bmp8_printInfo(image);
                break;
            case 5:
                exit = 0;
                break;
            default:
                printf("Erreur\n");
        }
    }
    return 0;
}


// 3. Appliquer un filtre
// 5. Quitter
// >>> Votre choix : 3
// Veuillez choisir un filtre :
// 1. Négatif
// 2. Luminosité
// 3. Binarisation
// 4. Flou
// 5. Flou gaussien
// 5. Netteté
// 6. Contours
// 7. Relief
// 8. Retourner au menu précédent
// >>> Votre choix : 1
// Filtre appliqué avec succès !
// Veuillez choisir une option :
// 1. Ouvrir une image
// 2. Sauvegarder une image
// 3. Appliquer un filtre
// 4. Afficher les informations de l'image
// 5. Quitter
// >>> Votre choix : 2
// Chemin du fichier : barbara_gray_negatif.bmp
// Image sauvegardée avec succès !
// Veuillez choisir une option :
// 1. Ouvrir une image
// 2. Sauvegarder une image
// 3. Appliquer un filtre
// 4. Afficher les informations de l'image
// 5. Quitter
// >>> Votre choix : 5
