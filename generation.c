//
// Created by Pax on 09/10/2023.
//

#include "generation.h"
#include "states.h"
#include <malloc.h>
#include <stdlib.h>




Cell **allocateMemory(int width, int height) {
    Cell **grid = (Cell **) malloc(width * sizeof(Cell *));
    for (int i = 0; i < width; i++)
        grid[i] = (Cell *) malloc(height * sizeof(Cell));
    return grid;
}

void initMap(Cell **grid, int width, int height) {
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


Cell** readMap(char *filename) {

    int width = getMapWidth(filename);
    int height = getMapHeight(filename);

    FILE* fp = fopen(filename,"a+");
    char cellChar;


    Cell **grid = (Cell **) malloc(width * sizeof(Cell *));
    for (int i = 0; i < width; i++)
        grid[i] = (Cell *) malloc(height * sizeof(Cell));

    if(fp != NULL) {

        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                cellChar = fgetc(fp);
                if(cellChar == EOF) break;
                if(cellChar == 'F') {
                    grid[i][j].state = FUEL;
                } else if(cellChar == 'N') {
                    grid[i][j].state = NON_FUEL;
                }
            }
        };
    } else {
        printf("Error : the file couldn't be opened");
    }
    fclose(fp);
    return grid;

}

