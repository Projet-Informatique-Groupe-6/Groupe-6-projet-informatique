#ifndef CAPTEUR_H
#define CAPTEUR_H


typedef struct Paquet {
    int id;
    float valeur;
    long timestamp;
    struct Paquet *suivant;
} Paquet;


typedef struct {
    float batterie;
    float x, y;
    Paquet *buffer_tete;
    int buffer_usage;
} Capteur;


void produire_paquet(Capteur *c, long temps);
void ajouter_paquet_fin(Capteur *c, Paquet *p);
void supprimer_premier_paquet(Capteur *c);
void vider_buffer(Capteur *c);

#endif
