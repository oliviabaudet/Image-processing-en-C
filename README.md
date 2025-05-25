Image Processing en C
TI202 - Algorithmique et Structures de Données 1
Baudet Olivia – Antoszczyk Sara


Description : 

Ce projet, réalisé en langage C, consiste à implémenter un programme de traitement d’images au format BMP. Il y a deux types d’images :

- bmp8 : images en niveaux de gris (8 bits)
- bmp24 : images en couleurs (24 bits).

Le programme permet : 

- la lecture et la sauvegarde d’images BMP
- l’application de transformations sur les images (netteté, luminosité)
- l’égalisation d’histogramme


Compilation :

Le fichier main.c utilise un menu pour permettre à l’utilisateur de naviguer entre les différentes fonctionnalités. Le main.c fait appel aux fonctions définies dans menu.c via le menu.h. Le menu.c définit toutes les fonctions et Le menu.h appellent toutes ces fonctions

Voici ce que le menu affiche dans le terminal :

Veuillez choisir une option :
1. Ouvrir une image
2. Sauvegarder une image
3. Appliquer un filtre
4. Afficher les informations de l'image
5. Quitter
Votre choix :


Ensemble de fonctionnalités implémentées :

Partie 1 : Image 8 bits en niveaux de gris : Représentation simplifiée d’une image et familiarisation avec les opérations de base.

- chargement et sauvegarde d’une image bmp 8 bits
- affichage d’informations ( taille…)
- application de filtres (luminosité, flou, contours, relief…)

fichier fourni : barbara_gray.bmp


Partie 2 : Image 24 bits et gestion des images en couleur : Représentation plus complexe d’une image et extension des opérations de base aux images en couleur 

- chargement et sauvegarde d’une image bmp 24 bits
- application de filtres ( luminosité, conversion en niveaux de gris, négatif…)

fichier fourni : flowers_color.bmp


Partie 3 : Égalisation d’histogramme : Fonctionnalités avancées et améliorations.

- calcul de l’histogramme
- calcul de la CDF (Fonction de Distribution Cumulative) dans l’histogramme
- égalisation de l’histogramme


Ensemble des bugs connus :

- L’égalisation d’histogramme en couleur peut dégrader les couleurs de l’image.

- Les filtres ne s’appliquent pas aux bords de l’image pour éviter d’accéder à des pixels inexistants.

