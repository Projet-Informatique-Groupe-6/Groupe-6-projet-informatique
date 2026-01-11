#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "simulation.h"
#include "capteur.h"

int transmettre_paquets(Capteur *c) {
    if (c->buffer_tete == NULL) {
        return 0;
    }

    double distance = sqrt(c->x * c->x + c->y * c->y);
    double energie = 0.05 + 0.01 * distance * distance;

    if (c->batterie < energie) {
        return -1;
    }

    c->batterie -= energie;

    printf("Energie consommee: %.3f Joules\n", energie);


    return 0;
}
