#include "airbnb.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Compte le nombre de lignes d'un fichier
int nbLignes(FILE* fichier) {
    int nbLignes = 0;
    char cara;

    while((cara = fgetc(fichier)) != EOF) if (cara == '\n') nbLignes++;
    rewind(fichier);

    return nbLignes;
}

// Affiche les n premiers logements d'un tableau de logements
void afficherTab(logement* tab, int n) {
    printf("accomodates\tbedrooms\tbeds\tprice\t\tdistance\n");
    for (int i = 0; i < n; i++) {
        logement l = tab[i];
        printf("%d\t\t%d\t\t%d\t%f\t%f\n", l.accomodates, l.bedrooms, l.beds, l.price, l.distance);
    }
}

// Parcourt le fichier csv pour remplir le tableau de logements
void remplirTab(logement logementX, logement* tab, FILE* fichier, int tailleTab) {
    char* buffer = (char*) malloc(sizeof(char) * TAILLEMAXBUFFER);
    fgets(buffer, TAILLEMAXBUFFER, fichier); // Pas besoin de l'entête du csv
    for (int i = 0; i < tailleTab; i++) {
        fgets(buffer, TAILLEMAXBUFFER, fichier);

        // Remplissage des champs
        logement l;
        char* sep = ",";

        strtok(buffer, sep); // Pas besoin de l'id du logement

        l.accomodates = atoi(strtok(NULL, sep));
        l.bedrooms = atoi(strtok(NULL, sep));
        strtok(NULL, sep); // On ne considère par le nombre de salles de bain
        l.beds = atoi(strtok(NULL, sep));
        l.price = atof(strtok(NULL, sep));

        // Calcul de la distance
        l.distance = sqrt(pow(logementX.accomodates - l.accomodates, 2) + pow(logementX.bedrooms - l.bedrooms, 2) + pow(logementX.beds - l.beds, 2));

        tab[i] = l;
    }

    free(buffer);
}

// Parcourt le fichier csv pour remplir le tableau de logements sans les distances (pour la partie 2)
void remplirTabSansDistance(logement* tab, FILE* fichier, int tailleTab) {
    char* buffer = (char*) malloc(sizeof(char) * TAILLEMAXBUFFER);
    fgets(buffer, TAILLEMAXBUFFER, fichier); // Pas besoin de l'entête du csv
    for (int i = 0; i < tailleTab; i++) {
        fgets(buffer, TAILLEMAXBUFFER, fichier);

        // Remplissage des champs
        logement l;
        char* sep = ",";

        strtok(buffer, sep); // Pas besoin de l'id du logement

        l.accomodates = atoi(strtok(NULL, sep));
        l.bedrooms = atoi(strtok(NULL, sep));
        strtok(NULL, sep); // On ne considère par le nombre de salles de bain
        l.beds = atoi(strtok(NULL, sep));
        l.price = atof(strtok(NULL, sep));

        tab[i] = l;
    }

    free(buffer);
}

// Mélange le tableau passé en paramètre
void melangerTab(logement* tab, int tailleTab) {
    srand(time(NULL));

    for (int i = tailleTab - 1; i > 0; i--) {
        int j = rand() % i + 1;
        logement tmp = tab[j];
        tab[j] = tab[i];
        tab[i] = tmp;
    }
}

// Calcule la moyenne des prix des n premiers logements du tableau trié
float moyenne(logement* tab, int n) {
    float prixMoyen = 0.0;

    for (int i = 0; i < n; i++) prixMoyen += tab[i].price;

    return prixMoyen/(float) n;
}

// Non demandé : calcule le taux de précision du prix obtenu (en %)
float tauxFiab(logement* tab, int tailleTab, int n) {
    float fiabSomme = 0.0;
    float pireDistance = tab[tailleTab - 1].distance;

    for (int i = 0; i < n; i++) fiabSomme += 1 - tab[i].distance / pireDistance;

    return fiabSomme/(float) n * 100;
}

// Echange deux éléments
void echange(logement* a, logement* b) {
    logement tmp = *a;
    *a = *b;
    *b = tmp;
}

void triRapideAux(logement* tab, int gauche, int droite) {
    if (gauche < droite) {
        int pivot = gauche;
        int i = gauche;
        int j = droite;

        while (i < j) {
            while (tab[i].distance <= tab[pivot].distance && i < droite) i++;
            while (tab[j].distance > tab[pivot].distance) j--;
            if (i < j) echange(&tab[i], &tab[j]);
        }

        echange(&tab[pivot], &tab[j]);
        triRapideAux(tab, gauche, j - 1);
        triRapideAux(tab, j + 1, droite);
    }
}

// Trie le tableau passé en paramètre en fonction de la distance
void triRapide(logement* tab, int tailleTab) {
    triRapideAux(tab, 0, tailleTab - 1);
}

// Remplit le tableau des prédictions pour chaque logement test en fonction des n logements entraînement les plus proches à chaque fois
void remplirPrediction(logement* tabEnt, int tailleTabEnt, logement* tabTest, int tailleTabTest, float* tabPrediction, int n) {

    for (int i = 0; i < tailleTabTest; i++) {
        logement logementTest = tabTest[i];

        for (int j = 0; j < tailleTabEnt; j++) {
            logement logementEnt = tabEnt[j];
            tabEnt[j].distance = sqrt(pow(logementTest.accomodates - logementEnt.accomodates, 2) + pow(logementTest.bedrooms - logementEnt.bedrooms, 2) + pow(logementTest.beds - logementEnt.beds, 2));
        }

        melangerTab(tabEnt, tailleTabEnt);
        triRapide(tabEnt, tailleTabEnt);

        tabPrediction[i] = moyenne(tabEnt, n);
    }
}

// Affiche les n premiers logements d'un tableau de logements, et leur prédiction associée
void afficherTabEtPrediction(logement* tab, float* prediction, int n) {
    printf("accomodates\tbedrooms\tbeds\tprice\tprediction\n");
    for (int i = 0; i < n; i++) {
        logement l = tab[i];
        printf("%d\t\t%d\t\t%d\t%.2f\t%.2f\n", l.accomodates, l.bedrooms, l.beds, l.price, prediction[i]);
    }
}

float calculMAE(logement* tab, float* prediction, int taille) {
    float mae = 0.0;

    for (int i = 0; i < taille; i++) mae += fabs(tab[i].price - prediction[i]);
    
    return mae/(float) taille;
}

void partie1() {
    // Logement fictif X pour lequel on va estimer le prix
    logement logementX;
    printf("Veuillez renseigner les informations suivantes sur le logement pour lequel vous voulez estimer le prix.\nNombre d'hôtes :\n");
    int retCode1 = scanf("%d", &logementX.accomodates);
    if (!retCode1) exit(11);

    printf("Nombre de chambres :\n");
    int retCode2 = scanf("%d", &logementX.bedrooms);
    if (!retCode2) exit(12);

    printf("Nombre de lits :\n");
    int retCode3 = scanf("%d", &logementX.beds);
    if (!retCode3) exit(13);

    FILE* fichier = fopen("data/airbnb_donnees_propre.csv", "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    int nLignes = nbLignes(fichier);
    int tailleTab = nLignes - 1; // On retire 1 pour l'entête du csv
    logement tableauLogements[tailleTab];

    // Remplissage du tableau
    remplirTab(logementX, tableauLogements, fichier, tailleTab);
    melangerTab(tableauLogements, tailleTab);
    triRapide(tableauLogements, tailleTab);

    printf("Le prix estimé obtenu avec les %d logements les plus proches du logement X est de %.2f€ (obtenu avec un fiabilité de %.2f%%)\n", NOMBRELOGEMENTS, moyenne(tableauLogements, NOMBRELOGEMENTS), tauxFiab(tableauLogements, tailleTab, NOMBRELOGEMENTS));

    fclose(fichier);
}

// Affiche une barre de chargement pour informer où la recherche en est
void affichageChargement(int min, int max, int k, int etape) {
    system("clear");
    printf("Recherche %1$d par %1$d sur les entiers dans [%2$d, %3$d] (k = %4$d)\n" ROUGE "[", etape ? 1 : PAS, min, etape ? max - 1 : max, k - 1);

    float pos = (float) (k - min)/ (float) (max - min) * TAILLEBARRECHARGEMENT;
    int iterEtape1 = (FIN - DEBUT)/PAS; // Nombre d'itérations effectuées pendant l'étape 1
    int iterEtape2 = PAS - 2;
    int nbIterTotal = iterEtape1 + iterEtape2;

    if (!etape) pos *= (float) iterEtape1/ (float) nbIterTotal; // Si on est dans la première partie 
    else { // Si on est dans la deuxième
        pos *= (float) iterEtape2/ (float) nbIterTotal;
        pos += (float) iterEtape1/ (float) nbIterTotal * TAILLEBARRECHARGEMENT;
    }
    pos = floor(pos);
    
    for (int i = 0; i < pos; i++) printf("#");
    printf(NEUTRE);
    for (int i = 0; i < TAILLEBARRECHARGEMENT - pos; i++) printf(" ");
    printf(ROUGE "]\n\n" NEUTRE);
}

void partie2() {
    FILE* fichierEnt = fopen("data/airbnbEntrainement.csv", "r");
    if (fichierEnt == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }
    FILE* fichierTest = fopen("data/airbnbTest.csv", "r");
    if (fichierTest == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }

    int nLignesEnt = nbLignes(fichierEnt);
    int tailleTabEnt = nLignesEnt - 1;
    logement tabEntrainement[tailleTabEnt];
    int nLignesTest = nbLignes(fichierTest);
    int tailleTabTest = nLignesTest - 1;
    logement tabTest[tailleTabTest];

    remplirTabSansDistance(tabEntrainement, fichierEnt, tailleTabEnt);
    remplirTabSansDistance(tabTest, fichierTest, tailleTabTest);
    
    // Recherche empirique du meilleur k (l'algorithme devant faire un tri rapide de 7000 éléments pour chacun des 2000 éléments, il serait très long de faire tous les k un par un)
    int kMin = 1;
    float maeMin = 0.0;

    affichageChargement(DEBUT, FIN, DEBUT, 0);

    for (int k = DEBUT; k <= FIN; k += PAS) {
        float tabPrediction[tailleTabTest];
        remplirPrediction(tabEntrainement, tailleTabEnt, tabTest, tailleTabTest, tabPrediction, k);

        float mae = calculMAE(tabTest, tabPrediction, tailleTabTest);
        if (maeMin == 0.0 || mae < maeMin) {
            maeMin = mae;
            kMin = k;
        }
        affichageChargement(DEBUT, FIN, k, 0);
        printf("maeMin = %.5f est atteint pour k = %d\n", maeMin, kMin);
    }

    printf("Pour k = %d, le MAE était le plus faible sur les entiers dans [%d, %d] (MAE = %.5f)\n", kMin, DEBUT, FIN, maeMin);
    printf("Recherche 1 par 1 sur les entiers dans [%d, %d]\n", kMin + 1, kMin + 29);

    int kBorneInf = kMin + 1;
    int kBorneSup = kMin + PAS;
    for (int k = kBorneInf; k < kBorneSup; k++) { // Inutile de recalculer pour kMin (il est déjà en cache)
        float tabPrediction[tailleTabTest];
        remplirPrediction(tabEntrainement, tailleTabEnt, tabTest, tailleTabTest, tabPrediction, k);

        float mae = calculMAE(tabTest, tabPrediction, tailleTabTest);
        if (mae < maeMin) {
            maeMin = mae;
            kMin = k;
        }
        affichageChargement(kBorneInf, kBorneSup, k + 1, 1);
        printf("maeMin = %.5f est atteint pour k = %d\n", maeMin, kMin);
    }

    printf("Pour k = %d, les performances sont optimales (MAE = %.5f)\n", kMin, maeMin);

    fclose(fichierEnt);
    fclose(fichierTest);
}