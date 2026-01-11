#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"


extern int numero_paquet;


void sauvegarder_etat(Capteur *c) {

    FILE *fichier = fopen("save.bin", "wb");
    if (fichier == NULL) {
        printf("Erreur: impossible de sauvegarder\n");
        return;
    }


    fwrite(&c->batterie, sizeof(float), 1, fichier);
    fwrite(&c->x, sizeof(float), 1, fichier);
    fwrite(&c->y, sizeof(float), 1, fichier);
    fwrite(&c->buffer_usage, sizeof(int), 1, fichier);
    fwrite(&numero_paquet, sizeof(int), 1, fichier);


    Paquet *actuel = c->buffer_tete;
    while (actuel != NULL) {
        fwrite(&actuel->id, sizeof(int), 1, fichier);
        fwrite(&actuel->valeur, sizeof(float), 1, fichier);
        fwrite(&actuel->timestamp, sizeof(long), 1, fichier);
        actuel = actuel->suivant;
    }

    fclose(fichier);
    printf("Etat sauvegarde dans save.bin\n");
}


void charger_etat(Capteur *c) {

    FILE *fichier = fopen("save.bin", "rb");
    if (fichier == NULL) {
        printf("Aucune sauvegarde trouvee\n");
        return;
    }


    fread(&c->batterie, sizeof(float), 1, fichier);
    fread(&c->x, sizeof(float), 1, fichier);
    fread(&c->y, sizeof(float), 1, fichier);
    fread(&c->buffer_usage, sizeof(int), 1, fichier);
    fread(&numero_paquet, sizeof(int), 1, fichier);


    c->buffer_tete = NULL;


    Paquet *dernier = NULL;
    for (int i = 0; i < c->buffer_usage; i++) {

        Paquet *nouveau = malloc(sizeof(Paquet));
        if (nouveau == NULL) {
            printf("Erreur memoire lors du chargement\n");
            break;
        }


        fread(&nouveau->id, sizeof(int), 1, fichier);
        fread(&nouveau->valeur, sizeof(float), 1, fichier);
        fread(&nouveau->timestamp, sizeof(long), 1, fichier);
        nouveau->suivant = NULL;


        if (c->buffer_tete == NULL) {

            c->buffer_tete = nouveau;
            dernier = nouveau;
        }
        else {

            dernier->suivant = nouveau;
            dernier = nouveau;
        }
    }

    fclose(fichier);
    printf("Etat charge depuis save.bin\n");
}
