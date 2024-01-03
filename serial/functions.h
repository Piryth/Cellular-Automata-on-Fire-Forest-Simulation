//
// Created by arnaud on 30/10/23.
//

#ifndef CELLULAR_AUTOMATA_ON_FIRE_FOREST_SIMULATION_CONSTANTS_H
#define CELLULAR_AUTOMATA_ON_FIRE_FOREST_SIMULATION_CONSTANTS_H


#include "structures.h"

CELL** initializeMap();
void evaluateCell(int x, int y, CELL **gridSource, CELL **gridDest);
void outputData(char* filename, CELL** grid);

//Perlin noise
//NOTE : IMPLEMENTED BY https://gist.github.com/nowl/828013
float lin_inter(float x, float y, float s);
int noise2(int x, int y);
float perlin2d(float x, float y, float freq, int depth);
float noise2d(float x, float y);
float smooth_inter(float x, float y, float s);


#endif //CELLULAR_AUTOMATA_ON_FIRE_FOREST_SIMULATION_CONSTANTS_H

