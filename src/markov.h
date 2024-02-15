/**
Fichier markov.h
Auteur(s):Hugo Favier 22102319
*/
#ifndef __MARKOV_H__
#define __MARKOV_H__
#include"hachage.h"
#include <stdio.h>
#include <stdlib.h>

// Vous travaillerez ici


typedef struct markov_s{
  unsigned int taille;
  unsigned int * etats;
  int ** matrice_poid;
}markov_t;

/**
   Cette fonction créé une chaine de markov et initialise la graine aléatoire
   @param graine est la graine de génération aléatoire.
   @ensures resultat->taille == 0
   @ensures resultat->etats == NULL
   @ensures resultat->matrice_poid == NULL
   @return une chaine de markov Vide
*/
markov_t* creer_markov(int graine);
/**
   Cette fonction prend en entrée une une chaine de markov et libère l'espace mémoire de la structure markov_t
   @param chaine est la chaine de markov à détruire.
   @ensures l'espace mémoire de chaine->etats est libéré
   @ensures pour chaque ligne de chaine->matrice_poid,  l'espace mémoire de la ligne est libéré et l'espace mémoire de chaine->matrice_poid est libéré
*/
void detruire_markov(markov_t* chaine);
/**
   Cette fonction prend en entrée une une chaine de markov et lui ajoute un état(reprsenté par un int)
   @param chaine est la chaine de markov à modifier.
   @requires la chaine à été initialisé avec la fonction creer_markov
   @ensures taille = taille + 1
   @ensures res -> etats[taille] = taille-1 (soit taille avant d'utiliser cette fonction)
   @ensures la taille de chaine->états est augmenté de 1 élément
   @ensures le coté de la matrice carré chaine->matrice_poid est augmenté de 1
*/
void ajouterEtat(markov_t* chaine);

/**
   Cette fonction prend en entrée une une chaine de markov et augmente le poid entre l'etat e1 et l'etat e2
   @param chaine est la chaine de markov à modifier.
   @param e1 est l'indice de e1 dans chaine->états.
   @param e2 est l'indice de e2 dans chaine->états.
   @ensures res -> matrice_poid[e1][e2] += 1
*/
void augmenterPoid(markov_t* chaine,unsigned int e1,unsigned int e2);

/**
   Cette fonction prend en entrée une une chaine de markov et renvoi le poid entre l'etat e1 et l'etat e2
   @param chaine est la chaine de markov à modifier.
   @param e1 est l'indice de e1 dans chaine->états.
   @param e2 est l'indice de e2 dans chaine->états.
   @requires e1,e2 >=0 && e1,e2 <chaine->taille
   @ensure resultat >= 0
   @return le poid entre l'etat e1 et l'etat e2
*/
int poid(markov_t* chaine,unsigned int e1,unsigned int e2);

/**
   Cette fonction calcule la probabilité de passer d'un etat e1 à un etat e2
   @param chaine est la chaine de markov à modifier.
   @param e1 est l'indice de e1 dans chaine->états.
   @param e2 est l'indice de e2 dans chaine->états.
   @requires e1,e2 >=0 && e1,e2 <chaine->taille
   @ensure resultat >=0
   @ensure resultat <=1
   @return le probabilité de passer de e1 à e2
*/
double probabilite(markov_t* chaine,unsigned int e1,unsigned int e2);

/**
   Cette fonction utilise la fonction probabilite pour se déplacer d'un etat e1 à un etat choisis aléatoirement parmis ses voisins
   @param chaine est la chaine de markov à modifier.
   @param e1 est l'indice de e1 dans chaine->états.
   @ensure poid(chaine,e1,resultat) == 0 => la chaine est homogène
   @return l'indice d'un etat choisis aléatoirement parmis les voisins de e1
*/
unsigned int deplacementAleatoire(markov_t* chaine,unsigned int e1);


#endif
