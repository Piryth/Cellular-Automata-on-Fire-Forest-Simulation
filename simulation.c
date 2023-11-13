/**
 *  This file contains all the functions related to cell simulation evaluation
 */
#include "structures.h"
#include "constants.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Evaluates cell by cell by analyzing the neighbours
*/
int modulo(int a, int b) {
    return ((a%b)+b)%b;
}
void evaluateCELL(int x, int y, int width, int height, CELL **grid) {
    //srand(time(NULL));
    int nbNeighbours = 0;
    if(grid[modulo(x-1, width)][modulo(y-1,height)].state == BURNING) {nbNeighbours++;

    }
    if(grid[modulo(x, width)][modulo(y-1,height)].state == BURNING) nbNeighbours++;
    if(grid[modulo(x+1, width)][modulo(y-1,height)].state == BURNING) nbNeighbours++;
    if(grid[modulo(x-1, width)][modulo(y,height)].state == BURNING) nbNeighbours++;
    if(grid[modulo(x+1, width)][modulo(y,height)].state == BURNING) nbNeighbours++;
    if(grid[modulo(x-1, width)][modulo(y+1,height)].state == BURNING) nbNeighbours++;
    if(grid[modulo(x, width)][modulo(y+1,height)].state == BURNING) nbNeighbours++;
    if(grid[modulo(x+1, width)][modulo(y+1,height)].state == BURNING) nbNeighbours++;



    float probability = nbNeighbours/8.0;
    int random = rand()% (100);

    //printf("Neighbours at %d,%d : %d\n",x,y, nbNeighbours);
    //printf("Probality of burn at %d,%d : %d\n",x,y, (int)(probability*100.0));
    //printf("Random seed at %d,%d : %d\n",x,y, random);
    if(random < (int)(probability*100) && grid[x][y].state == FUEL) {
        grid[x][y].state = BURNING;
        printf("Cell[%d][%d] is burning !\n", x,y);
    }

    if(grid[x][y].state == BURNING) {
        grid[x][y].generationsBurning++;
    }

    if(grid[x][y].generationsBurning >=3) {
        grid[x][y].state = BURNT;
    }






}

