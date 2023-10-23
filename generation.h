//
// Created by Pax on 09/10/2023.
//

#ifndef FIRE_PROJECT_GENERATION_H
#define FIRE_PROJECT_GENERATION_H
#include "structures.h"


CELL **allocateMemory(int width, int height);
void initMap(CELL **grid, int width, int height);
CELL **readMap(char *filename);
int getMapWidth(char *filename);
int getMapHeight(char *filename);
#endif //FIRE_PROJECT_GENERATION_H
