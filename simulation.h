//
// Created by Pax on 09/10/2023.
//

#ifndef FIRE_PROJECT_SIMULATION_H
#define FIRE_PROJECT_SIMULATION_H
#include "structures.h"
#include <stdio.h>

void startFire(int x, int y, CELL **grid);
void evaluateCELL(int x, int y, int width, int height, CELL **grid);
void evaluateGrid(CELL **grid);

#endif //FIRE_PROJECT_SIMULATION_H
