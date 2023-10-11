#include <stdio.h>
#include <malloc.h>
#include "states.h"
#include "generation.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20


int main(int argc, char **argv) {

    //Specifying the acces to the map
    //char *home = "/mnt/c/Users/Pax/Documents/Etudes/ThirdYear/ParallelComputing/FireProject/map";

    //Reading the map file and assigning the size. WARNING : the size must be correct and the map must be square
    Cell **grid = readMap("map");

    //We need to retrive the size of the map
    int width =  getMapWidth("map");
    int height = getMapHeight("map");
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            printf(" %d ", grid[i][j].state);
        }
        printf("\n");
    }

    for (int i = 0; i < width; i++) {
        free(grid[i]);
    }
    free(grid);
    
}

