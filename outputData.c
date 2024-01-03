//Author : Arnaud Endignous
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "functions.h"
#include "constants.h"
void outputData(char* filename, CELL** grid) {
    //Opening the file. Appending mode
    FILE *fp = fopen( filename,"w");
    if(fp != NULL) {
        for(int i = 0; i < MAP_WIDTH; i++) {
            for(int j=0;j<MAP_HEIGHT; j++) {
                char toPrint;
                if(grid[i][j].state == LOW_FLAMMABILITY) toPrint='L';
                else if(grid[i][j].state == MEDIUM_FLAMMABILITY) toPrint='M';
                else if(grid[i][j].state == HIGH_FLAMMABILITY) toPrint='H';
                else if(grid[i][j].state == BURNING)toPrint='B';
                else if(grid[i][j].state == BURNT) toPrint='D';
                else if(grid[i][j].state == NON_FUEL) toPrint='N';
                else toPrint= 'E';
                fprintf(fp,"%c",toPrint);
            }
            fprintf(fp,"\n");
        }

        fclose(fp);
    } else {
        printf("Error : the output file couldn't be processed");
    }

}
