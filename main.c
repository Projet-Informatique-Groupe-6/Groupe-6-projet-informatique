#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "capteur.h"
#include "simulation.h"
#include "fichier.h"

int id_global = 0;

int main() {
    srand(time(NULL));

    Capteur c;

    printf("=== SIMULATEUR DE CAPTEUR ECO-SENSING ===\n\n");

    printf("Entrez le niveau de batterie initial (Joules) : ");
    scanf("%f", &c.batterie);

    printf("Entrez la position X du capteur : ");
    scanf("%f", &c.x);

    printf("Entrez la position Y du capteur : ");
    scanf("%f", &c.y);

    c.buffer_tete = NULL;
    c.buffer_usage = 0;

    FILE *log = fopen("log.txt", "w");
    if (!log) {
        printf("Erreur ouverture log.txt\n");
        return 1;
    }

    long temps = 1;
    int total_transmis = 0;

    printf("\n=== DEBUT DE LA SIMULATION ===\n\n");

    while (1) {
        printf("\n--- Cycle %ld ---\n", temps);

        if (c.batterie <= 0) {
            printf("Batterie epuisee! Simulation terminee.\n");
            break;
        }

        produire_paquet(&c, temps);

        printf("Paquets dans le buffer : %d/5\n", c.buffer_usage);

        if (c.buffer_tete != NULL) {
            printf("Contenu du buffer :\n");
            Paquet *p = c.buffer_tete;
            int i = 1;
            while (p != NULL) {
                printf("  %d. ID=%d, Valeur=%.1f\n",
                       i++, p->id, p->valeur, p->timestamp);
                p = p->suivant;
            }
        }

        int resultat = transmettre_paquets(&c);

        if (resultat == -1) {
            printf("Erreur : batterie insuffisante pour transmission\n");
            c.batterie = 0;
        }

        fprintf(log, "Temps:%lds | Batterie:%.2fJ | Paquets en attente:%d\n",
                temps, c.batterie, c.buffer_usage);

        printf("Batterie restante : %.2f Joules\n", c.batterie);

        temps++;


    }

    sauvegarder_etat(&c);

    fclose(log);

    printf("\n=== FIN DE LA SIMULATION ===\n");
    printf("Duree totale : %ld cycles\n", temps);
    printf("Paquets restants dans le buffer : %d\n", c.buffer_usage);

    return 0;
}
