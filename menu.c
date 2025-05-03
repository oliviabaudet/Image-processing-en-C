#include <stdio.h>

#include "bmp8.h"
#include "menu.h"


int menu_filtre(t_bmp8 *image) {
    int quitter = 0;
    if (image == NULL) {
        printf("Aucune image chargée !\n");
        return -1;
    }
    while (!quitter) {
        printf("\nVeuillez choisir un filtre : \n");
        printf("1. Négatif\n");
        printf("2. Luminosité\n");
        printf("3. Binarisation\n");
        printf("4. Flou\n");
        printf("5. Flou gaussien\n");
        printf("6. Netteté\n");
        printf("7. Contours\n");
        printf("8. Retourner au menu précédent\n");
        int selection = -1;
        printf("Votre choix: ");
        scanf("%d", &selection);
        while ((selection < 1) || (selection > 8)) {
            printf("Entrez un nombre entre 1 et 8 :\n");
            scanf("%d", &selection);
        }

        switch (selection) {
            case 1:
                bmp8_negative(image);
                printf("Filtre Négatif appliqué avec succès !\n");
                break;
            case 2: {
                int value;
                printf("Entrez la valeur de luminosité (-255 à 255) : ");
                scanf("%d", &value);
                while ((value < -255) || (value > 255)) {
                    printf("Veuillez entrer une valeur entre -255 et 255 : ");
                    scanf("%d", &value);
                }
                bmp8_brightness(image, value);
                printf("Filtre Luminosité appliqué avec succès !\n");
                break;
            }
            case 3:
                int value;
                printf("Entrez la valeur de seuil (0 à 255) : ");
                scanf("%d", &value);
                while ((value < 0) || (value > 255)) {
                    printf("Veuillez entrer une valeur entre 0 et 255 : ");
                    scanf("%d", &value);
                }
                bmp8_threshold(image, value);
                printf("Filtre Binarisation appliqué avec succès !\n");
                break;
            case 4:
                // bmp8_applyFilter(image, flouKernel, taille);
                printf("Filtre Flou (non implémenté ici).\n");
                break;
            case 5:
                printf("Filtre Flou gaussien (non implémenté ici).\n");
                break;
            case 6:
                printf("Filtre Netteté (non implémenté ici).\n");
                break;
            case 7:
                printf("Filtre Contours (non implémenté ici).\n");
                break;
            case 8:
                quitter = 1;
                break;
            default:
                printf("Erreur : choix invalide.\n");
        }
    }
    return 0;
}

int menu_principal() {
    char chemin[128];
    t_bmp8 *image = NULL;
    int exit = 0;

    while (!exit) {
        printf("\nVeuillez choisir une option :\n");
        printf("1. Ouvrir une image\n");
        printf("2. Sauvegarder une image\n");
        printf("3. Appliquer un filtre\n");
        printf("4. Afficher les informations de l'image\n");
        printf("5. Quitter\n");

        int choix = -1;
        printf("Votre choix : ");
        scanf("%d", &choix);
        while (choix < 1 || choix > 5) {
            printf("Veuillez choisir un nombre entre 1 et 5 : \n");
            scanf("%d", &choix);
        }

        switch (choix) {
            case 1:
                printf("Chemin du fichier : ");
                scanf("%s", chemin);
                image = bmp8_loadImage(chemin);
                if (image == NULL) {
                    printf("Erreur de chargement de l'image.\n");
                } else {
                    printf("Image chargée avec succès !\n");
                }
                break;
            case 2:
                if (image == NULL) {
                    printf("Aucune image à sauvegarder.\n");
                } else {
                    printf("Chemin du fichier de sauvegarde : ");
                    scanf("%s", chemin);
                    bmp8_saveImage(chemin, image);
                    printf("Image sauvegardée avec succès !\n");
                }
                break;
            case 3:
                if (image == NULL) {
                    printf("Veuillez d'abord charger une image.\n");
                } else {
                    menu_filtre(image);
                }
                break;
            case 4:
                if (image == NULL) {
                    printf("Aucune image chargée.\n");
                } else {
                    bmp8_printInfo(image);
                }
                break;
            case 5:
                printf("Au revoir !\n");
                exit = 1;
                break;
            default:
                printf("Erreur : choix invalide.\n");
        }
    }
    return 0;
}
