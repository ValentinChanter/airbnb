
<div align="center">
  <p>
    <img src="https://i.imgur.com/IJdvswV.png" width="546" alt="Sujet 1" />
  </p>
</div>

## A propos

Ce sujet consiste en la prédiction du prix de logements sur Airbnb. Il est séparé en deux parties : 
* La première permet de prédire le prix d'une habitation en particulier, connaissant ses caractéristiques
* La deuxième, bonus, permet d'évaluer la performance du modèle de prédiction

## Pour commencer

### Prérequis

* gcc (ou un autre compilateur en C)
* Un ordinateur sous Linux (l'application a été testée sur Ubuntu 20.04.5)

### Mise en place lors de la première utilisation

1. Ouvrez un terminal et placez-vous dans le répertoire dans lequel se trouvent le Makefile et les fichiers .c et .h
2. Compilez à l'aide du Makefile
   ```console
   make
   ```
3. (Optionnel) Supprimez les fichiers .o
   ```console
   make clean
   ```

## Usage

Peu importe la partie qu'on veut lancer, il faut commencer par exécuter le fichier généré avec le Makefile
   ```console
   ./airbnb
   ```
Le terminal affichera ainsi :
   ```console
   Quelle partie voulez-vous lancer ?
   [1] Partie 1 - Prédiction du prix
   [2] Partie 2 - Evaluation de la performance du modèle
   ```

### Pour estimer le prix d'un logement

1. Tapez 1 et appuyez sur Entrée
2. Suivez les instructions affichées par le terminal : renseignez le nombre d'hôtes, le nombre de chambres, et le nombre de lits que votre logement comporte
3. Le terminal affichera le prix estimé obtenu et sa fiabilité

### Pour trouver un k tel que les performances du modèles soient optimales

1. Tapez 2 et appuyez sur Entrée
2. Le terminal commencera à chercher k, 30 par 30, entre 20 et 500, tel que le MAE est le plus faible. Ensuite, il cherchera entre k + 1 et k + 29. Une fois terminé, il affichera le k obtenu

## Options supplémentaires

Plusieurs constantes sont définies par défaut dans le fichier airbnb.h et sont modifiables au besoin.

* `NOMBRELOGEMENTS` correspond au nombre de logements qu'on va utiliser pour prédire le prix (par défaut 500)
* `DEBUT` correspond au k auquel commencer la recherche du k optimal (par défaut 20)
* `FIN` correspond au k auquel arrêter la recherche du k optimal (par défaut 500)
* `PAS` correspond au pas du k pendant la recherche du k optimal (par défaut 30)
* `TAILLEBARRECHARGEMENT` correspond au nombre de caractères constituant la barre de chargement pendant la recherche (par défaut 50)