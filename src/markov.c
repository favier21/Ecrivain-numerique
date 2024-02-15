#include"markov.h"
#include <stdlib.h>
# include <stdio.h>

markov_t* creer_markov(int graine){
  srand (graine);
  markov_t* res = malloc(sizeof(markov_t));
  res -> taille = 0;
  res -> etats = NULL;
  res -> matrice_poid = NULL;
  return res;

}
void detruire_markov(markov_t* chaine){
    for(int i = 0; i < chaine->taille; i++)
        free(chaine->matrice_poid[i]);
    free(chaine->matrice_poid);
    free(chaine->etats);
    free(chaine);
}
void ajouterEtat(markov_t* chaine){
  chaine->taille++;
  chaine->etats = realloc(chaine->etats,sizeof(int) *chaine->taille);
  chaine->etats[chaine->taille-1] = chaine->taille-1;
  chaine->matrice_poid = realloc(chaine->matrice_poid,sizeof(int*) * chaine->taille);
  chaine->matrice_poid[chaine->taille-1] = calloc(chaine->taille, sizeof(int)*chaine->taille);//ajouter une ligne de 0
  for(int i = 0; i < chaine->taille-1; i++){
    chaine->matrice_poid[i] = realloc(chaine->matrice_poid[i],sizeof(int) * chaine->taille);
    chaine->matrice_poid[i][chaine->taille-1] =0; //ajouter la colone des 0
  }
}

void augmenterPoid(markov_t* chaine,unsigned int e1,unsigned int e2){
  chaine->matrice_poid[e1][e2]++;
}

int poid(markov_t* chaine,unsigned int e1,unsigned int e2){
  return chaine->matrice_poid[e1][e2];
}

double probabilite(markov_t* chaine,unsigned int e1,unsigned int e2){
  double somme_poid = 0;
  for (unsigned int i = 0; i < chaine->taille; i++)
    somme_poid = somme_poid + poid(chaine,e1,i);
  if (somme_poid == 0) {
    return 1.0 / chaine->taille; // renvoyer une probabilité uniforme
  }
  return poid(chaine,e1,e2)/somme_poid;
}
void trier(markov_t* chaine,double* liste, int taille) {
    int i, j, min, temp1, temp2;
    for (i = 0; i < taille - 1; i++) {
        min= i;
        for (j = i + 1; j < taille; j++) {
            if (liste[j] < liste[min])
                min = j;
        }
        temp1 = liste[i];
        temp2 = chaine -> etats[i];
        chaine -> etats[i] = chaine -> etats[min];
        liste[i] = liste[min];
        liste[min] = temp1;
        chaine -> etats[min] = temp2;
    }
}
unsigned int deplacementAleatoire(markov_t* chaine,unsigned int e1){
  double choix[chaine->taille];
  double rand_num =rand() / (double)RAND_MAX;

  for (unsigned int i = 0; i < chaine->taille; i++) {
    choix[i]=probabilite(chaine,e1,i);
  }
  trier(chaine,choix,chaine->taille);
  for (unsigned int i = 0; i < chaine->taille; i++) {
    if(rand_num<=choix[i]){
      return chaine->etats[i];
    }
    else
      rand_num = rand_num - choix[i];
  }
  printf("Il y a une erreur,aucun poids n'a été ajouté\n");
  exit(EXIT_FAILURE);
}

/*
int main(void){
   markov_t* mark =creer_markov(-50);
   ajouterEtat(mark);
   ajouterEtat(mark);
   ajouterEtat(mark);
   ajouterEtat(mark);
   ajouterEtat(mark);
   printf("%f\n", probabilite(mark,0,4));
   printf("%f\n", probabilite(mark,1,4));
   printf("%f\n", probabilite(mark,2,4));
   printf("%f\n", probabilite(mark,3,4));
   printf("%f\n", probabilite(mark,4,4));
   printf("%u \n",deplacementAleatoire(mark,3));
   detruire_markov(mark);
   return 0;
}
*/
