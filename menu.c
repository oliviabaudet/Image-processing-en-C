#include <stdio.h>
#include <stdlib.h>

#include "bmp8.h"
#include "bmp24.h"
#include "kernels.h"
#include "menu.h"


int menu_filtre_bmp8(t_bmp8 *image) {
    int quitter = 0;
    float **kernel = NULL;
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
        printf("8. Relief\n");
        printf("9. Egalisation d'histogramme\n");
        printf("10. Retourner au menu précédent\n");
        int selection = -1;
        printf("Votre choix: ");
        do {
            printf("Entrez un nombre entre 1 et 10 :\n");
            scanf("%d", &selection);
        } while ((selection < 1) || (selection > 10));

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
            printf("Filtre Flou.\n");
            kernel = box_blur_new();
            bmp8_applyFilter(image, kernel, 3);
            box_blur_delete(kernel);
            kernel = NULL;
            break;
        case 5:
            printf("Filtre Flou gaussien.\n");
            kernel = gaussian_blur_new();
            bmp8_applyFilter(image, kernel, 3);
            gaussian_blur_delete(kernel);
            kernel = NULL;
            break;
        case 6:
            printf("Filtre Netteté.\n");
            kernel = sharpen_new();
            bmp8_applyFilter(image, kernel, 3);
            sharpen_delete(kernel);
            kernel = NULL;
            break;
        case 7:
            printf("Filtre Contours.\n");
            kernel = outline_new();
            bmp8_applyFilter(image, kernel, 3);
            outline_delete(kernel);
            kernel = NULL;
            break;
        case 8:
            printf("Filtre Relief.\n");
            kernel = emboss_new();
            bmp8_applyFilter(image, kernel, 3);
            emboss_delete(kernel);
            kernel = NULL;
            break;
        case 9:
            bmp8_equalize(image);
            printf("Egalisateur d'histogramme appliqué avec succès !\n");
            break;
        case 10:
            quitter = 1;
            break;
        default:
            printf("Erreur : choix invalide.\n");
        }
    }
    return 0;
}

int menu_filtre_bmp24(t_bmp24 *image) {
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
        printf("8. Relief\n");
        printf("9. Egalisation d'histogramme\n");
        printf("10. Retourner au menu précédent\n");
        int selection = -1;
        printf("Votre choix: ");
        scanf("%d", &selection);
        while ((selection < 1) || (selection > 10)) {
            printf("Entrez un nombre entre 1 et 10 :\n");
            scanf("%d", &selection);
        }

        switch (selection) {
        case 1:
            bmp24_negative(image);
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
                bmp24_brightness(image, value);
                printf("Filtre Luminosité appliqué avec succès !\n");
                break;
        }
        case 3:
            bmp24_grayscale(image);
            break;
        case 4:
            bmp24_boxBlur(image);
            printf("Filtre Flou.\n");
            break;
        case 5:
            bmp24_gaussianBlur(image);
            printf("Filtre Flou gaussien.\n");
            break;
        case 6:
            bmp24_sharpen(image);
            printf("Filtre Netteté.\n");
            break;
        case 7:
            bmp24_outline(image);
            printf("Filtre Contours.\n");
            break;
        case 8:
            bmp24_emboss(image);
            printf("Filtre Relief.\n");
            break;
        case 9:
            bmp24_equalize(image);
            printf("Egalisateur d'histogramme appliqué avec succès !\n");
            break;
        case 10:
            quitter = 1;
            break;
        default:
            printf("Erreur : choix invalide.\n");
        }
    }
    return 0;
}

int menu_bmp8() {
    char chemin[128];
    t_bmp8 *image = NULL;
    int exit = 0;
    while (image == NULL) {
        printf("Chemin du fichier : ");
        scanf("%s", chemin);
        image = bmp8_loadImage(chemin);
        if (image == NULL) {
            printf("Erreur de chargement de l'image.\n");
        } else {
            printf("Image chargée avec succès !\n");
        }
    }
    while (!exit) {
        printf("\nVeuillez choisir une option :\n");
        printf("1. Sauvegarder une image\n");
        printf("2. Appliquer un filtre\n");
        printf("3. Afficher les informations de l'image\n");
        printf("4. Retour au menu principal\n");

        int choix = -1;
        printf("Votre choix : ");
        scanf("%d", &choix);
        while (choix < 1 || choix > 4) {
            printf("Veuillez choisir un nombre entre 1 et 4 : \n");
            scanf("%d", &choix);
        }

        switch (choix) {
            case 1:
                printf("Chemin du fichier de sauvegarde : ");
                scanf("%s", chemin);
                bmp8_saveImage(chemin, image);
                printf("Image sauvegardée avec succès !\n");
                break;
            case 2:
                menu_filtre_bmp8(image);
                break;
            case 3:
                bmp8_printInfo(image);
                break;
            case 4:
                exit = 1;
                break;
            default:
                printf("Erreur : choix invalide.\n");
        }
    }
    return 0;
}

int menu_bmp24() {
    char chemin[128];
    t_bmp24 *image = NULL;
    int exit = 0;
    while (image == NULL) {
        printf("Chemin du fichier : ");
        scanf("%s", chemin);
        image = bmp24_loadImage(chemin);
        if (image == NULL) {
            printf("Erreur de chargement de l'image.\n");
        } else {
            printf("Image chargée avec succès !\n");
        }
    }
    while (!exit) {
        printf("\nVeuillez choisir une option :\n");
        printf("1. Sauvegarder une image\n");
        printf("2. Appliquer un filtre\n");
        printf("3. Afficher les informations de l'image\n");
        printf("4. Retour au menu principal\n");

        int choix = -1;
        printf("Votre choix : ");
        scanf("%d", &choix);
        while (choix < 1 || choix > 4) {
            printf("Veuillez choisir un nombre entre 1 et 4 : \n");
            scanf("%d", &choix);
        }

        switch (choix) {
            case 1:
                printf("Chemin du fichier de sauvegarde : ");
                scanf("%s", chemin);
                bmp24_saveImage(image, chemin);
                printf("Image sauvegardée avec succès !\n");
                break;
            case 2:
                menu_filtre_bmp24(image);
                break;
            case 3:
                bmp24_dump(image);
                break;
            case 4:
                exit = 1;
                break;
            default:
                printf("Erreur : choix invalide.\n");
        }
    }
    return 0;
}

int menu_principal() {
    int fin = 0;
    while (!fin) {
        printf("Bienvenue dans le menu principal !\n");
        printf("Veuillez choisir une option :\n");
        printf("1. Ouvrir une image en noir et blanc (8 bits).\n");
        printf("2. Ouvrir une image en couleur (24 bits).\n");
        printf("3. Quitter.\n");
        int choix = -1;
        printf("Votre choix : ");
        scanf("%d", &choix);
        while (choix < 1 || choix > 3) {
            printf("Veuillez choisir un nombre entre 1 et 3 : \n");
            scanf("%d", &choix);
        }
        switch (choix) {
            case 1:
                menu_bmp8();
                break;
            case 2:
                menu_bmp24();
                break;
            case 3:
                printf("Au revoir !\n");
                fin = 1;
                break;
            default:
                printf("Erreur : choix invalide.\n");
                break;
        }
    }
}