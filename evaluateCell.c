//Author : Arnaud Endignous
/**
 *  This file contains all the functions related to cell simulation evaluation
 */
#include "structures.h"
#include "functions.h"
#include "constants.h"
#include <stdlib.h>

float probabilities[] = {0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1};

/**
 * Evaluates the cell of a current grid, evaluates its states and put it in a source grid
 * @param x X axis
 * @param y Y axis
 * @param gridDest  Grid of destination. Future grid that will contain new states
 * @param gridSource  Source grid or current grid. Destination grid is modified according to it
 */
void evaluateCell(int x, int y, CELL **gridSource, CELL **gridDest) {

    int state = gridSource[x][y].state;

    if (state == LOW_FLAMMABILITY || state == MEDIUM_FLAMMABILITY || state == HIGH_FLAMMABILITY) {
        int nbNeighbours = 0;

        int x_west = (x - 1 + MAP_WIDTH) % MAP_WIDTH;
        int x_east = (x + 1 + MAP_WIDTH) % MAP_WIDTH;

        int y_north = (y - 1 + MAP_HEIGHT) % MAP_HEIGHT;
        int y_south = (y + 1 + MAP_HEIGHT) % MAP_HEIGHT;

        if (gridSource[x_west][y_north].state == BURNING) nbNeighbours++;
        if (gridSource[x][y_north].state == BURNING) nbNeighbours++;
        if (gridSource[x_east][y_north].state == BURNING) nbNeighbours++;

        if (gridSource[x_west][y].state == BURNING) nbNeighbours++;
        if (gridSource[x_east][y].state == BURNING) nbNeighbours++;
        if (gridSource[x_west][y_south].state == BURNING) nbNeighbours++;
        if (gridSource[x][y_south].state == BURNING) nbNeighbours++;
        if (gridSource[x_east][y_south].state == BURNING) nbNeighbours++;

        float randFloat = (float) rand() / (float) RAND_MAX;
        float probability = probabilities[nbNeighbours];

        if (state == LOW_FLAMMABILITY) probability *= 0.8;
        if (state == HIGH_FLAMMABILITY) probability *= 1.25;

        if (randFloat < probability) {
            gridDest[x][y].state = BURNING;
        }

    } else if (state == BURNING) {
        gridDest[x][y].generationsBurning++;
        if (gridSource[x][y].generationsBurning >= 3) {
            gridDest[x][y].state = BURNT;
        }
    }

}

