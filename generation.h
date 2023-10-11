//
// Created by Pax on 09/10/2023.
//

#ifndef FIRE_PROJECT_GENERATION_H
#define FIRE_PROJECT_GENERATION_H
#include "states.h"


Cell **allocateMemory(int width, int height);
void initMap(Cell **grid, int width, int height);
Cell **readMap(char *filename);
int getMapWidth(char *filename);
int getMapHeight(char *filename);
#endif //FIRE_PROJECT_GENERATION_H
