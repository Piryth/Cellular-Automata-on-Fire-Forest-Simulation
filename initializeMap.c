//Author : Arnaud Endignous
#include "structures.h"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "functions.h"

/**
 * Function readMap aims to manage the input.
 * @pre The map file must be correct
 * @return A grid of CELLs according to the map file
 */
CELL** initializeMap() {

    srand(time(NULL));

    //MAP ALLOCATION
    CELL **map = (CELL **) malloc(MAP_WIDTH * sizeof(CELL *));
    for (int i = 0; i < MAP_WIDTH; i++)
        map[i] = (CELL *) malloc(MAP_HEIGHT * sizeof(CELL));

    int randState;
    for(int i = 0; i < MAP_WIDTH; i++) {
        //Retriving line by line
        //Itrerating over the array of char
        for(int j = 0; j < MAP_HEIGHT; j++) {

            //Creating noise
            float perlinCoefficient = perlin2d(i,j,0.1,4);

            if(perlinCoefficient <= .5) map[i][j].state = NON_FUEL;
            else if(perlinCoefficient > .5 && perlinCoefficient < .55) map[i][j].state = LOW_FLAMMABILITY;
            else if(perlinCoefficient >= .55 && perlinCoefficient < .7) map[i][j].state = MEDIUM_FLAMMABILITY;
            else map[i][j].state = HIGH_FLAMMABILITY;

        }
    }

    return map;
}

//DEPRECATED : READING TO FILE TO ALLOCATE DYNAMIC MAP SIZE
//TOO COMPLICATED TO CREATE LARGER MAPS
 /*
CELL** readMap(char *filename) {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////                                      EVALUATING MAP WIDTH                                    ////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Map file
    FILE* fp = fopen(filename,"a+");
    //char cellChar;
    mapWidth = 0;
    if(fp != NULL) {
        //Iterating over the file
        while(fgetc(fp) != '\n') {
            //We increment the map width
            mapWidth++;
        }
        fclose(fp);

    } else {
        printf("Error : the file couldn't be opened");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                       EVALUATING MAP HEIGHT                                    ////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Map file
    fp = fopen(filename,"a+");
    //buffer char
    char cellChar;
    mapHeight = 0;

    if(fp != NULL) {
        //Iterating over the file
        while(1) {
            cellChar = fgetc(fp);
            if(cellChar == EOF) break;
            if(cellChar=='\n') {
                mapHeight++;
            }
        }
        fclose(fp);

    } else {
        printf("Error : the file couldn't be opened");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////                                      CREATING THE CA                                         //////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    fp = fopen(filename,"a+");
    //Buffer line of char
    char cellLine[mapWidth];

    //MAP ALLOCATION
    CELL **map = (CELL **) malloc(mapWidth * sizeof(CELL *));
    for (int i = 0; i < mapWidth; i++)
        map[i] = (CELL *) malloc(mapHeight * sizeof(CELL));

    if(fp != NULL) {
        //Iterating into the file
        for(int i = 0; i < mapHeight; i++) {
            //Retriving line by line
            fgets(cellLine, mapWidth, fp);
            //Itrerating over the array of char
            for(int j = 0; j < mapWidth; j++) {
                cellChar = cellLine[j];
                if(cellChar == 'F') {
                    map[i][j].state = FUEL;
                } else {
                    map[i][j].state = NON_FUEL;
                }
                //Initializing generations burning
                map[i][j].generationsBurning = -1;
            }
        }

    } else {
        printf("Error : the file couldn't be opened");
    }
    fclose(fp);
    //Closing the file
    return map;

}*/