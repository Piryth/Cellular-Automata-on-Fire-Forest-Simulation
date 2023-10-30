#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "structures.h"
#include "simulation.h"
#include "readmap.h"
#include "constants.h"

int main(int argc, char **argv) {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     INITIALISATION                                             ////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Specifying the acces to the map
    char *fileName = "map";

    //Reading the map file and assigning the size. WARNING : the size must be correct and the map must be square
    CELL **gridCurr = readMap(fileName);

    CELL **gridFuture = (CELL **) malloc(mapWidth * sizeof(CELL *));
    for (int i = 0; i < mapWidth; i++)
        gridFuture[i] = (CELL *) malloc(mapHeight * sizeof(CELL));

    //Copying the data to the future grid
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            gridFuture[i][j] = gridCurr[i][j];
        }
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     SIMULATION                                             ////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Start the fire at 1,1 (debug)
    int x_start = 1;
    int y_start = 1;
    //NOTE : at the beginning, we do not take into account whether the cell is fuel or not
    gridFuture[x_start][y_start].state = BURNING;

    //////////////////////////////////////////
    /////   SIMULATION BEGIN            /////
    /////////////////////////////////////////
    int n=0;
    while(n < NUMBEROFGENERATIONS) {

        ////////////////////////////////////////////
        //// STEP 1 : COPY FUTURE MAP TO CURRENT////
        ////////////////////////////////////////////
        //Copying the future grid to the current (saves the change of the fire start)
        for (int i = 0; i < mapWidth; i++) {
            for (int j = 0; j < mapHeight; j++) {
                gridCurr[i][j] = gridFuture[i][j];
            }
        }

        ////////////////////////////////////////////
        //// STEP 2 : EVALUATE NEW STATES       ////
        ////////////////////////////////////////////
        for (int i = 0; i < mapWidth; i++) {
            for (int j = 0; j < mapHeight; j++) {
                //Changing the state of the future grid
                evaluateCELL(i,j,mapWidth,mapHeight, gridFuture);
            }
        }


        n++;
    }


    //Displaying
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            printf(" %d ", gridFuture[i][j].state);
        }
        printf("\n");
    }



    //Freeing the grids
    for (int i = 0; i < mapWidth; i++) {
        free(gridCurr[i]);
        free(gridFuture[i]);
    }

    free(gridCurr);
    free(gridFuture);



}
