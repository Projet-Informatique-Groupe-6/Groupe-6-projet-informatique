#ifndef SIMULATION_H
#define SIMULATION_H

#include "capteur.h"


#define ENERGIE_CIRCUIT 0.05f
#define ENERGIE_AMPLI   0.01f


int transmettre_un_paquet(Capteur *c);
float calculer_distance(float x, float y);

#endif
