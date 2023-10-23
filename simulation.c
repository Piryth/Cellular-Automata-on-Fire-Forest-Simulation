/**
 *  This file contains all the functions related to cell simulation evaluation
 */
#include "structures.h"
#include <stdio.h>

/**
 * Evaluates the cells of the map and modify their state
 */
void evaluateGrid(CELL **grid) {

}

/**
 * Evaluates cell by cell by analyzing the neighbours
*/
void evaluateCELL(int x, int y, int width, int height, CELL **grid) {
  CELL cell = grid[x][y];

  if(cell.state = FUEL) {
    CELL neighbour;
    int nbNeighbours = 0;

    for(int i = x-1; i <= x+1; i++) {

      for(int j = y - 1; j <= y +1; j++) {
        neighbour = grid[i][j];

        if(i < 0) neighbour = grid[width-1][j];
        if(j < 0) neighbour = grid[i][height-1];
        if(i > width-1) neighbour = grid[0][j];
        if(j > height-1) neighbour = grid[i][0];

        if(neighbour.state == BURNING) nbNeighbours++;

      }
    }

  } else if (cell.state = BURNING) {
    if(cell.generationsBurning >= 3) {
      cell.state = BURNT;
    }
    cell.generationsBurning++;

  }


}

/**
 *  Sets a cell to burning at the specified location. If the cell is NON_FUEL, nothing happens
 */
void startFire(int x, int y, CELL **grid) {

  if(grid[x][y].state == FUEL) {
    grid[x][y].state = BURNING;
  }
}
