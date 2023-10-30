/**
 *  This file contains all the functions related to cell simulation evaluation
 */
#include "structures.h"
#include "constants.h"
#include <time.h>
#include <stdlib.h>


/**
 * Evaluates cell by cell by analyzing the neighbours
*/
void evaluateCELL(int x, int y, int width, int height, CELL **grid) {
  CELL cell = grid[x][y];
  srand(time(NULL));

  if(cell.state == FUEL) {
    CELL neighbour;
    int nbNeighbours = 0;

    for(int i = x-1; i <= x+1; i++) {
      for(int j = y - 1; j <= y +1; j++) {
        if(grid[i%mapWidth][j%mapHeight].state == BURNING) nbNeighbours++;
      }
    }
    int randomInt = rand()%101;
    if(nbNeighbours*10 >= randomInt) {
        cell.state = BURNING;
    }


  } else if (cell.state == BURNING) {
    if(cell.generationsBurning >= 3) {
      cell.state = BURNT;
    }
    cell.generationsBurning++;

  }
}

