//
// Created by arnaud on 10/12/23.
//

#ifndef CELLULAR_AUTOMATA_PARALLEL_EDIT_FUNCTIONS_H
#define CELLULAR_AUTOMATA_PARALLEL_EDIT_FUNCTIONS_H
#include "structures.h"

CELL** initializeMap();
void *thread_simulation(void *args);
void outputData(char* filename, CELL** grid);

//Perlin noise
//NOTE : IMPLEMENTED BY https://gist.github.com/nowl/828013
float lin_inter(float x, float y, float s);
int noise2(int x, int y);
float perlin2d(float x, float y, float freq, int depth);
float noise2d(float x, float y);
float smooth_inter(float x, float y, float s);


#endif //CELLULAR_AUTOMATA_PARALLEL_EDIT_FUNCTIONS_H
