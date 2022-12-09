#include "airbnb.h"
#include <stdlib.h>

int main() {
    printf("Quelle partie voulez-vous lancer ?\n[1] Partie 1 - Prédiction du prix d'un logement\n[2] Partie 2 - Evaluation de la performance du modèle\n");

    int partie;
    int retCode = scanf("%d", &partie);
    if (!retCode) exit(2);

    switch(partie) {
        case 1:
            partie1();
            break;

        case 2:
            partie2();
            break;

        default:
            printf("Cette partie n'existe pas.\n");
            break;
    }
}