#include "structures.h"
#include <malloc.h>
#include "readmap.h"

#include "constants.h"
//
// Created by arnaud on 30/10/23.
//

int mapWidth;
int mapHeight;
/**
 * Function readMap aims to manage the input. It processes a map file to return a grid of CELLs
 * @pre The map file must be correct
 * @param filename The file path
 * @return A grid of CELLs according to the map file
 */
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
    CELL **grid = (CELL **) malloc(mapWidth * sizeof(CELL *));
    for (int i = 0; i < mapWidth; i++)
        grid[i] = (CELL *) malloc(mapHeight * sizeof(CELL));

    if(fp != NULL) {
        //Iterating into the file
        for(int i = 0; i < mapHeight; i++) {
            //Retriving line by line
            fgets(cellLine, mapWidth, fp);
            //Itrerating over the array of char
            for(int j = 0; j < mapWidth; j++) {
                cellChar = cellLine[j];
                if(cellChar == 'F') {
                    grid[i][j].state = FUEL;
                } else {
                    grid[i][j].state = NON_FUEL;
                }
                //Initializing generations burning
                grid[i][j].generationsBurning = -1;
            }
        }

    } else {
        printf("Error : the file couldn't be opened");
    }
    fclose(fp);
    //Closing the file
    return grid;

}