//
// Created by Pax on 09/10/2023.
//

#include "generation.h"
#include "structures.h"
#include <malloc.h>
#include <stdlib.h>




CELL **allocateMemory(int width, int height) {
    CELL **grid = (CELL **) malloc(width * sizeof(CELL *));
    for (int i = 0; i < width; i++)
        grid[i] = (CELL *) malloc(height * sizeof(CELL));
    return grid;
}

void initMap(CELL **grid, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            grid[i][j].state = FUEL;
        }
    }

}

int getMapWidth(char *filename) {
    FILE* fp = fopen(filename,"a+");
    //char cellChar;
    int count = 0;

    if(fp != NULL) {
        while(fgetc(fp) != '\n') {
            count++;
        }
        fclose(fp);

    } else {
        printf("Error : the file couldn't be opened");
    }
    return count;
}

int getMapHeight(char *filename) {
    FILE* fp = fopen(filename,"a+");
    char cellChar;
    int count = 0;

    if(fp != NULL) {

        while(1) {
            cellChar = fgetc(fp);
            if(cellChar == EOF) break;
            if(cellChar=='\n') {
                count++;
            }
        }
        fclose(fp);

    } else {
        printf("Error : the file couldn't be opened");
    }
    return count;
}


CELL** readMap(char *filename) {

    int width = getMapWidth(filename);
    int height = getMapHeight(filename);

    FILE* fp = fopen(filename,"a+");
    char cellLine[width];
    char cellChar;

    CELL **grid = (CELL **) malloc(width * sizeof(CELL *));
    for (int i = 0; i < width; i++)
        grid[i] = (CELL *) malloc(height * sizeof(CELL));

    if(fp != NULL) {
      for(int i = 0; i < height; i++) {
        fgets(cellLine, width, fp);

        for(int j = 0; j < width; j++) {
          cellChar = cellLine[j];
          if(cellChar == 'F') {
            grid[i][j].state = FUEL;
          } else {
            grid[i][j].state = NON_FUEL;
          }
          grid[i][j].generationsBurning = -1;
        }
      }

    } else {
        printf("Error : the file couldn't be opened");
    }
    fclose(fp);
    return grid;

}
