#define TAILLEMAXBUFFER 100
#define NOMBRELOGEMENTS 500 // k logements à utiliser pour calculer le prix du logement X dans le sujet 1

// Les valeurs de début, fin et pas pour la recherche du k pour un MAE optimal
#define DEBUT 20
#define FIN 500
#define PAS 30
#define TAILLEBARRECHARGEMENT 50

#define ROUGE "\033[1m\033[31m"
#define NEUTRE "\033[0m"

#include <stdio.h>

typedef struct Logement {
    // Comme indiqué dans l'énoncé, on ne considèrera que ces 3 critères, inutile d'ajouter les autres
    int accomodates;
    int bedrooms;
    int beds;
    float price;
    float distance;
} logement;

// Fonctions pour le sujet 1
int nbLignes(FILE*);
void afficherTab(logement*, int);
void remplirTab(logement, logement*, FILE*, int);
void remplirTabSansDistance(logement*, FILE*, int);
void melangerTab(logement*, int);
float moyenne(logement*, int);
float tauxFiab(logement*, int, int);

// Pour le tri rapide
void echange(logement*, logement*);
int partition(logement*, int, int);
void triRapideAux(logement*, int, int);
void triRapide(logement*, int);

// Pour la partie 2 du sujet 1
void remplirPrediction(logement*, int, logement*, int, float*, int);
void afficherTabEtPrediction(logement*, float*, int);
float calculMAE(logement*, float*, int);

void partie1();
void partie2();