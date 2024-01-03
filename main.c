//Author : Arnaud Endignous
#include <stdio.h>
#include "structures.h"
#include <stdlib.h>
#include "functions.h"
#include "constants.h"
#include <time.h>

//Grids
CELL **gridCurr;
CELL **gridFuture;

int main(void) {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     INITIALISATION                                             ////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Reading the map file and assigning the size. WARNING : the size must be correct and the map must be square
    gridCurr = initializeMap();

    gridFuture = (CELL **) malloc(MAP_WIDTH * sizeof(CELL *));
    for (int i = 0; i < MAP_WIDTH; i++) {
        gridFuture[i] = (CELL *) malloc(MAP_HEIGHT * sizeof(CELL));
    }

    //Copying the data to the future grid
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            gridFuture[i][j] = gridCurr[i][j];
        }
    }

    printf("Serial program execution\n");


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                     SIMULATION                                             ////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Start the fire at 1,1 (debug)
    int x_start = 5;
    int y_start = 5;
    //NOTE : at the beginning, we do not take into account whether the cell is fuel or not
    gridFuture[x_start][y_start].state = BURNING;


    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC,&start);

    //////////////////////////////////////////
    /////   SIMULATION BEGIN            /////
    /////////////////////////////////////////
    int n=0;
    while(n < NUMBEROFGENERATIONS) {

        ////////////////////////////////////////////
        //// STEP 1 : EVALUATE NEW STATES       ////
        ////////////////////////////////////////////

        for (int i = 0; i < MAP_WIDTH; i++) {
            for (int j = 0; j < MAP_HEIGHT; j++) {
                evaluateCell(i,j, gridCurr,gridFuture);
            }
        }

        ////////////////////////////////////////////
        //// STEP 2 : COPY FUTURE MAP TO CURRENT////
        ////////////////////////////////////////////
        for (int i = 0; i < MAP_WIDTH; i++) {
            for (int j = 0; j < MAP_HEIGHT; j++) {
                gridCurr[i][j] = gridFuture[i][j];
            }
        }

        ////////////////////////////////////////////
        //// STEP 3 : WRITING OUTPUT TO FILE    ///
        ////////////////////////////////////////////
        char* buffer = malloc(30*sizeof(char));
        sprintf(buffer,"out/%d.dat",n);
        outputData(buffer,gridFuture);

        n++;
    }


    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec);
    elapsed+= (end.tv_nsec - start.tv_nsec)/ 1000000000.0;
    printf("Time elapsed according to clock_gettime : %lf sec\n",elapsed);

    //Freeing the grids
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(gridCurr[i]);
        free(gridFuture[i]);
    }

    free(gridCurr);
    free(gridFuture);


}
