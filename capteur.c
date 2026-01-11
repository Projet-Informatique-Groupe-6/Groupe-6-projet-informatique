#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "capteur.h"

int numero_paquet = 0;

void produire_paquet(Capteur *c, long temps) {

    if (c->batterie <= 0) {
        return;
    }


    if (c->buffer_usage >= 5) {

        Paquet *a_supprimer = c->buffer_tete;


        printf("ALERTE : Memoire saturee. Suppression du paquet ID %d pour liberer de l'espace.\n",
               a_supprimer->id);


        c->buffer_tete = a_supprimer->suivant;


        free(a_supprimer);


        c->buffer_usage--;
    }


    Paquet *nouveau = malloc(sizeof(Paquet));
    if (nouveau == NULL) {
        printf("Erreur allocation memoire\n");
        return;
    }


    numero_paquet++;
    nouveau->id = numero_paquet;
    nouveau->valeur = (rand() % 1001) / 10.0f;
    nouveau->timestamp = temps;
    nouveau->suivant = NULL;

    if (c->buffer_tete == NULL) {

        c->buffer_tete = nouveau;
    } else {

        Paquet *courant = c->buffer_tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }

    c->buffer_usage++;

    printf("Nouveau paquet cree: ID=%d\n", nouveau->id);
}




