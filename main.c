#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "structures.h"
#include "generation.h"
#include "simulation.h"


int main(int argc, char **argv) {

    //Specifying the acces to the map
    //char *home = "/mnt/c/Users/Pax/Documents/Etudes/ThirdYear/ParallelComputing/FireProject/map";

    //We need to retrive the size of the map
    int width =  getMapWidth("map");
    int height = getMapHeight("map");

    //Reading the map file and assigning the size. WARNING : the size must be correct and the map must be square
    CELL **gridCurr = readMap("map");
    CELL **gridFuture = allocateMemory(width, height);

    //Copying the data to the future grid
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            gridFuture[i][j] = gridCurr[i][j];
        }
    }

    //Not working
    //memcpy(gridFuture, gridCurr, sizeof(gridCurr));

    startFire(0,0,gridFuture);

    //Displaying
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            printf(" %d ", gridFuture[i][j].state);
        }
        printf("\n");
    }

    //Freeing the grids
    for (int i = 0; i < width; i++) {
        free(gridCurr[i]);
        free(gridFuture[i]);
    }

    free(gridCurr);
    free(gridFuture);



}
